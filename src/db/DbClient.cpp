
#include "db/DbClient.hpp"
#include <QJsonDocument>
#include <QTimer>

namespace DB {
    // Public

    DbClient::DbClient(const quint16 port, QObject* parent) : QObject(parent), port(port) {
        this->socket = new QTcpSocket(this);

        connect(this->socket, &QTcpSocket::readyRead, this, &DbClient::onReadyRead);
        connect(this->socket, &QTcpSocket::disconnected, this, &DbClient::reconnect);
        connect(this->socket, &QTcpSocket::connected, this, &DbClient::flushPending);

        this->connectToServer();
    }

    void DbClient::verifyState(std::function<void(QJsonObject)> cb) {this->sendRequest(Operation::VerifyState, Specification::Unknown, {}, std::move(cb));}

    void DbClient::addDownload(const CONTAINER::Download& download, std::function<void(QJsonObject)> cb) {this->sendRequest(Operation::AddInformation, Specification::Unknown, download.toJson(), std::move(cb));}

    void DbClient::removeDownload(const int userId, std::function<void(QJsonObject)> cb) {
        QJsonObject params;
        params[DB_CONSTANTS::JSON_FORMAT::USER_ID] = userId;
        this->sendRequest(Operation::DeleteInformation, Specification::Unknown, params, std::move(cb));
    }

    void DbClient::removeAllDownloads(std::function<void(QJsonObject)> cb) {this->sendRequest(Operation::DeleteAllInformation, Specification::Unknown, {}, std::move(cb));}

    void DbClient::updateAudioCode(const int userId, const int audio_code, std::function<void(QJsonObject)> cb) {
        QJsonObject params;
        params[DB_CONSTANTS::JSON_FORMAT::USER_ID] = userId;
        params[DB_CONSTANTS::JSON_FORMAT::AUDIO_CODE] = audio_code;
        this->sendRequest(Operation::UpdateInformation, Specification::AudioCode, params, std::move(cb));
    }

    void DbClient::updateVideoCode(const int userId, const int video_code, std::function<void(QJsonObject)> cb) {
        QJsonObject params;
        params[DB_CONSTANTS::JSON_FORMAT::USER_ID] = userId;
        params[DB_CONSTANTS::JSON_FORMAT::VIDEO_CODE] = video_code;
        this->sendRequest(Operation::UpdateInformation, Specification::VideoCode, params, std::move(cb));
    }

    void DbClient::updateVideoFormat(const int userId, const QString& video_format, std::function<void(QJsonObject)> cb) {
        QJsonObject params;
        params[DB_CONSTANTS::JSON_FORMAT::USER_ID] = userId;
        params[DB_CONSTANTS::JSON_FORMAT::VIDEO_FORMAT] = video_format;
        this->sendRequest(Operation::UpdateInformation, Specification::VideoFormat, params, std::move(cb));
    }

    void DbClient::updateSaveName(const int userId, const QString& saveName, std::function<void(QJsonObject)> cb) {
        QJsonObject params;
        params[DB_CONSTANTS::JSON_FORMAT::USER_ID] = userId;
        params[DB_CONSTANTS::JSON_FORMAT::SAVE_NAME] = saveName;
        this->sendRequest(Operation::UpdateInformation, Specification::SaveName, params, std::move(cb));
    }

    void DbClient::updateFilePath(const int userId, const QString& filePath, std::function<void(QJsonObject)> cb) {
        QJsonObject params;
        params[DB_CONSTANTS::JSON_FORMAT::USER_ID] = userId;
        params[DB_CONSTANTS::JSON_FORMAT::FILE_PATH] = filePath;
        this->sendRequest(Operation::UpdateInformation, Specification::FilePath, params, std::move(cb));
    }

    void DbClient::updateSuffix(const int userId, const QString& suffix, std::function<void(QJsonObject)> cb) {
        QJsonObject params;
        params[DB_CONSTANTS::JSON_FORMAT::USER_ID] = userId;
        params[DB_CONSTANTS::JSON_FORMAT::SUFFIX] = suffix;
        this->sendRequest(Operation::UpdateInformation, Specification::Suffix, params, std::move(cb));
    }

    void DbClient::updateProgress(const int userId, const int progress, std::function<void(QJsonObject)> cb) {
        QJsonObject params;
        params[DB_CONSTANTS::JSON_FORMAT::USER_ID] = userId;
        params[DB_CONSTANTS::JSON_FORMAT::PROGRESS] = progress;
        this->sendRequest(Operation::UpdateInformation, Specification::Progress, params, std::move(cb));
    }

    void DbClient::updateDownloadState(const int userId, const bool download_state, std::function<void(QJsonObject)> cb) {
        QJsonObject params;
        params[DB_CONSTANTS::JSON_FORMAT::USER_ID] = userId;
        params[DB_CONSTANTS::JSON_FORMAT::DOWNLOAD_STATE] = download_state;
        this->sendRequest(Operation::UpdateInformation, Specification::DownloadState, params, std::move(cb));
    }

    void DbClient::updateMetadata(const int userId, const bool metadata, std::function<void(QJsonObject)> cb) {
        QJsonObject params;
        params[DB_CONSTANTS::JSON_FORMAT::USER_ID] = userId;
        params[DB_CONSTANTS::JSON_FORMAT::METADATA] = metadata;
        this->sendRequest(Operation::UpdateInformation, Specification::Metadata, params, std::move(cb));
    }

    void DbClient::updateSubtitles(const int userId, const bool subtitles, std::function<void(QJsonObject)> cb) {
        QJsonObject params;
        params[DB_CONSTANTS::JSON_FORMAT::USER_ID] = userId;
        params[DB_CONSTANTS::JSON_FORMAT::SUBTITLES] = subtitles;
        this->sendRequest(Operation::UpdateInformation, Specification::Subtitles, params, std::move(cb));
    }

    void DbClient::updateAutoGeneratedSubtitles(const int userId, const bool auto_generated_subtitles, std::function<void(QJsonObject)> cb) {
        QJsonObject params;
        params[DB_CONSTANTS::JSON_FORMAT::USER_ID] = userId;
        params[DB_CONSTANTS::JSON_FORMAT::AUTO_GENERATED_SUBTITLES] = auto_generated_subtitles;
        this->sendRequest(Operation::UpdateInformation, Specification::AutoGeneratedSubtitles, params, std::move(cb));
    }

    void DbClient::readDownload(const int userId, std::function<void(QJsonObject)> cb) {
        QJsonObject params;
        params[DB_CONSTANTS::JSON_FORMAT::USER_ID] = userId;
        this->sendRequest(Operation::GetInformation, Specification::Unknown, params, std::move(cb));
    }

    void DbClient::readAllDownloads(std::function<void(QJsonObject)> cb) {this->sendRequest(Operation::GetAllInformation, Specification::Unknown, {}, std::move(cb));}

    DbClient::~DbClient() {
        if (this->socket) {
            this->socket->disconnectFromHost();
            this->socket->abort();
        }
    }


    // Private Slots

    void DbClient::onReadyRead() {
        while (this->socket->canReadLine()) {
            auto doc = QJsonDocument::fromJson(this->socket->readLine());

            if (!doc.isObject()) continue;

            auto obj = doc.object();

            if (const int id = obj[DB_CONSTANTS::JSON_FORMAT::ID].toInt(); this->callbacks.contains(id)) {
                auto cb = this->callbacks.take(id);
                cb(obj);
            }
        }
    }


    // Private

    void DbClient::connectToServer() const {
        if (this->socket->state() == QAbstractSocket::ConnectedState) return;

        this->socket->connectToHost(QHostAddress::LocalHost, this->port);
    }

    void DbClient::reconnect() const {QTimer::singleShot(DB_CONSTANTS::DB_CLIENT::INTERVAL_FOR_RECONNECT, this, [this]() {this->connectToServer();});}

    void DbClient::flushPending() {
        while (!this->pending.empty()) {
            auto [op, spec, params, cb] = this->pending.dequeue();
            this->sendRequest(op, spec, params, cb);
        }
    }

    void DbClient::sendRequest(const Operation& op, const Specification& spec, const QJsonObject& params, std::function<void(QJsonObject)> cb) {
        if (this->socket->state() != QAbstractSocket::ConnectedState) {
            this->pending.enqueue({op, spec, params, cb});
            return;
        }

        const auto id = nextId++;
        this->callbacks[id] = std::move(cb);

        QJsonObject obj;

        obj[DB_CONSTANTS::JSON_FORMAT::ID] = id;
        obj[DB_CONSTANTS::JSON_FORMAT::OPERATION] = opToString(op);
        obj[DB_CONSTANTS::JSON_FORMAT::SPECIFICATION] = specToString(spec);
        obj[DB_CONSTANTS::JSON_FORMAT::PARAMETERS] = params;

        this->socket->write(QJsonDocument(obj).toJson(QJsonDocument::Compact) + "\n");

        QTimer::singleShot(DB_CONSTANTS::DB_CLIENT::TIME_REMOVE_ID_FROM_CALLBACKS, this, [this, id]() {this->callbacks.remove(id);});
    }
}
