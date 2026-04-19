
#pragma once

#include <QApplication>
#include <QUrl>

namespace UI_CONSTANTS {
    namespace DOWNLOAD_CARD {
        inline constexpr int DEFAULT_SPACING_LAYOUT = 25;
        inline constexpr int DEFAULT_VALUE_PROGRESS_BAR = 0;
        inline constexpr int DURATION_ANIMATION = 4000;

        inline constexpr QPair TEXT_BROWSER_SIZE {0,30};
        inline constexpr QPair PROGRESS_BAR_SIZE {0,20};
        inline constexpr QPair RANGE_PROGRESS_BAR {0,1000};

        inline QString EDIT_BTN() {return QObject::tr("Edit");}
        inline QString REMOVE_BTN() {return QObject::tr("Remove");}

        inline const QByteArray DEFAULT_PROPERTY_NAME_PROGRESS_BAR = "value";

        inline const QString STYLE_TEXT_BROWSER = R"(
            QTextBrowser {background: transparent;}
            QScrollBar:horizontal {height: 0px;}
            QScrollBar:vertical {width: 0px;}
            QTextEdit {background: transparent;}
        )";

        inline const QString STYLE = R"(
            QProgressBar {
                border: none;
                background-color: #DADADA;
                min-height: 0px;
                height: 20px;
                border-radius: 10px;
                font-size: 10px;
            }

            QProgressBar::chunk {
                border-radius: 10px;
                background: qlineargradient(
                    x1: 0, y1: 0, x2: 1, y2: 0,
                    stop: 0 #4facfe,
                    stop: 1 #00f2fe
                );
            }

            QPushButton {
                color: #2c3e50;
                background-color: qlineargradient(
                    x1: 0, y1: 0, x2: 0, y2: 1,
                    stop: 0 #d6f0ff,
                    stop: 1 #a3d5f7
                );
                border: 1px solid #a3d5f7;
                border-radius: 8px;
                padding: 6px 12px;
                font-size: 12px;
                font-weight: bold;
            }

            QPushButton:hover {
                background-color: qlineargradient(
                    x1: 0, y1: 0, x2: 0, y2: 1,
                    stop: 0 #c0e0f0,
                    stop: 1 #89c2e0
                );
                border: 1px solid #89c2e0;
                color: #1c2e40;
            }

            QPushButton:pressed {
                background-color: qlineargradient(
                    x1: 0, y1: 0, x2: 0, y2: 1,
                    stop: 0 #89c2e0,
                    stop: 1 #a3d5f7
                );
                border: 1px solid #5ca6c8;
                color: #1c2e40;
            }

            QPushButton:disabled {
                color: #F2F2F2;
                background-color: #686868;
                border: 1px solid #cccccc;
            }
        )";
    }

    namespace DOWNLOAD_CONFIG {
        inline constexpr int DEFAULT_NEXT_ID = 0;
        inline constexpr int DEFAULT_SPACING_LAYOUT = 20;
        inline constexpr int WAIT_INTERVAL_FOR_URL_INPUTS = 1000;
        inline constexpr int WAIT_INTERVAL_FOR_I_TAGS_INPUT = 1200;
        inline constexpr int SLEEP_TIME = 1000;

        inline constexpr QPair WINDOW_SIZE {850, 650};
        inline constexpr QPair LINEEDIT_SIZE {600, 35};
        inline constexpr QPair OUTPUT_LAYOUT_LINEEDIT_SIZE {LINEEDIT_SIZE.first - 100, LINEEDIT_SIZE.second};
        inline constexpr QPair COMBO_SIZE {275, 25};

        inline QString GENERAL_INFORMATION() {return QObject::tr("General");}
        inline QString DOWNLOAD_CONFIG() {return QObject::tr("Config");}
        inline QString GENERAL_CONFIG() {return QObject::tr("General configuration");}
        inline QString LINK() {return QObject::tr("URL: ");}
        inline QString HINT_TEXT_URL_EDIT(){return QObject::tr("Input download address ...");}
        inline QString INVALID_LINK() {return QObject::tr("Invalid URL format");}
        inline QString WARNING() {return QObject::tr("Warning");}
        inline QString INVALID_URL(const QString& text) {return QObject::tr("Invalid URL: %1").arg(text);}
        inline QString TITLE() {return QObject::tr("Title: ");}
        inline QString TITLE_FAILED() {return QObject::tr("Failed");}
        inline QString MODE() {return QObject::tr("Mode: ");}
        inline QString BEST_AUDIO() {return QObject::tr("Best audio");}
        inline QString BEST_VIDEO() {return QObject::tr("Best video");}
        inline QString PERSONALIZED() {return QObject::tr("Personalized");}
        inline QString SHOW_I_TAGS() {return QObject::tr("Show itags");}
        inline QString AUDIO_I_TAG() {return QObject::tr("Audio Itag: ");}
        inline QString EXAMPLE_AUDIO_I_TAG() {return QObject::tr("Example: 251");}
        inline QString INVALID_AUDIO_I_TAG(const QString& text) {return QObject::tr("Unsupported audio itag: %1").arg(text);}
        inline QString REQUIRED_AUDIO_I_TAG() {return QObject::tr("At least one audio itag must be specified");}
        inline QString VIDEO_I_TAG() {return QObject::tr("Video Itag: ");}
        inline QString EXAMPLE_VIDEO_I_TAG() {return QObject::tr("Example: 401");}
        inline QString INVALID_VIDEO_I_TAG(const QString& text) {return QObject::tr("Unsupported video itag: %1").arg(text);}
        inline QString NON_STANDARD_VIDEO_I_TAG() {return QObject::tr("*Video Itag: ");}
        inline QString AI_UPSCALED_ONLY() {return QObject::tr("AI-Upscaled Only");}
        inline QString EXAMPLE_NON_STANDARD_VIDEO_I_TAG() {return QObject::tr("Example: 401-sr");}
        inline QString INVALID_NON_STANDARD_VIDEO_I_TAG(const QString& text) {return QObject::tr("Unsupported non-standard video itag: %1").arg(text);}
        inline QString CHOOSE_BETWEEN_VI_AND_VI_AI() {return QObject::tr("If you provide both a video itag and a video itag (AI upscaled), the AI‑upscaled option will be chosen by default\n\nAre you sure you want to proceed?");}
        inline QString METADATA_LAB() {return QObject::tr("Metadata: ");}
        inline QString WITHOUT_METADATA() {return QObject::tr("Without Metadata");}
        inline QString WITH_METADATA() {return QObject::tr("With Metadata");}
        inline QString SUBTITLE_LAB() {return QObject::tr("Subtitles: ");}
        inline QString WITHOUT_SUBTITLES() {return QObject::tr("Without Subtitles");}
        //inline QString WITH_SUBTITLES() {return QObject::tr("With Subtitles");}
        inline QString AUTO_GENERATED_SUBTITLES_LAB() {return QObject::tr("**Subtitles: ");}
        inline QString WITHOUT_AUTO_GENERATED_SUBTITLES() {return QObject::tr("Without Auto Generated Subtitles");}
        //inline QString WITH_AUTO_GENERATED_SUBTITLES() {return QObject::tr("With Auto Generated Subtitles");}
        inline QString SAVE_PATH() {return QObject::tr("Save path: ");}
        inline QString INVALID_SAVE_PATH() {return QObject::tr("Invalid Save Path");}
        inline QString INVALID_SAVE_NAME(const QString& text) {return QObject::tr("Invalid Save Name: %1\n\nwhich contains invalid characters").arg(text);}
        inline QString INVALID_FILE_PATH(const QString& text) {return QObject::tr("Invalid file path: %1\n\nwhich does not exist or lacks read/write permissions").arg(text);}
        inline QString INVALID_SUFFIX(const QString& text) {return QObject::tr("Invalid Suffix: %1 which is unsupported").arg(text);}
        inline QString OUTPUT() {return QObject::tr("Output");}
        inline QString SAVE_PATH_LAB() {return QObject::tr("Save path: ");}
        inline QString SAVE_AS() {return QObject::tr("Save as");}
        inline QString REQUIRED_URL() {return QObject::tr("A valid URL is required first");}
        inline QString ASK_FOR_SAVE_PATH() {return QObject::tr("After selecting the file save path, the previous options can no longer be modified\n\nThey can still be adjusted later via Main Interface → Widget\n\nAre you sure you want to proceed?");}
        inline QString CONFIRM() {return QObject::tr("Confirm");}

        inline const QString STYLE = R"(
            QDialog {
                background-color: qlineargradient(
                    x1: 0, y1: 0, x2: 1, y2: 1,
                    stop: 0 #a3d5f7,
                    stop: 0.5 #c0e0f0,
                    stop: 1 #a3d5f7
                );
                font-family: 'Segoe UI', 'Microsoft YaHei', sans-serif;
                font-size: 12px;
            }

            QLabel {
                color: #fdffea;
                font-weight: bold;
                font-size: 14px;
            }

            QLineEdit {
                background-color: #e5f4f6;
                color: #333333;
                border: 1px solid #cccccc;
                border-radius: 5px;
                padding: 6px;
                font-size: 12px;
            }

            QLineEdit:disabled {
                background-color: #525252;
                color: #F2F2F2;
            }

            QComboBox {
                border: 1px solid #a3d5f7;
                border-radius: 6px;
                padding: 4px 8px;
                background-color: #eaf6fc;
                color: #2c3e50;
                font-weight: bold;
            }

            QComboBox::drop-down {
                subcontrol-origin: padding;
                subcontrol-position: top right;
                width: 20px;
                border-left: 1px solid #a3d5f7;
                background-color: #d6f0ff;
                border-top-right-radius: 6px;
                border-bottom-right-radius: 6px;
            }

            QComboBox QAbstractItemView {
                background-color: #f0f8fc;
                border: 1px solid #a3d5f7;
                selection-background-color: #b5dff0;
                selection-color: #1c2e40;
                padding: 4px;
                outline: 0px;
            }

            QComboBox:disabled {
                color: #F2F2F2;
                background-color: #686868;
            }

            QComboBox:hover {
                background-color: #d6f0ff;
                border: 1px solid #89c2e0;
            }

            QComboBox:pressed {
                background-color: #b0d5eb;
                border: 1px solid #5ca6c8;
            }

            QPushButton {
                color: #2c3e50;
                background-color: qlineargradient(
                    x1: 0, y1: 0, x2: 0, y2: 1,
                    stop: 0 #d6f0ff,
                    stop: 1 #a3d5f7
                );
                border: 1px solid #a3d5f7;
                border-radius: 8px;
                padding: 6px 12px;
                font-size: 12px;
                font-weight: bold;
            }

            QPushButton:hover {
                background-color: qlineargradient(
                    x1: 0, y1: 0, x2: 0, y2: 1,
                    stop: 0 #c0e0f0,
                    stop: 1 #89c2e0
                );
                border: 1px solid #89c2e0;
                color: #1c2e40;
            }

            QPushButton:pressed {
                background-color: qlineargradient(
                    x1: 0, y1: 0, x2: 0, y2: 1,
                    stop: 0 #89c2e0,
                    stop: 1 #a3d5f7
                );
                border: 1px solid #5ca6c8;
                color: #1c2e40;
            }

            QPushButton:disabled {
                color: #F2F2F2;
                background-color: #686868;
                border: 1px solid #cccccc;
            }

            QGroupBox {
                border: 1px solid #a3d5f7;
                border-radius: 6px;
                margin-top: 10px;
                padding: 10px;
                font-weight: bold;
                color: #2c3e50;
            }

            QGroupBox::title {
                subcontrol-origin: margin;
                left: 10px;
                padding: 0 4px;
                background-color: transparent;
            }

            QFormLayout > QLabel {
                min-width: 80px;
            }

            QFrame {
                border: none;
            }

            QFrame[frameShape="4"] { /* HLine */
                border: 1px solid #a3d5f7;
            }

            QFrame[frameShape="5"] { /* VLine */
                border-left: 1px solid #a3d5f7;
            }

            QListView, QTreeView {
                background-color: #dff0fa;
                color: #2c3e50;
                border: 1px solid #a3d5f7;
                border-radius: 6px;
            }

            QListView::item:selected, QTreeView::item:selected {
                background-color: #a3d5f7;
                color: #1c2e40;
                border-radius: 4px;
            }

            QListView::item:hover, QTreeView::item:hover {
                background-color: #c0e0f0;
                border-radius: 4px;
            }

            QHeaderView::section {
                background-color: #cde7f5;
                color: #2c3e50;
                border: 1px solid #a3d5f7;
                padding: 4px;
                font-weight: bold;
            }

            QToolButton {
                background-color: transparent;
                color: #2c3e50;
                border: none;
                border-radius: 5px;
                padding: 4px;
            }

            QToolButton:hover {
                background-color: #c0e0f0;
                border: 1px solid #a3d5f7;
            }

            QToolButton:pressed {
                background-color: #a3d5f7;
            }

            QListWidget {
                background-color: #cde7f5;
                color: #2c3e50;
                border: none;
                border-right: 1px solid #a3d5f7;
            }

            QListWidget::item:selected {
                background-color: #a3d5f7;
                color: #1c2e40;
                border-radius: 4px;
            }

            QListWidget::item:hover {
                background-color: #c0e0f0;
                border-radius: 4px;
            }

            QScrollBar:vertical, QScrollBar:horizontal {
                background: #d6f0ff;
                width: 8px;
                height: 8px;
                border-radius: 4px;
                margin: 0px;
            }

            QScrollBar::handle:vertical, QScrollBar::handle:horizontal {
                background: #a3d5f7;
                border-radius: 4px;
                min-height: 20px;
                min-width: 20px;
            }

            QScrollBar::handle:hover {
                background: #89c2e0;
            }

            QScrollBar::add-line, QScrollBar::sub-line {
                height: 0px;
                width: 0px;
            }
        )";
    }

    namespace GLASS_WIDGET {
        inline constexpr int PEN_WIDTH = 2;
        inline constexpr int BLUR_RADIUS = 40;
        inline constexpr double DIVISOR_HIGHLIGHT_Y_FINAL_STOP = 2.0;

        inline const QVector Q_RECT_ADJUSTED = {2,2,-2,-2};
        inline const QVector HIGHLIGHTS_START = {0,0,0};

        inline constexpr QPair RADIUS_DRAW_ROUNDED_RECT = {20,20};
        inline constexpr QPair HIGHLIGHT_POS = {0.0,1.0};

        inline constexpr QColor COLOR_PAINT_SET_BRUSH_1 = {0,0,0,60};
        inline constexpr QColor COLOR_PAINT_SET_BRUSH_2 = {250,250,250,80};
        inline constexpr QColor COLOR_PEN_SET_BRUSH = {250,250,250,180};
        inline constexpr QColor COLOR_HIGHLIGHT_1 = {255,255,255,150};
        inline constexpr QColor COLOR_HIGHLIGHT_2 = {255,255,255,0};
    }

    namespace MAIN_CPP {
        inline constexpr int WAIT_FOR_SOCKET_CONNECT = 200;
        inline constexpr int WAIT_FOR_BYTES_WRITTEN = 200;

        inline const QString APP_NAME = "Youtube Media Downloader";
        inline const QByteArray KEY_MSG = "show";

        inline QString CRITICAL() {return QObject::tr("Critical");}
        inline QString CAN_NOT_EXECUTE() {return QObject::tr("All three program paths are required\n\nThe application cannot proceed without them\n\nPlease try again later or contact the developer");}
    }

    namespace MAIN_WINDOW {
        inline constexpr int SPACING_BUTTON_LAYOUT = 100;
        inline constexpr int SPACING_LIST_WIDGET = 0;
        inline constexpr int WAIT_INTERVAL_CLIENT = 1000;
        inline constexpr int DEFAULT_ERROR_SERVER_PORT = -1;

        inline constexpr QPair WINDOW_SIZE {800,600};
        inline const QList CONTENTS_MARGINS_SIZE {50,10,50,10};

        inline QString WINDOW_TITLE() {return QObject::tr("Media Downloader (Official Release v1.0.0)");}

        inline QString FILE_MENU() {return QObject::tr("File");}
        inline QString LANGUAGE_MENU() {return QObject::tr("Language");}
        inline QString PREFERENCES_MENU() {return QObject::tr("Preferences");}
        inline QString HELP_MENU() {return QObject::tr("Help");}
        inline QString IMPORT_DATA() {return QObject::tr("Import data");}
        inline QString FAILED_IMPORT_DATA() {return QObject::tr("Failed to import data");}
        inline QString FAILED_APPEND_DATA_LIST() {return QObject::tr("To import data, you need to clear the list first");}
        inline QString SUCCESS_IMPORT_DATA() {return QObject::tr("Successfully imported data");}
        inline QString EXPORT_DATA() {return QObject::tr("Export data");}
        inline QString FAILED_EXPORT_DATA() {return QObject::tr("Failed to export data");}
        inline QString SUCCESS_EXPORT_DATA() {return QObject::tr("Successfully exported data");}
        inline QString CLEAR_DOWNLOAD_STATUS() {return QObject::tr("Clear download status");}
        inline QString QUIT_ACTION() {return QObject::tr("Quit");}
        inline QString FAILED_CHANGE_LANGUAGE(const QString& language) {return QObject::tr("Failed to change language: %1").arg(language);}
        inline QString GENERAL_ACTION() {return QObject::tr("General");}
        inline QString HELP_CONTENTS_ACTION() {return QObject::tr("Help Documentation");}
        inline QString CHECK_FOR_UPDATES_ACTION() {return QObject::tr("Check for updates");}
        inline QString REPORT_ISSUES_ACTION() {return QObject::tr("Report issues");}

        inline QString START_BTN() {return QObject::tr("Start");}
        inline QString STOP_BTN() {return QObject::tr("Stop");}
        inline QString ADD_BTN() {return QObject::tr("Add new download");}
        inline QString REMOVE_BTN() {return QObject::tr("Remove all downloads");}

        inline QString SUCCESS() {return QObject::tr("Success");}
        inline QString FAILED() {return QObject::tr("Failed");}
        inline QString SAVE() {return QObject::tr("Save");}
        inline QString CHANGE_SUCCESS() {return QObject::tr("Successfully changed");}

        inline QString CONFIRMATION() {return QObject::tr("Confirmation");}
        inline QString INFORMATION() {return QObject::tr("Information");}
        inline QString WARNING() {return QObject::tr("Warning");}
        inline QString CRITICAL() {return QObject::tr("Critical");}

        inline QString QUIT_APP() {return QObject::tr("Quit App");}
        inline QString ASK_IF_QUIT_APP() {return QObject::tr("Are you sure you want to quit?");}
        inline QString STOP_ALL() {return QObject::tr("Stop All");}
        inline QString ASK_IF_STOP_ALL() {return QObject::tr("Are you sure you want to stop all downloads?");}
        inline QString DB_SERVER_FAILED() {return QObject::tr("Db Server can not open\n\nPlease contact with the developer");}
        inline QString CONFIRM_DELETION() {return QObject::tr("Confirm deletion?");}
        inline QString CRYPTO_INIT_FAILED() {return QObject::tr("Failed to initialize crypto module\n\nCan not import data o export data");}
        inline QString UNNORMAL_EXIT_DOWNLOAD(const QString& name, const QString& title) {return QObject::tr("Download paused: %1\n\nwhich title is: %2").arg(name, title);}

        inline QStringList GET_TRANSLATION_PATH() {
            #if defined(Q_OS_MACOS)
                const QString translationPath = QCoreApplication::applicationDirPath() + "/../Resources/translations";
            #elif defined(Q_OS_WIN)
                const QString translationPath = QCoreApplication::applicationDirPath() + "/translations";
            #else
                const QString translationPath = QCoreApplication::applicationDirPath() + "/translations";
            #endif

            const QStringList searchPaths = {
                translationPath,
                "../translations",
                "../../translations",
                ":/translations",
            };

            return searchPaths;
        }

        inline const QString ENGLISH_ACTION = "English";
        inline const QString CHINESE_ACTION = "中文";
        inline const QString CHINESE_TRADITIONAL_ACTION = "繁體中文";
        inline const QString SPANISH_ACTION = "Español";
        inline const QString PORTUGUESE_ACTION = "Português";
        inline const QString FRENCH_ACTION = "Français";
        inline const QString GERMAN_ACTION = "Deutsch";
        inline const QString ITALIAN_ACTION = "Italiano";
        inline const QString ARABIC_ACTION = "العربية";
        inline const QString RUSSIAN_ACTION = "Русский";
        inline const QString UKRAINIAN_ACTION = "Українська";
        inline const QString JAPANESE_ACTION = "日本語";
        inline const QString KOREAN_ACTION = "한국어";

        inline const QString POINT = ".";
        inline const QString DEFAULT_EXPORTED_DATA_NAME = "appData";
        inline const QString DEFAULT_DATA_SUFFIX = ".dat";
        inline QString DEFAULT_DATA_FILTER() {return QObject::tr("DATA (*.dat);;");}

        inline const auto URL_REPO = QUrl("https://github.com/Rafael-l-m/Youtube-Media-Downloader");
        inline const auto URL_REPORT_ISSUES = QUrl("https://github.com/Rafael-l-m/Youtube-Media-Downloader/issues/new");

        inline const QString STYLE = R"(
            QMainWindow {
                background-color: qlineargradient(
                    x1: 0, y1: 0, x2: 1, y2: 1,
                    stop: 0 #a3d5f7,
                    stop: 0.5 #c0e0f0,
                    stop: 1 #a3d5f7
                );
            }

            QMenu {
                background-color: #e3f3fc;
                color: #2c3e50;
                border: 1px solid #a3d5f7;
                border-radius: 6px;
            }

            QMenu::item {
                padding: 6px 20px;
                border-radius: 4px;
            }

            QMenu::item:selected {
                background-color: #b5dff0;
                color: #1c2e40;
            }

            QMenu::right-arrow {
                image: none;
            }

            QMenuBar {
                background-color: #cde7f5;
                color: #2c3e50;
                border-bottom: 1px solid #a3d5f7;
                font-weight: bold;
                padding: 4px;
            }

            QMenuBar::item {
                background: transparent;
                padding: 6px 12px;
                border-radius: 6px;
            }

            QMenuBar::item:selected {
                background-color: #a3d5f7;
                color: #1c2e40;
            }

            QPushButton {
                color: #2c3e50;
                background-color: qlineargradient(
                    x1: 0, y1: 0, x2: 0, y2: 1,
                    stop: 0 #d6f0ff,
                    stop: 1 #a3d5f7
                );
                border: 1px solid #a3d5f7;
                border-radius: 8px;
                padding: 6px 12px;
                font-size: 12px;
                font-weight: bold;
            }

            QPushButton:hover {
                background-color: qlineargradient(
                    x1: 0, y1: 0, x2: 0, y2: 1,
                    stop: 0 #c0e0f0,
                    stop: 1 #89c2e0
                );
                border: 1px solid #89c2e0;
                color: #1c2e40;
            }

            QPushButton:pressed {
                background-color: qlineargradient(
                    x1: 0, y1: 0, x2: 0, y2: 1,
                    stop: 0 #89c2e0,
                    stop: 1 #a3d5f7
                );
                border: 1px solid #5ca6c8;
                color: #1c2e40;
            }

            QPushButton:disabled {
                color: #a0b0bb;
                background-color: qlineargradient(
                    x1: 0, y1: 0, x2: 0, y2: 1,
                    stop: 0 #e8f4fb,
                    stop: 1 #cce5f5
                );
                border: 1px solid #cce5f5;
                border-radius: 8px;
                padding: 6px 12px;
                font-size: 12px;
                font-weight: bold;
            }

            QScrollArea {
                background-color: #b8def1;
                border: 1px solid #a3d5f7;
                border-radius: 8px;
            }

            QScrollBar:vertical {
                background: #d6f0ff;
                width: 12px;
                margin: 2px;
                border-radius: 6px;
            }

            QScrollBar::handle:vertical {
                background: #a3d5f7;
                border-radius: 6px;
                min-height: 20px;
            }

            QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
                background: none;
                height: 0px;
            }

            QScrollArea QWidget {
                background-color: #b8def1;
                border: none;
            }

            QListWidget {
                background-color: #b8def1;
                border: 1px solid #a3d5f7;
                border-radius: 8px;
            }

            QListWidget::item {
                background-color: transparent;
                padding: 6px;
                border-bottom: 1px solid #a3d5f7;
            }

            QListWidget::item:selected {
                background-color: #a3d5f7;
                color: #1c2e40;
            }
        )";

        namespace Q_LIST_WIDGET {
            inline constexpr int PAGE_SIZE = 50;
            inline constexpr int DIFFERENCE_PAGES = 3;
            inline constexpr QPair ITEM_SIZE {0, 65};
        }
    }

    namespace NOTICE_VIEW {
        inline constexpr QPair SHOW_ICON_SIZE {50,50};

        inline QString YES_BTN() {return QObject::tr("OK");}
        inline QString NO_BTN() {return QObject::tr("No");}

        inline QString RESOURCES_PATH() {
            const auto EXECUTABLE_PATH = QCoreApplication::applicationDirPath();

            #ifdef Q_OS_MAC
                const auto RESOURCES_PATH = EXECUTABLE_PATH + "/../Resources/icons";
            #elif defined(Q_OS_WIN)
                const auto RESOURCES_PATH = EXECUTABLE_PATH + "/resources/icons";
            #elif defined(Q_OS_LINUX)
                const auto RESOURCES_PATH = EXECUTABLE_PATH + "/resources/icons";
            #endif

            return RESOURCES_PATH;
        }

        inline const QString ICON_NAME = "Video.png";
        inline const QString PIC_CONFIRM_NAME = "Confirmation.png";
        inline const QString PIC_INFORM_NAME = "Information.png";
        inline const QString PIC_WARN_NAME = "Warning.png";
        inline const QString PIC_CRITIC_NAME = "Critical.png";

        inline const QString STYLE = R"(
            QDialog {
                background-color: #ffffff;
            }

            QLabel {
                font-size: 13px;
            }

            QPushButton {
                color: #2c3e50;
                background-color: qlineargradient(
                    x1: 0, y1: 0, x2: 0, y2: 1,
                    stop: 0 #d6f0ff,
                    stop: 1 #a3d5f7
                );
                border: 1px solid #a3d5f7;
                border-radius: 8px;
                padding: 6px 12px;
                font-size: 10px;
                font-weight: bold;
            }

            QPushButton:hover {
                background-color: qlineargradient(
                    x1: 0, y1: 0, x2: 0, y2: 1,
                    stop: 0 #c0e0f0,
                    stop: 1 #89c2e0
                );
                border: 1px solid #89c2e0;
                color: #1c2e40;
            }

            QPushButton:pressed {
                background-color: qlineargradient(
                    x1: 0, y1: 0, x2: 0, y2: 1,
                    stop: 0 #89c2e0,
                    stop: 1 #a3d5f7
                );
                border: 1px solid #5ca6c8;
                color: #1c2e40;
            }

            QPushButton:disabled {
                color: #F2F2F2;
                background-color: #686868;
                border: 1px solid #cccccc;
            }
        )";
    }

    namespace SETTINGS_VIEW {
        inline constexpr bool DEFAULT_IF_AUDIO = true;

        inline constexpr QPair WINDOW_SIZE {750,450};
        inline constexpr QPair LINEEDIT_SIZE {450,25};
        inline constexpr QPair GRID_FIXED_SPACING {20,20};

        inline QString YT_DLP() {
            #ifdef Q_OS_WIN
                return "yt-dlp.exe";
            #else
                return "yt-dlp";
            #endif
        }

        inline QString FFMPEG() {
            #ifdef Q_OS_WIN
                return "ffmpeg.exe";
            #else
                return "ffmpeg";
            #endif
        }

        inline QString NODE_JS() {
            #ifdef Q_OS_WIN
                return "node.exe";
            #else
                return "node";
            #endif
        }

        inline QString FILTER() {
            #ifdef Q_OS_MAC
                return QObject::tr("Executable File(*);;App Store File(*.app)");
            #elif defined(Q_OS_WIN)
                return QObject::tr("Executable File(*.exe)");
            #elif defined(Q_OS_LINUX)
                return QObject::tr("Executable File(*)");
            #endif
        }

        inline QString WINDOW_TITLE() {return QObject::tr("Preferences");}
        inline QString TOOLS_BOX() {return QObject::tr("Tools");}
        inline QString YT_DLP_LAB() {return QObject::tr("yt-dlp: ");}
        inline QString CHOOSE_YT_DLP() {return QObject::tr("Choose yt-dlp");}
        inline QString FFMPEG_LAB() {return QObject::tr("ffmpeg: ");}
        inline QString CHOOSE_FFMPEG() {return QObject::tr("Choose ffmpeg");}
        inline QString NODE_LAB() {return QObject::tr("node.js: ");}
        inline QString CHOOSE_NODE() {return QObject::tr("Choose node");}
        inline QString SEARCH_LAB() {return QObject::tr("Search");}
        inline QString SAVE_BTN() {return QObject::tr("Save");}

        inline QString SUCCESS() {return QObject::tr("Success");}
        inline QString FAILED() {return QObject::tr("Failed");}
        inline QString ERROR() {return QObject::tr("Error");}
        inline QString TITLE_MODIFY() {return QObject::tr("Modify Executable File Path");}
        inline QString CONTENT_MODIFY() {return QObject::tr("The program has detected the executable file path\n\nDo you wish to modify it?");}
        inline QString CONTENT_CHANGED_CORRECTLY_PATH() {return QObject::tr("Path changed correctly");}
        inline QString CONTENT_FAILED_CHANGE_PATH() {return QObject::tr("Invalid executable file.\n\nPlease try again");}
        inline QString TOOL_PATH_MUST_BE_PROVIDED() {return QObject::tr("All three tool paths must be provided");}
        inline QString CONFIG_SAVED_CORRECTLY() {return QObject::tr("Settings saved successfully");}
        inline QString CONFIG_SAVED_FAILED() {return QObject::tr("Oops, something went wrong\n\nPlease try again later");}

        inline const QString STYLE = R"(
            QDialog {
                background-color: qlineargradient(
                    x1: 0, y1: 0, x2: 1, y2: 1,
                    stop: 0 #a3d5f7,
                    stop: 0.5 #c0e0f0,
                    stop: 1 #a3d5f7
                );
                font-family: 'Segoe UI', 'Microsoft YaHei', sans-serif;
                font-size: 10px;
            }

            QLabel {
                color: #fdffea;
                font-weight: bold;
                font-size: 12px;
            }

            QLineEdit {
                background-color: #e5f4f6;
                color: #333333;
                border: 1px solid #cccccc;
                border-radius: 5px;
                padding: 6px;
                font-size: 10px;
            }

            QLineEdit:disabled {
                background-color: #525252;
                color: #F2F2F2;
            }

            QPushButton {
                color: #2c3e50;
                background-color: qlineargradient(
                    x1: 0, y1: 0, x2: 0, y2: 1,
                    stop: 0 #d6f0ff,
                    stop: 1 #a3d5f7
                );
                border: 1px solid #a3d5f7;
                border-radius: 8px;
                padding: 6px 12px;
                font-size: 10px;
                font-weight: bold;
            }

            QPushButton:hover {
                background-color: qlineargradient(
                    x1: 0, y1: 0, x2: 0, y2: 1,
                    stop: 0 #c0e0f0,
                    stop: 1 #89c2e0
                );
                border: 1px solid #89c2e0;
                color: #1c2e40;
            }

            QPushButton:pressed {
                background-color: qlineargradient(
                    x1: 0, y1: 0, x2: 0, y2: 1,
                    stop: 0 #89c2e0,
                    stop: 1 #a3d5f7
                );
                border: 1px solid #5ca6c8;
                color: #1c2e40;
            }

            QPushButton:disabled {
                color: #F2F2F2;
                background-color: #686868;
                border: 1px solid #cccccc;
            }
        )";
    }

    namespace SHOW_I_TAGS {
        inline constexpr QPair WINDOW_SIZE {1000,450};

        inline QString TITLE() {return QObject::tr("Show Itags");}

        inline const QString FONT = "Courier New";
        inline const QString PATH = "PATH";

        inline const QString STYLE = R"(
            QPlainTextEdit {
                background-color: qlineargradient(
                    x1: 0, y1: 0, x2: 1, y2: 1,
                    stop: 0 #a3d5f7,
                    stop: 0.5 #c0e0f0,
                    stop: 1 #a3d5f7
                );
                font-size: 14px;
                color: #4B0082;
            }
        )";
    }
}
