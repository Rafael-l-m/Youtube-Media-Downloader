
#include "constants/Core_Constants.hpp"
#include "constants/Download_Constants.hpp"
#include "download/DownloadManager.hpp"
#include "core/SharedStorage.hpp"
#include <QTimer>

namespace DOWNLOAD_DOWNLOAD_MANAGER {
    // Public

    DownloadManager::DownloadManager(QWidget *parent) : QWidget(parent), runningWorkers(0), maxConcurrent(DOWNLOAD_CONSTANTS::DOWNLOAD_WORKER::MAX_CONCURRENT_PROCESS) {}

    bool DownloadManager::isRunning() const {return this->runningWorkers > 0;}

    void DownloadManager::start() {
        this->stopping = false;
        QTimer::singleShot(0, this, &DownloadManager::tryStartNext);
    }

    void DownloadManager::stopAll() {
        QMutexLocker locker(&this->mutex);

        this->stopping = true;

        for (const auto& worker : this->workers) {
            if (worker) {
                (void)worker->disconnect();
                worker->deleteLater();
            }
        }

        this->workers.clear();
        this->currentlyDownloading.clear();
        this->runningWorkers = 0;
    }

    void DownloadManager::setMaxConcurrent(const int max_concurrent) {this->maxConcurrent = max_concurrent;}


    // Private slots

    void DownloadManager::handleUpdateProgress(const int id, const int progress) {emit downloadProgress(id, progress);}
    void DownloadManager::handleTooManyRequest() {emit downloadTooManyRequest();}  // Dynamic process scaling + Preferences->General let users decide
    void DownloadManager::handleErrorOccurred(const QString& errorString) {emit downloadErrorOccurred(errorString);}


    // Private

    void DownloadManager::tryStartNext() {
        QMutexLocker locker(&this->mutex);

        if (this->stopping) return;

        const auto list = CORE::SharedStorage::instance().getDownloads();
        if (!list) return;

        for (auto& d : *list) {
            if (this->runningWorkers >= this->maxConcurrent) return;

            if (d->getDownloadState()) continue;

            if (this->currentlyDownloading.contains(d->getId())) continue;

            auto* worker = new DOWNLOAD_DOWNLOAD_WORKER::DownloadWorker(d, this);
            this->workers.insert(d->getId(), worker);

            connect(worker, &DOWNLOAD_DOWNLOAD_WORKER::DownloadWorker::progress, this, &DownloadManager::handleUpdateProgress);
            connect(worker, &DOWNLOAD_DOWNLOAD_WORKER::DownloadWorker::normalFinished, this, [this, worker](const int idd) {
                {
                    QMutexLocker lock(&this->mutex);
                    --this->runningWorkers;
                }

                worker->stop();
                this->workers.remove(idd);
                this->currentlyDownloading.remove(idd);
                worker->deleteLater();

                QTimer::singleShot(0, this, &DownloadManager::tryStartNext);
                emit downloadNormalFinished(idd);

                this->checkAllFinished();
            });

            connect(worker, &DOWNLOAD_DOWNLOAD_WORKER::DownloadWorker::unnormalFinished, this, [this, worker](const int idd) {
                {
                    QMutexLocker lock(&this->mutex);
                    --this->runningWorkers;
                }

                worker->stop();
                this->workers.remove(idd);
                this->currentlyDownloading.remove(idd);
                worker->deleteLater();

                QTimer::singleShot(0, this, &DownloadManager::tryStartNext);

                // Exception
                if (CORE_CONSTANTS::MEDIA_FILTERS::AUDIO_FILTERS::SUPPORTED_AUDIO_FORMATS.contains(CORE::SharedStorage::instance().getDownload(idd)->getSuffix())) emit downloadNormalFinished(idd);
                else emit downloadUnnormalFinished(idd);

                this->checkAllFinished();
            });

            connect(worker, &DOWNLOAD_DOWNLOAD_WORKER::DownloadWorker::tooManyRequests, this, &DownloadManager::handleTooManyRequest);
            connect(worker, &DOWNLOAD_DOWNLOAD_WORKER::DownloadWorker::errorOccurred, this, &DownloadManager::handleErrorOccurred);

            this->currentlyDownloading.insert(d->getId());
            ++this->runningWorkers;

            worker->start();
        }
    }

    void DownloadManager::checkAllFinished() {
        QMutexLocker locker(&this->mutex);

        if (this->runningWorkers > 0) return;
        if (!this->currentlyDownloading.isEmpty()) return;

        if (const auto list = CORE::SharedStorage::instance().getDownloads(); !list) return;

        emit allFinished();
    }
}
