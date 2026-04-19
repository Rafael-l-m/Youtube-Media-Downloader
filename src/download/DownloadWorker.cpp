
#include "constants/Core_Constants.hpp"
#include <constants/Download_Constants.hpp>
#include "constants/Ui_Constants.hpp"
#include "core/SharedStorage.hpp"
#include "download/DownloadWorker.hpp"
#include <QDir>
#include <QRandomGenerator>
#include <QTimer>

namespace DOWNLOAD_DOWNLOAD_WORKER {
    // Public

    DownloadWorker::DownloadWorker(const QSharedPointer<CONTAINER::Download>& d, QWidget* parent) : QWidget(parent), download(d), process(new QProcess(this)) {}

    DownloadWorker::~DownloadWorker() {(void)disconnect();}


    // Public slots

    void DownloadWorker::start() {
        const auto randomDelayMs = QRandomGenerator::global()->bounded(DOWNLOAD_CONSTANTS::DOWNLOAD_WORKER::MIN_WAIT_TIME, DOWNLOAD_CONSTANTS::DOWNLOAD_WORKER::MAX_WAIT_TIME + 1);
        const auto randomKString = QRandomGenerator::global()->bounded(DOWNLOAD_CONSTANTS::DOWNLOAD_WORKER::MIN_RATE, DOWNLOAD_CONSTANTS::DOWNLOAD_WORKER::MAX_RATE);
        const auto& ua = DOWNLOAD_CONSTANTS::DOWNLOAD_WORKER::userAgents.at(QRandomGenerator::global()->bounded(DOWNLOAD_CONSTANTS::DOWNLOAD_WORKER::userAgents.size()));

        QTimer::singleShot(randomDelayMs, this, [this, randomKString, ua]() {
            const auto tp = CORE::SharedStorage::instance().getToolsPath();

            QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
            env.insert(DOWNLOAD_CONSTANTS::DOWNLOAD_WORKER::PATH, tp->getNodePath() + QDir::listSeparator() + env.value(DOWNLOAD_CONSTANTS::DOWNLOAD_WORKER::PATH));
            this->process->setProcessEnvironment(env);

            QStringList arguments;
            arguments << CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::FFMPEG_LOCATION << tp->getFFmpegPath()
                    << CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::NO_PLAYLIST
                    << CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::LIMIT_RATE << QString::number(randomKString) + "K"
                    << CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::USER_AGENT << ua
                    << CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::OUTPUT << (this->download->getFilePath() + QDir::separator() + this->download->getSaveName() + UI_CONSTANTS::MAIN_WINDOW::POINT + this->download->getSuffix())
                    << CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::RETRIES << QString::number(DOWNLOAD_CONSTANTS::DOWNLOAD_WORKER::RETRIES)
                    << CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::FRAGMENT_RETRIES << QString::number(DOWNLOAD_CONSTANTS::DOWNLOAD_WORKER::FRAGMENT_RETRIES)
                    << CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::CONCURRENT_FRAGMENTS << QString::number(DOWNLOAD_CONSTANTS::DOWNLOAD_WORKER::CONCURRENT_RETRIES);

            if (this->download->getMetadata()) arguments.append(CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::EMBED_METADATA);

            const auto ac = this->download->getAudioCode();
            const auto vc = this->download->getVideoCode();
            const auto vf = this->download->getVideoFormat();
            const auto suf = this->download->getSuffix();

            if (ac != 0 && vc != 0) {
                arguments.append(CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::F);
                arguments.append(QString("%1+%2").arg(vc).arg(ac));
                arguments.append(CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::MERGE_OUTPUT_FORMAT);
                arguments.append(suf);
            }

            else if (vc == 0 && ac != 0) {
                if (vf.trimmed().isEmpty()) {
                    arguments.append(CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::X);
                    arguments.append(CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::AUDIO_FORMAT);
                    arguments.append(suf);
                    arguments.append(CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::F);
                    arguments.append(QString("%1").arg(ac));
                    arguments.append(CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::AUDIO_QUALITY);
                    arguments.append("0");
                }

                else {
                    arguments.append(CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::F);
                    arguments.append(QString("%1+%2").arg(vf).arg(ac));
                    arguments.append(CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::MERGE_OUTPUT_FORMAT);
                    arguments.append(suf);
                }
            }

            else {
                if (CORE_CONSTANTS::MEDIA_FILTERS::AUDIO_FILTERS::SUPPORTED_AUDIO_FORMATS.contains(suf)) {
                    arguments.append(CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::F);
                    arguments.append(CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::BEST_AUDIO);
                    arguments.append(CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::AUDIO_FORMAT);
                    arguments.append(suf);
                    arguments.append(CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::AUDIO_QUALITY);
                    arguments.append("0");
                }

                else if (CORE_CONSTANTS::MEDIA_FILTERS::VIDEO_FILTERS::SUPPORTED_VIDEO_FORMATS.contains(suf)) {
                    arguments.append(CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::F);
                    arguments.append(CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::BEST_AUDIO_AND_BEST_VIDEO);
                    arguments.append(CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::MERGE_OUTPUT_FORMAT);
                    arguments.append(suf);
                }
            }

            /*
            const auto subt = this->download->getSubtitles();
            const auto at_subt = this->download->getAutoGeneratedSubtitles();

            if (subt) {
                arguments.append(CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::WRITE_SUBS);
                if (at_subt) arguments.append(CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::WRITE_AUTO_SUBS);
                arguments.append(CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::SUB_LANGS);
                arguments.append(CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::ALL);
                arguments.append(CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::EMBED_SUBS);
            }
            */

            arguments.append(this->download->getUrl());

            // emit progress();
            connect(this->process, &QProcess::readyReadStandardOutput, this, [this]() {
                #ifdef Q_OS_WIN
                    const auto text = QString::fromLocal8Bit(this->process->readAllStandardOutput());
                #else
                    const auto text = QString::fromUtf8(this->process->readAllStandardOutput());
                #endif

                if (const auto match = DOWNLOAD_CONSTANTS::DOWNLOAD_WORKER::PATTERN_EXTRACT_PROGRESS.match(text); match.hasMatch()) {
                    const auto pg = match.captured(1).toDouble();
                    const auto prog = qRound(pg * 10);
                    emit progress(this->download->getId(), prog);
                }
            });

            connect(this->process, &QProcess::readyReadStandardError, this, [this]() {
                if (const auto err = this->process->readAllStandardError();
                    err.contains(DOWNLOAD_CONSTANTS::DOWNLOAD_WORKER::ERRORS_CAUSED_TOO_MANY_REQUESTS::CODE_429) ||
                    err.contains(DOWNLOAD_CONSTANTS::DOWNLOAD_WORKER::ERRORS_CAUSED_TOO_MANY_REQUESTS::TOO_MANY_REQUEST) ||
                    err.contains(DOWNLOAD_CONSTANTS::DOWNLOAD_WORKER::ERRORS_CAUSED_TOO_MANY_REQUESTS::CODE_403) ||
                    err.contains(DOWNLOAD_CONSTANTS::DOWNLOAD_WORKER::ERRORS_CAUSED_TOO_MANY_REQUESTS::FORBIDDEN) ||
                    err.contains(DOWNLOAD_CONSTANTS::DOWNLOAD_WORKER::ERRORS_CAUSED_TOO_MANY_REQUESTS::RATE_LIMIT) ||
                    err.contains(DOWNLOAD_CONSTANTS::DOWNLOAD_WORKER::ERRORS_CAUSED_TOO_MANY_REQUESTS::LIMIT_EXCEEDED)) emit tooManyRequests();
                else emit errorOccurred(err);
            });

            connect(this->process, &QProcess::finished, this, [=, this](const int exitCode, const QProcess::ExitStatus exitStatus) mutable {
                if (exitCode == 0 && exitStatus == QProcess::NormalExit)  emit normalFinished(this->download->getId());

                else emit unnormalFinished(this->download->getId());

                this->process->deleteLater();
            });

            connect(this->process, &QProcess::errorOccurred, this, [this]() {emit errorOccurred(this->process->errorString());});

            this->process->start(tp->getYtDlpPath(), arguments);
        });
    }

    void DownloadWorker::stop() const {
        if (!this->process) return;

        if (this->process->state() != QProcess::NotRunning) {
            process->terminate();
            QTimer::singleShot(200,this,[this]() {if (process && process->state() != QProcess::NotRunning) process->kill();});
        }
    }
}
