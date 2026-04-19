
#pragma once

#include "constants/Core_Constants.hpp"
#include "constants/Db_Constants.hpp"
#include "constants/Ui_Constants.hpp"
#include <QDirIterator>
#include <QProcess>
#include <QSettings>
#include <QStandardPaths>

namespace CORE {
    inline QString upgradeYtDlp(const QString& yt_dlp_path) {
        QProcess process;
        process.start(yt_dlp_path, {"-U"});
        process.waitForFinished(-1);
        return QString::fromUtf8(process.readAllStandardOutput());
    }

    namespace MEDIA_INFO {
        inline bool ifValidId(const int id) {return id >= 0;}

        inline bool ifValidURL(const QString& url) {return CORE_CONSTANTS::BASIC_TOOLS::PATTERN_VALID_URL.match(url).hasMatch();}

        inline QString cutURL(const QString& url) {
            // Case 1: YouTube
            if (CORE_CONSTANTS::BASIC_TOOLS::PATTERN_CUR_URL_YOUTUBE.match(url).hasMatch()) {
                if (const auto pos = url.indexOf(CORE_CONSTANTS::BASIC_TOOLS::SEPARATOR::CUT_YOUTUBE); pos != -1) return url.left(pos);
            }

            return url;
        }

        inline QString getTitleFromURL(const QString& yt_dlp_path, const QString& ffmpeg_path, const QString& url) {
            QProcess process;

            const QStringList arguments {
                CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::FFMPEG_LOCATION, ffmpeg_path,
                CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::NO_PLAYLIST,
                CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::GET_TITLE, url
            };

            process.start(yt_dlp_path, arguments);

            if (!process.waitForFinished(CORE_CONSTANTS::BASIC_TOOLS::WAIT_TIME_FOR_GETTING_TITLE)) {
                process.kill();
                return {};
            }

            const auto output = process.readAllStandardOutput();

            return output.isEmpty() ? QString() : QString::fromUtf8(output).trimmed();
        }

        inline bool ifValidAudioCode(const int audio_code) {return CORE_CONSTANTS::MEDIA_I_TAGS::AUDIO_I_TAGS::AUDIO_FORMATS.contains(audio_code);}

        inline bool ifValidVideoCode(const int video_code) {return CORE_CONSTANTS::MEDIA_I_TAGS::VIDEO_I_TAGS::VIDEO_FORMATS.contains(video_code);}

        inline bool ifValidVideoFormat(const QString& video_format) {return video_format.isEmpty() || CORE_CONSTANTS::BASIC_TOOLS::PATTERN_VIDEO_FORMAT.match(video_format.trimmed()).hasMatch();}

        inline bool ifValidTitle(const QString& title) {return title.compare(DB_CONSTANTS::JSON_FORMAT::FAILED(), Qt::CaseInsensitive) != 0;}

        inline bool ifValidSaveName(const QString& save_name) {return !save_name.isEmpty() && !CORE_CONSTANTS::BASIC_TOOLS::INVALID_CHARACTERS.match(save_name).hasMatch() && !CORE_CONSTANTS::BASIC_TOOLS::RESERVED_STRINGS.contains(save_name.toUpper());}

        inline bool ifValidPath(const QString& path) {const QDir dir(path); return dir.exists() && dir.isReadable();}

        inline bool ifValidSuffix(const QString& suffix) {return CORE_CONSTANTS::MEDIA_FILTERS::AUDIO_FILTERS::SUPPORTED_AUDIO_FORMATS.contains(suffix) || CORE_CONSTANTS::MEDIA_FILTERS::VIDEO_FILTERS::SUPPORTED_VIDEO_FORMATS.contains(suffix);}

        inline bool ifValidProgress(const int progress) {return progress >= 0;}
    }

    namespace SYS_INFO {
        inline QString checkExecutable(const QString& program) {
            QProcess process;

            process.setProgram(program);
            process.setArguments({});

            if (process.startDetached()) return program;

            process.start();

            if (process.waitForStarted(CORE_CONSTANTS::BASIC_TOOLS::WAIT_INTERVAL_CHECK_EXECUTABLE)) {
                process.kill();
                process.waitForFinished(CORE_CONSTANTS::BASIC_TOOLS::WAIT_INTERVAL_CHECK_EXECUTABLE);
                return program;
            }

            return {};
        }

        inline QString findToolPath(const QString& program) {
            if (const auto path = QStandardPaths::findExecutable(program); !path.isEmpty()) return path;

            for (const auto searchPaths = CORE_CONSTANTS::BASIC_TOOLS::SEARCH_PATHS(); const auto& dirPath : searchPaths) {
                QDirIterator it(dirPath, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);

                while (it.hasNext()) {
                    it.next();

                    if (QFileInfo fi(it.filePath()); fi.fileName().compare(program, Qt::CaseInsensitive) == 0) return fi.absoluteFilePath();
                }
            }

            return checkExecutable(program);
        }

        static QString readConfig(const QString& key, const QString& organization = CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_ORGANIZATION, const QString& application = CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_APPLICATION) {
            if (const QSettings sysSettings(QSettings::SystemScope, organization, application); sysSettings.contains(key)) return sysSettings.value(key).toString();
            if (const QSettings userSettings(QSettings::UserScope, organization, application); userSettings.contains(key)) return userSettings.value(key).toString();
            return {};
        }

        static bool writeConfig(const QMap<QString, QString>& map, const QString& organization = CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_ORGANIZATION, const QString& application = CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_APPLICATION) {
            QSettings userSettings(QSettings::UserScope, organization, application);

            for (const auto& [key, value] : map.asKeyValueRange()) {userSettings.setValue(key, value);}

            userSettings.sync();

            return userSettings.status() == QSettings::NoError;
        }
    }

    namespace TRANSLATION {
        inline QString languageLocalCode(const QString& language) {
            if (language.compare(UI_CONSTANTS::MAIN_WINDOW::ENGLISH_ACTION, Qt::CaseInsensitive) == 0) return "en_US";
            if (language.compare(UI_CONSTANTS::MAIN_WINDOW::CHINESE_ACTION, Qt::CaseInsensitive) == 0) return "zh_CN";
            if (language.compare(UI_CONSTANTS::MAIN_WINDOW::CHINESE_TRADITIONAL_ACTION, Qt::CaseInsensitive) == 0) return "zh_TW";
            if (language.compare(UI_CONSTANTS::MAIN_WINDOW::SPANISH_ACTION, Qt::CaseInsensitive) == 0) return "es_ES";
            if (language.compare(UI_CONSTANTS::MAIN_WINDOW::PORTUGUESE_ACTION, Qt::CaseInsensitive) == 0) return "pt_PT";
            if (language.compare(UI_CONSTANTS::MAIN_WINDOW::FRENCH_ACTION, Qt::CaseInsensitive) == 0) return "fr_FR";
            if (language.compare(UI_CONSTANTS::MAIN_WINDOW::GERMAN_ACTION, Qt::CaseInsensitive) == 0) return "de_DE";
            if (language.compare(UI_CONSTANTS::MAIN_WINDOW::ITALIAN_ACTION, Qt::CaseInsensitive) == 0) return "it_IT";
            if (language.compare(UI_CONSTANTS::MAIN_WINDOW::ARABIC_ACTION, Qt::CaseInsensitive) == 0) return "ar_SA";
            if (language.compare(UI_CONSTANTS::MAIN_WINDOW::RUSSIAN_ACTION, Qt::CaseInsensitive) == 0) return "ru_RU";
            if (language.compare(UI_CONSTANTS::MAIN_WINDOW::UKRAINIAN_ACTION, Qt::CaseInsensitive) == 0) return "uk_UA";
            if (language.compare(UI_CONSTANTS::MAIN_WINDOW::JAPANESE_ACTION, Qt::CaseInsensitive) == 0) return "ja_JP";
            if (language.compare(UI_CONSTANTS::MAIN_WINDOW::KOREAN_ACTION, Qt::CaseInsensitive) == 0) return "ko_KR";

            return "en_US";
        }
    }
}
