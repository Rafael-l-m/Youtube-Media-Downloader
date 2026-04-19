
#include "constants/Core_Constants.hpp"
#include "constants/Update_Constants.hpp"
#include "update/UpdateChecker.hpp"
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkReply>

namespace UPDATE {
    // Public

    UpdateChecker::UpdateChecker(QObject* parent) : QObject(parent) {this->manager = new QNetworkAccessManager(this);}

    void UpdateChecker::check() {
        QNetworkRequest req(UPDATE_CONSTANTS::UPDATE_CHECKER::URL_GET_UPDATES);
        req.setRawHeader("Cache-Control", "no-cache");

        QNetworkReply* reply = this->manager->get(req);

        connect(reply, &QNetworkReply::finished, this, [this, reply]() {
            if (reply->error() != QNetworkReply::NoError) {
                emit checkFailed(reply->errorString());
                reply->deleteLater();
                return;
            }

            const auto data = reply->readAll();
            reply->deleteLater();

            const auto doc = QJsonDocument::fromJson(data);
            if (!doc.isObject()) return;

            auto obj = doc.object();

            const auto latest = obj[UPDATE_CONSTANTS::UPDATE_CHECKER::TAG_NAME].toString();
            const auto notes = obj[UPDATE_CONSTANTS::UPDATE_CHECKER::BODY].toString();

            QString downloadUrl;
            if (obj[UPDATE_CONSTANTS::UPDATE_CHECKER::ASSETS].isArray() && !obj[UPDATE_CONSTANTS::UPDATE_CHECKER::ASSETS].toArray().isEmpty()) downloadUrl = obj[UPDATE_CONSTANTS::UPDATE_CHECKER::ASSETS].toArray()[0].toObject()[UPDATE_CONSTANTS::UPDATE_CHECKER::BROWSER_DOWNLOAD_URL].toString();

            emit versionGreater(latest, CORE_CONSTANTS::CURRENT_VERSION) ? updateAvailable(latest, notes, downloadUrl) : noUpdate();
        });
    }


    // Private

    bool UpdateChecker::versionGreater(const QString& version1, const QString& version2) {
        auto split = [](const QString& v) {
            const auto parts = v.mid(1).split(".");

            QList<int> nums;
            for (auto& p : parts) nums << p.toInt();

            return nums;
        };

        QList<int> a = split(version1);
        QList<int> b = split(version2);

        for (int i = 0; i < qMax(a.size(), b.size()); i++) {
            const auto x = i < a.size() ? a[i] : 0;
            const auto y = i < b.size() ? b[i] : 0;
            if (x != y) return x > y;
        }

        return false;
    }
}
