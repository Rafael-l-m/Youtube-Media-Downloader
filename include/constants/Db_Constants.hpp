
#pragma once

#include <QObject>

namespace DB_CONSTANTS {
    namespace DB_CLIENT {
        inline constexpr int INTERVAL_FOR_RECONNECT = 1000;
        inline constexpr int TIME_REMOVE_ID_FROM_CALLBACKS = 5000;
    }

    namespace DB_MANAGER {
        inline const QString DATABASE_NAME = "MediaDownloader.sqlite";
        inline const QString CONNECTION_TYPE = "QSQLITE";
        inline const QString CREATE_TABLE = R"(
            CREATE TABLE IF NOT EXISTS downloads (
                id                        INTEGER PRIMARY KEY,
                url                       TEXT NOT NULL,
                audio_code                INTEGER DEFAULT 0,
                video_code                INTEGER DEFAULT 0,
                video_format              TEXT,
                title                     TEXT NOT NULL,
                save_name                 TEXT NOT NULL,
                file_path                 TEXT NOT NULL,
                suffix                    TEXT NOT NULL,
                progress                  INTEGER DEFAULT 0,
                download_state            INTEGER DEFAULT 0,
                metadata                  INTEGER DEFAULT 0,
                subtitles                 INTEGER DEFAULT 0,
                auto_generated_subtitles  INTEGER DEFAULT 0
            )
        )";
    }

    namespace JSON_FORMAT {
        inline const QString ID = "id";
        inline const QString USER_ID = "userId";
        inline const QString URL = "url";
        inline const QString AUDIO_CODE = "audio_code";
        inline const QString VIDEO_CODE = "video_code";
        inline const QString VIDEO_FORMAT = "video_format";
        inline const QString TITLE = "title";
        inline const QString SAVE_NAME = "save_name";
        inline const QString FILE_PATH = "file_path";
        inline const QString SUFFIX = "suffix";
        inline const QString PROGRESS = "progress";
        inline const QString DOWNLOAD_STATE = "download_state";
        inline const QString METADATA = "metadata";
        inline const QString SUBTITLES = "subtitles";
        inline const QString AUTO_GENERATED_SUBTITLES = "auto_generated_subtitles";

        inline const QString OPERATION = "operation";
        inline const QString SPECIFICATION = "specification";
        inline const QString PARAMETERS = "params";
        inline const QString STATUS = "status";
        inline const QString ERROR = "error";
        inline const QString MESSAGE = "message";

        inline const QString STATUS_OK = "ok";
        inline const QString STATUS_REFUSED = "no";

        inline QString FAILED() {return QObject::tr("Failed");}
        inline QString ADD_DOWNLOAD_FAILED() {return QObject::tr("Failed to add download: Operation rejected by database");}
        inline QString UPDATE_AUDIO_CODE_FAILED() {return QObject::tr("Failed to update audio code: Operation rejected by database");}
        inline QString UPDATE_VIDEO_CODE_FAILED() {return QObject::tr("Failed to update video code: Operation rejected by database");}
        inline QString UPDATE_VIDEO_FORMAT_FAILED() {return QObject::tr("Failed to update video format: Operation rejected by database");}
        inline QString UPDATE_SAVE_NAME_FAILED() {return QObject::tr("Failed to update save name: Operation rejected by database");}
        inline QString UPDATE_FILE_PATH_FAILED() {return QObject::tr("Failed to update file path: Operation rejected by database");}
        inline QString UPDATE_SUFFIX_FAILED() {return QObject::tr("Failed to update suffix: Operation rejected by database");}
        inline QString UPDATE_PROGRESS_FAILED() {return QObject::tr("Failed to update progress: Operation rejected by database");}
        inline QString UPDATE_DOWNLOAD_STATE_FAILED() {return QObject::tr("Failed to update download state: Operation rejected by database");}
        inline QString UPDATE_METADATA_FAILED() {  return QObject::tr("Failed to update metadata: Operation rejected by database"); }
        inline QString UPDATE_SUBTITLES_FAILED() {return QObject::tr("Failed to update subtitles: Operation rejected by database"); }
        inline QString UPDATE_AUTO_GENERATED_SUBTITLES_FAILED() {return QObject::tr("Failed to update auto-generated subtitles: Operation rejected by database"); }

        inline QString DATABASE_EMPTY() {return QObject::tr("Database is empty");}
        inline QString INVALID_OPERATION() {return QObject::tr("Invalid operation: unknown operation");}
        inline QString INVALID_SPECIFICATION() {return QObject::tr("Invalid specification: unknown specification");}
        inline QString INVALID_JSON() {return QObject::tr("Invalid Json");}

        inline QString ID_EXISTS() {return QObject::tr("Id already exists");}
        inline QString ID_NOT_EXISTS() {return QObject::tr("Id not found");}
        inline QString ERROR_ID() {return QObject::tr("Invalid UserId: negative value");}
        inline QString ERROR_TITLE() {return QObject::tr("Invalid Title: unsupported format");}
        inline QString ERROR_VIDEO_FORMAT() {return QObject::tr("Invalid Video Format: unsupported format");}
        inline QString ERROR_SAVE_NAME() {return QObject::tr("Invalid Save Name: contains invalid characters");}
        inline QString ERROR_FILE_PATH() {return QObject::tr("Invalid file path: path does not exist or lacks read/write permissions.");}
        inline QString ERROR_SUFFIX() {return QObject::tr("Invalid Suffix: unsupported format");}
        inline QString ERROR_PROGRESS() {return QObject::tr("Invalid Progress: value is out of range");}
    }

    namespace OPERATIONS {
        inline const QString VERIFY_STATE = "VerifyState";
        inline const QString ADD_INFORMATION = "AddInformation";
        inline const QString GET_INFORMATION = "GetInformation";
        inline const QString GET_ALL_INFORMATION = "GetAllInformation";
        inline const QString UPDATE_INFORMATION = "UpdateInformation";
        inline const QString DELETE_INFORMATION = "DeleteInformation";
        inline const QString DELETE_ALL_INFORMATION = "DeleteAllInformation";
        inline const QString UNKNOWN = "Unknown";
    }

    namespace UPDATE_OPTIONS {
        inline const QString AUDIO_CODE = "AudioCode";
        inline const QString VIDEO_CODE = "VideoCode";
        inline const QString VIDEO_FORMAT = "VideoFormat";
        inline const QString TITLE = "Title";
        inline const QString SAVE_NAME = "SaveName";
        inline const QString FILE_PATH = "FilePath";
        inline const QString SUFFIX = "Suffix";
        inline const QString PROGRESS = "Progress";
        inline const QString DOWNLOAD_STATE = "DownloadState";
        inline const QString METADATA = "Metadata";
        inline const QString SUBTITLES = "Subtitles";
        inline const QString AUTO_GENERATED_SUBTITLES = "AutoGeneratedSubtitles";
        inline const QString UNKNOWN = "Unknown";
    }
}
