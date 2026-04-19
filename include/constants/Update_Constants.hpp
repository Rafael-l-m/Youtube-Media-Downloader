
#pragma once

#include <QObject>
#include <QUrl>

namespace UPDATE_CONSTANTS::UPDATE_CHECKER {
        inline const QString TAG_NAME = "tag_name";
        inline const QString BODY = "body";
        inline const QString ASSETS = "assets";
        inline const QString BROWSER_DOWNLOAD_URL = "browser_download_url";

        inline const auto URL_GET_UPDATES = QUrl("https://api.github.com/repos/Rafael-l-m/YouTubeMediaDownloader/releases/latest");

        inline QString UPDATE_AVAILABLE() {return QObject::tr("Update Available");}
        inline QString UPDATE_INFORMATION(const QString& version, const QString& notes) {return QObject::tr("New Version: %1\n\n%2").arg(version, notes);}
        inline QString NO_UPDATE() {return QObject::tr("No Update");}
        inline QString INFO_NO_UPDATE() {return QObject::tr("You are using the latest version");}
        inline QString FAILED_UPDATE() {return QObject::tr("Failed Update");}
}
