
#pragma once

#include <QNetworkAccessManager>

namespace UPDATE {
    class UpdateChecker final : public QObject {
        Q_OBJECT
    public:
        explicit UpdateChecker(QObject* parent = nullptr);
        void check();

    signals:
        void updateAvailable(QString latestVersion, QString notes, QString downloadUrl);
        void noUpdate();
        void checkFailed(QString error);

    private:
        QNetworkAccessManager* manager;
        static bool versionGreater(const QString& version1, const QString& version2);
    };
}
