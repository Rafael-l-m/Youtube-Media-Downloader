
#include "core/BasicTools.hpp"
#include "core/SharedStorage.hpp"
#include "ui/MainWindow.hpp"
#include "ui/NoticeView.hpp"
#include "ui/SettingsView.hpp"
#include <QLocalServer>
#include <QLocalSocket>
#include <QTranslator>

QLocalServer* server = nullptr;

bool sendMessageToRunningInstance(const QString& serverName, const QString& message) {
    QLocalSocket socket;
    socket.connectToServer(serverName);

    if (!socket.waitForConnected(UI_CONSTANTS::MAIN_CPP::WAIT_FOR_SOCKET_CONNECT)) return false;

    socket.write(message.toUtf8());
    socket.flush();
    socket.waitForBytesWritten(UI_CONSTANTS::MAIN_CPP::WAIT_FOR_BYTES_WRITTEN);
    socket.disconnectFromServer();

    return true;
}

void setupServer(const QString& serverName, UI::MainWindow* m) {
    server = new QLocalServer(m);

    QLocalServer::removeServer(serverName);

    server->listen(serverName);

    QObject::connect(server, &QLocalServer::newConnection, [m]() {
        QLocalSocket *client = server->nextPendingConnection();

        QObject::connect(client, &QLocalSocket::readyRead, [client, m] {
            if (const QByteArray msg = client->readAll(); msg.contains(UI_CONSTANTS::MAIN_CPP::KEY_MSG)) {
                m->showNormal();
                m->raise();
                m->activateWindow();
            }
        });
    });
}

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    // LocalServer
    QCoreApplication::setApplicationName(UI_CONSTANTS::MAIN_CPP::APP_NAME);

    if (sendMessageToRunningInstance(CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_LOCAL_SERVER, UI_CONSTANTS::MAIN_CPP::KEY_MSG)) return 0;

    // Load language
    auto df_lan = CORE::SYS_INFO::readConfig(CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_TRANSLATOR_KEY, CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_ORGANIZATION, CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_TRANSLATION_PLIST);

    if (df_lan.isEmpty()) {
        QMap<QString, QString> keys;
        keys.insert(CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_TRANSLATOR_KEY, CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_LANGUAGE);
        CORE::SYS_INFO::writeConfig(keys, CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_ORGANIZATION, CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_TRANSLATION_PLIST);
        df_lan = CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_LANGUAGE;
    }

    QTranslator translator;

    for (const auto searchPaths = UI_CONSTANTS::MAIN_WINDOW::GET_TRANSLATION_PATH(); const QString& path : searchPaths) {
        if (translator.load(df_lan, path)) {
            if (df_lan.compare("ar_SA.qm", Qt::CaseInsensitive) == 0) qApp->setLayoutDirection(Qt::RightToLeft);

            else qApp->setLayoutDirection(Qt::LeftToRight);

            QApplication::installTranslator(&translator);
            break;
        }
    }

    // Load Toolpath
    bool flag = true;

    auto ytDlpPath = CORE::SYS_INFO::readConfig(CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_YT_DLP_KEY);
    auto ffmpegPath = CORE::SYS_INFO::readConfig(CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_FFMPEG_KEY);
    auto nodeJsPath = CORE::SYS_INFO::readConfig(CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_NODE_JS_KEY);

    if (ytDlpPath.isEmpty() || ffmpegPath.isEmpty() || nodeJsPath.isEmpty()) {
        if (UI::SettingsView view; view.exec() == QDialog::Accepted) {
            ytDlpPath = CORE::SYS_INFO::readConfig(CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_YT_DLP_KEY);
            ffmpegPath = CORE::SYS_INFO::readConfig(CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_FFMPEG_KEY);
            nodeJsPath = CORE::SYS_INFO::readConfig(CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_NODE_JS_KEY);
        }

        else flag = false;
    }

    CORE::SharedStorage::instance().setToolsPath({ytDlpPath, ffmpegPath, nodeJsPath});

    if (!flag) {
        UI::NoticeView::critical(UI_CONSTANTS::MAIN_CPP::CRITICAL(), UI_CONSTANTS::MAIN_CPP::CAN_NOT_EXECUTE());
        return -1;
    }

    // Upgrade yt-dlp if possible
    CORE::upgradeYtDlp(ytDlpPath);

    // Show
    UI::MainWindow mw;

    setupServer(CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_LOCAL_SERVER, &mw);

    mw.show();

    return QApplication::exec();
}
