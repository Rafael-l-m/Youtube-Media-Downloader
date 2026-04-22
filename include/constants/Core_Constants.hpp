
#pragma once

#include <QRegularExpression>

namespace CORE_CONSTANTS {
    inline const QString CURRENT_VERSION = "v1.0.0";

    namespace BASIC_TOOLS {
        namespace SEPARATOR {
            inline constexpr QChar CUT_YOUTUBE = '&';
        }

        inline constexpr int WAIT_TIME_FOR_GETTING_TITLE = 30000;
        inline constexpr int WAIT_INTERVAL_CHECK_EXECUTABLE = 3000;

        inline static const QRegularExpression PATTERN_VALID_URL(R"(^(https?|ftp)://[^\s/$.?#].[^\s]*$)", QRegularExpression::CaseInsensitiveOption);
        inline static const QRegularExpression PATTERN_CUR_URL_YOUTUBE(R"regex(https?://(www\.)?(youtube\.com/watch\?v=|youtu\.be/))regex", QRegularExpression::CaseInsensitiveOption);
        inline static const QRegularExpression PATTERN_VIDEO_FORMAT(R"(^\d+-sr$)", QRegularExpression::CaseInsensitiveOption);
        inline static const QRegularExpression INVALID_CHARACTERS(R"([\\\\/:*?\"<>|])", QRegularExpression::CaseInsensitiveOption);

        inline const QStringList RESERVED_STRINGS = {"CON","PRN","AUX","NUL","COM1","COM2","COM3","COM4","COM5","COM6","COM7","COM8","COM9", "LPT1","LPT2","LPT3","LPT4","LPT5","LPT6","LPT7","LPT8","LPT9"};

        inline QStringList SEARCH_PATHS() {
            QStringList searchPaths;

            #ifdef Q_OS_MAC
                searchPaths << "/opt/homebrew/bin"
                            << "/usr/local/bin"
                            << "/usr/bin"
                            << "/bin"
                            << "/opt/local/bin";
            #elif defined(Q_OS_LINUX)
                searchPaths << "/usr/bin"
                            << "/usr/local/bin"
                            << "/snap/bin"
                            << "snap/local/bin"
                            << "/bin"
                            << "/home/linuxbrew/.linuxbrew";
            #elif defined(Q_OS_WIN)
                searchPaths << "C:/Program Files"
                            << "C:/Program Files (x86)"
                            << "C:/ProgramData"
                            << QDir::homePath() + "/scoop/apps";
            #endif

            return searchPaths;
        }
    }

    namespace CRYPTO_MANAGER {
        inline const QString DEFAULT_KEY_NAME = "crypto.key";
    }

    namespace MEDIA_FILTERS {
        namespace AUDIO_FILTERS {
            inline const QString FILTER_AUDIO =
                "WAV (*.wav);;"
                "MP3 (*.mp3);;"
                "FLAC (*.flac);;"
                "M4A (*.m4a);;"
                "AAC (*.aac);;"
                "Opus (*.opus);;";

            inline QString EXTRACT_AUDIO_FILTER(const QString& text) {
                if (!text.isEmpty()) {
                    if (text.compare("WAV (*.wav)", Qt::CaseInsensitive) == 0) return "wav";
                    if (text.compare("MP3 (*.mp3)", Qt::CaseInsensitive) == 0) return "mp3";
                    if (text.compare("FLAC (*.flac)", Qt::CaseInsensitive) == 0) return "flac";
                    if (text.compare("M4A (*.m4a)", Qt::CaseInsensitive) == 0) return "m4a";
                    if (text.compare("AAC (*.aac)", Qt::CaseInsensitive) == 0) return "aac";
                    if (text.compare("Opus (*.opus)", Qt::CaseInsensitive) == 0) return "opus";
                }

                return "wav";
            }

            inline const QSet<QString> SUPPORTED_AUDIO_FORMATS = {"wav", "mp3", "flac", "m4a", "aac", "opus"};
        }

        namespace VIDEO_FILTERS {
            inline const QString FILTER_VIDEO =
                "MKV (*.mkv);;"
                "MP4 (*.mp4);;"
                "Webm (*.webm);;";

            inline QString EXTRACT_VIDEO_FILTER(const QString& text) {
                if (!text.isEmpty()) {
                    if (text.compare("MKV (*.mkv)", Qt::CaseInsensitive) == 0) return "mkv";
                    if (text.compare("MP4 (*.mp4)", Qt::CaseInsensitive) == 0) return "mp4";
                    if (text.compare("Webm (*.webm)", Qt::CaseInsensitive) == 0) return "webm";
                }

                return "mkv";
            }

            inline const QSet<QString> SUPPORTED_VIDEO_FORMATS = {"mkv", "mp4", "webm"};
        }
    }

    namespace MEDIA_I_TAGS {
        namespace AUDIO_I_TAGS {
            inline const QSet AUDIO_FORMATS = {139, 140, 141, 249, 250, 251};
            inline QString ERROR_MESSAGE_I_TAG() {return QObject::tr("Invalid Audio Itag");}
        }

        namespace VIDEO_I_TAGS {
            inline const QSet VIDEO_FORMATS = {133, 134, 135, 136, 137, 160, 242, 243, 244, 245, 246, 247, 248, 264, 266, 271, 272, 298, 299, 302, 303, 308, 313, 315, 330, 331, 332, 333, 334, 335, 336, 337, 394, 395, 396, 397, 398, 399, 400, 401, 402};
            inline QString ERROR_MESSAGE_I_TAG() {return QObject::tr("Invalid Video Itag");}
            inline QString ERROR_MESSAGE_FORMAT() {return QObject::tr("Invalid Video Format");}
        }
    }

    namespace SETTINGS_VIEW {
        inline const QString DEFAULT_ORGANIZATION = "rafael";
        inline const QString DEFAULT_APPLICATION = "MediaDownloader";
        inline const QString DEFAULT_LOCAL_SERVER = "MediaDownloaderAppServer";
        inline const QString DEFAULT_TRANSLATION_PLIST = "Translation";
        inline const QString DEFAULT_LANGUAGE = "en_US.qm";
        inline const QString DEFAULT_TRANSLATION_DOC_SUFFIX = ".qm";
        inline const QString DEFAULT_YT_DLP_KEY = "tools/yt_dlp_path";
        inline const QString DEFAULT_FFMPEG_KEY = "tools/ffmpeg_path";
        inline const QString DEFAULT_NODE_JS_KEY = "tools/node_js_path";
        inline const QString DEFAULT_TRANSLATOR_KEY = "translator/default_language";
    }

    namespace YT_DLP_CLI_OPTIONS {
        inline const QString AUDIO_FORMAT = "--audio-format";
        inline const QString AUDIO_QUALITY = "--audio-quality";
        inline const QString BEST_AUDIO = "bestaudio";
        inline const QString BEST_AUDIO_AND_BEST_VIDEO = "bv+ba";
        inline const QString CONCURRENT_FRAGMENTS = "--concurrent-fragments";
        inline const QString EMBED_METADATA = "--embed-metadata";
        inline const QString F = "-f";
        inline const QString FFMPEG_LOCATION = "--ffmpeg-location";
        inline const QString FRAGMENT_RETRIES = "--fragment-retries";
        inline const QString GET_TITLE = "--get-title";
        inline const QString INFO = "-F";
        inline const QString LIMIT_RATE = "--limit-rate";
        inline const QString MERGE_OUTPUT_FORMAT = "--merge-output-format";
        inline const QString NO_PLAYLIST = "--no-playlist";
        inline const QString OUTPUT = "--output";
        inline const QString RETRIES = "--retries";
        inline const QString USER_AGENT = "--user-agent";
        inline const QString X = "-x";
    }
}
