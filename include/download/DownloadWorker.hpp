
#pragma once

#include "container/Download.hpp"
#include <QProcess>
#include <QWidget>

namespace DOWNLOAD_DOWNLOAD_WORKER {
    class DownloadWorker final : public QWidget {
        Q_OBJECT
    public:
        explicit DownloadWorker(const QSharedPointer<CONTAINER::Download>& d, QWidget* parent = nullptr);
        ~DownloadWorker() override;

    signals:
        void progress(int id, int prog);
        void normalFinished(int id);
        void unnormalFinished(int id);
        void tooManyRequests();
        void errorOccurred(const QString& errorString);

    public slots:
        void start();
        void stop() const;

    private:
        QSharedPointer<CONTAINER::Download> download;
        QProcess* process;
    };
}
