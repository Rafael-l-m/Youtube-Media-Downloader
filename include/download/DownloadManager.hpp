
#pragma once

#include "download/DownloadWorker.hpp"

namespace DOWNLOAD_DOWNLOAD_MANAGER {
    class DownloadManager final : public QWidget {
        Q_OBJECT
    public:
        explicit DownloadManager(QWidget* parent = nullptr);
        bool isRunning() const;
        void start();
        void stopAll();
        void setMaxConcurrent(int max_concurrent);

    signals:
        void downloadProgress(int id, int progress);
        void downloadNormalFinished(int id);
        void downloadUnnormalFinished(int id);
        void downloadTooManyRequest();
        void downloadErrorOccurred(const QString& errorString);
        void allFinished();

    private slots:
        void handleUpdateProgress(int id, int progress);
        void handleTooManyRequest();
        void handleErrorOccurred(const QString& errorString);
        void checkAllFinished();

    private:
        void tryStartNext();

        mutable QMutex mutex;

        int runningWorkers;
        int maxConcurrent;
        bool stopping = false;

        QSet<int> currentlyDownloading;
        QHash<int, DOWNLOAD_DOWNLOAD_WORKER::DownloadWorker*> workers;
    };
}
