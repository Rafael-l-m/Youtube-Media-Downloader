
#include "constants/Update_Constants.hpp"
#include "core/BasicTools.hpp"
#include "core/SharedStorage.hpp"
#include "ui/DownloadConfig.hpp"
#include "ui/MainWindow.hpp"
#include "ui/NoticeView.hpp"
#include "ui/SettingsView.hpp"
#include <QCloseEvent>
#include <QDesktopServices>
#include <QFileDialog>
#include <QMenuBar>
#include <QScrollBar>
#include <QTimer>

namespace UI {
    // Public

    MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), serverPort(UI_CONSTANTS::MAIN_WINDOW::DEFAULT_ERROR_SERVER_PORT) {
        // MenuBar
        this->bar = this->menuBar();

        this->fileMenu = this->bar->addMenu(UI_CONSTANTS::MAIN_WINDOW::FILE_MENU());
        this->importDownloadListAction = new QAction(UI_CONSTANTS::MAIN_WINDOW::IMPORT_DATA(), this);
        this->exportDownloadListAction = new QAction(UI_CONSTANTS::MAIN_WINDOW::EXPORT_DATA(), this);
        this->clearStatusAction = new QAction(UI_CONSTANTS::MAIN_WINDOW::CLEAR_DOWNLOAD_STATUS(), this);
        this->quitAction = new QAction(UI_CONSTANTS::MAIN_WINDOW::QUIT_ACTION(), this);
        this->fileMenu->addAction(this->importDownloadListAction);
        this->fileMenu->addAction(this->exportDownloadListAction);
        this->fileMenu->addAction(this->clearStatusAction);
        this->fileMenu->addAction(this->quitAction);

        this->languageMenu = this->bar->addMenu(UI_CONSTANTS::MAIN_WINDOW::LANGUAGE_MENU());
        this->englishAction = new QAction(UI_CONSTANTS::MAIN_WINDOW::ENGLISH_ACTION, this);
        this->chineseAction = new QAction(UI_CONSTANTS::MAIN_WINDOW::CHINESE_ACTION, this);
        this->chineseTraditionalAction = new QAction(UI_CONSTANTS::MAIN_WINDOW::CHINESE_TRADITIONAL_ACTION, this);
        this->spanishAction = new QAction(UI_CONSTANTS::MAIN_WINDOW::SPANISH_ACTION, this);
        this->portugueseAction = new QAction(UI_CONSTANTS::MAIN_WINDOW::PORTUGUESE_ACTION, this);
        this->frenchAction = new QAction(UI_CONSTANTS::MAIN_WINDOW::FRENCH_ACTION, this);
        this->germanAction = new QAction(UI_CONSTANTS::MAIN_WINDOW::GERMAN_ACTION, this);
        this->italianAction = new QAction(UI_CONSTANTS::MAIN_WINDOW::ITALIAN_ACTION, this);
        this->arabicAction = new QAction(UI_CONSTANTS::MAIN_WINDOW::ARABIC_ACTION, this);
        this->russianAction = new QAction(UI_CONSTANTS::MAIN_WINDOW::RUSSIAN_ACTION, this);
        this->ukrainianAction = new QAction(UI_CONSTANTS::MAIN_WINDOW::UKRAINIAN_ACTION, this);
        this->japaneseAction = new QAction(UI_CONSTANTS::MAIN_WINDOW::JAPANESE_ACTION, this);
        this->koreanAction = new QAction(UI_CONSTANTS::MAIN_WINDOW::KOREAN_ACTION, this);
        this->languageMenu->addAction(this->englishAction);
        this->languageMenu->addAction(this->chineseAction);
        this->languageMenu->addAction(this->chineseTraditionalAction);
        this->languageMenu->addAction(this->spanishAction);
        this->languageMenu->addAction(this->portugueseAction);
        this->languageMenu->addAction(this->frenchAction);
        this->languageMenu->addAction(this->germanAction);
        this->languageMenu->addAction(this->italianAction);
        this->languageMenu->addAction(this->arabicAction);
        this->languageMenu->addAction(this->russianAction);
        this->languageMenu->addAction(this->ukrainianAction);
        this->languageMenu->addAction(this->japaneseAction);
        this->languageMenu->addAction(this->koreanAction);

        this->preferencesMenu = this->bar->addMenu(UI_CONSTANTS::MAIN_WINDOW::PREFERENCES_MENU());
        this->generalAction = new QAction(UI_CONSTANTS::MAIN_WINDOW::GENERAL_ACTION(), this);
        this->preferencesMenu->addAction(this->generalAction);

        this->helpMenu = this->bar->addMenu(UI_CONSTANTS::MAIN_WINDOW::HELP_MENU());
        this->helpContentsAction = new QAction(UI_CONSTANTS::MAIN_WINDOW::HELP_CONTENTS_ACTION(), this);
        this->checkForUpdatesAction = new QAction(UI_CONSTANTS::MAIN_WINDOW::CHECK_FOR_UPDATES_ACTION(), this);
        this->reportIssuesAction = new QAction(UI_CONSTANTS::MAIN_WINDOW::REPORT_ISSUES_ACTION(), this);
        this->helpMenu->addAction(this->helpContentsAction);
        this->helpMenu->addAction(this->checkForUpdatesAction);
        this->helpMenu->addAction(this->reportIssuesAction);

        //this->menuBar()->setNativeMenuBar(false);

        // Widgets
        this->central = new QWidget(this);
        this->mainLayout = new QVBoxLayout(this->central);

        // Row 1
        this->topButtonLayout = new QHBoxLayout;

        this->startBtn = new QPushButton(UI_CONSTANTS::MAIN_WINDOW::START_BTN(), this);
        this->stopBtn = new QPushButton(UI_CONSTANTS::MAIN_WINDOW::STOP_BTN(), this);

        this->topButtonLayout->addWidget(this->startBtn);
        this->topButtonLayout->addWidget(this->stopBtn);
        this->topButtonLayout->setSpacing(UI_CONSTANTS::MAIN_WINDOW::SPACING_BUTTON_LAYOUT);
        this->topButtonLayout->setContentsMargins(UI_CONSTANTS::MAIN_WINDOW::CONTENTS_MARGINS_SIZE[0], UI_CONSTANTS::MAIN_WINDOW::CONTENTS_MARGINS_SIZE[1], UI_CONSTANTS::MAIN_WINDOW::CONTENTS_MARGINS_SIZE[2], UI_CONSTANTS::MAIN_WINDOW::CONTENTS_MARGINS_SIZE[3]);

        // Row 2
        this->listWidget = new QListWidget(this);
        this->listWidget->setSpacing(UI_CONSTANTS::MAIN_WINDOW::SPACING_LIST_WIDGET);
        this->listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        this->listWidget->setResizeMode(QListView::Adjust);
        this->listWidget->clear();

        // Row 3
        this->bottomButtonLayout = new QHBoxLayout;

        this->addBtn = new QPushButton(UI_CONSTANTS::MAIN_WINDOW::ADD_BTN(), this);
        this->removeBtn = new QPushButton(UI_CONSTANTS::MAIN_WINDOW::REMOVE_BTN(), this);

        this->bottomButtonLayout->addStretch();
        this->bottomButtonLayout->addWidget(this->addBtn);
        this->bottomButtonLayout->addStretch();
        this->bottomButtonLayout->addWidget(this->removeBtn);
        this->bottomButtonLayout->addStretch();
        this->bottomButtonLayout->setSpacing(UI_CONSTANTS::MAIN_WINDOW::SPACING_BUTTON_LAYOUT);
        this->bottomButtonLayout->setContentsMargins(UI_CONSTANTS::MAIN_WINDOW::CONTENTS_MARGINS_SIZE[0], UI_CONSTANTS::MAIN_WINDOW::CONTENTS_MARGINS_SIZE[1], UI_CONSTANTS::MAIN_WINDOW::CONTENTS_MARGINS_SIZE[2], UI_CONSTANTS::MAIN_WINDOW::CONTENTS_MARGINS_SIZE[3]);

        // Widgets
        this->mainLayout->addLayout(this->topButtonLayout);
        this->mainLayout->addWidget(this->listWidget);
        this->mainLayout->addLayout(this->bottomButtonLayout);

        // Settings
        this->setCentralWidget(this->central);
        this->setWindowIcon(QIcon(UI_CONSTANTS::NOTICE_VIEW::RESOURCES_PATH() + QDir::separator() + UI_CONSTANTS::NOTICE_VIEW::ICON_NAME));
        this->setWindowTitle(UI_CONSTANTS::MAIN_WINDOW::WINDOW_TITLE());
        this->resize(UI_CONSTANTS::MAIN_WINDOW::WINDOW_SIZE.first, UI_CONSTANTS::MAIN_WINDOW::WINDOW_SIZE.second);
        this->setStyleSheet(UI_CONSTANTS::MAIN_WINDOW::STYLE);

        // Update Checker
        this->updateChecker = new UPDATE::UpdateChecker(this);

        // Download Manager
        this->downloadManager = new DOWNLOAD_DOWNLOAD_MANAGER::DownloadManager(this);

        // Signals && Slots
        connect(this, &MainWindow::loadHistories, this, &MainWindow::handleLoadHistories);
        connect(this, &MainWindow::quitApp, qApp, &QApplication::quit);
        connect(this, &MainWindow::restartAppRequest, this, &MainWindow::restartApp);
        connect(this->importDownloadListAction, &QAction::triggered, this, &MainWindow::handleImportData);
        connect(this->exportDownloadListAction, &QAction::triggered, this, &MainWindow::handleExportData);
        connect(this->clearStatusAction, &QAction::triggered, this, &MainWindow::handleClearStatus);
        connect(this->quitAction, &QAction::triggered, qApp, &QApplication::quit);
        connect(this->englishAction, &QAction::triggered, this, &MainWindow::onActionTriggered);
        connect(this->chineseAction, &QAction::triggered, this, &MainWindow::onActionTriggered);
        connect(this->chineseTraditionalAction, &QAction::triggered, this, &MainWindow::onActionTriggered);
        connect(this->spanishAction, &QAction::triggered, this, &MainWindow::onActionTriggered);
        connect(this->portugueseAction, &QAction::triggered, this, &MainWindow::onActionTriggered);
        connect(this->frenchAction, &QAction::triggered, this, &MainWindow::onActionTriggered);
        connect(this->germanAction, &QAction::triggered, this, &MainWindow::onActionTriggered);
        connect(this->italianAction, &QAction::triggered, this, &MainWindow::onActionTriggered);
        connect(this->arabicAction, &QAction::triggered, this, &MainWindow::onActionTriggered);
        connect(this->russianAction, &QAction::triggered, this, &MainWindow::onActionTriggered);
        connect(this->ukrainianAction, &QAction::triggered, this, &MainWindow::onActionTriggered);
        connect(this->japaneseAction, &QAction::triggered, this, &MainWindow::onActionTriggered);
        connect(this->koreanAction, &QAction::triggered, this, &MainWindow::onActionTriggered);
        connect(this->generalAction, &QAction::triggered, this, &MainWindow::configuration);
        connect(this->helpContentsAction, &QAction::triggered, this, []() {QDesktopServices::openUrl(UI_CONSTANTS::MAIN_WINDOW::URL_REPO);});
        connect(this->checkForUpdatesAction, &QAction::triggered, this->updateChecker, &UPDATE::UpdateChecker::check);
        connect(this->reportIssuesAction, &QAction::triggered, this, []() {QDesktopServices::openUrl(UI_CONSTANTS::MAIN_WINDOW::URL_REPORT_ISSUES);});
        connect(this->addBtn, &QPushButton::clicked, this, &MainWindow::addTask);
        connect(this->removeBtn, &QPushButton::clicked, this, &MainWindow::removeAll);
        connect(this->startBtn, &QPushButton::clicked, this, &MainWindow::handleStartRequest);
        connect(this->stopBtn, &QPushButton::clicked, this, &MainWindow::handleStopRequest);
        connect(this->listWidget->verticalScrollBar(), &QScrollBar::valueChanged, this, [this](const int value) {this->pageChanged(value);});

        QTimer::singleShot(0, this, &MainWindow::startInitialization);
    }


    // Protected

    void MainWindow::closeEvent(QCloseEvent* event) {!this->m_isRestarting ? (NoticeView::confirmation(UI_CONSTANTS::MAIN_WINDOW::QUIT_APP(), UI_CONSTANTS::MAIN_WINDOW::ASK_IF_QUIT_APP()) ? event->accept() : event->ignore()) : event->accept();}


    // Private Slots

    void MainWindow::startInitialization() {
        // Start Server
        if (!this->dbServer.start()) {
            NoticeView::warning(UI_CONSTANTS::MAIN_WINDOW::FAILED(), UI_CONSTANTS::MAIN_WINDOW::DB_SERVER_FAILED());
            this->m_isRestarting = true;
            emit quitApp();
        }

        else {
            this->serverPort = this->dbServer.getPort();
            this->dbClient = new DB::DbClient(this->serverPort, this);

            // Load Histories
            this->dbClient->readAllDownloads([&](const QJsonObject& resp) {
                if (resp[DB_CONSTANTS::JSON_FORMAT::STATUS].toString().compare(DB_CONSTANTS::JSON_FORMAT::STATUS_OK) == 0) {
                    const auto tmp = resp[DB_CONSTANTS::JSON_FORMAT::PARAMETERS].toObject();
                    const auto d = CONTAINER::Download::fromJsonList(tmp);
                    emit loadHistories(d);
                }
            });

            // Update Checker
            connect(this->updateChecker, &UPDATE::UpdateChecker::updateAvailable, this, [](const QString& version, const QString& notes, const QString& url) {
                NoticeView::information(UPDATE_CONSTANTS::UPDATE_CHECKER::UPDATE_AVAILABLE(), UPDATE_CONSTANTS::UPDATE_CHECKER::UPDATE_INFORMATION(version, notes));
                QDesktopServices::openUrl(url);
            });

            connect(this->updateChecker, &UPDATE::UpdateChecker::noUpdate, this, []() {NoticeView::information(UPDATE_CONSTANTS::UPDATE_CHECKER::NO_UPDATE(), UPDATE_CONSTANTS::UPDATE_CHECKER::INFO_NO_UPDATE());});

            connect(this->updateChecker, &UPDATE::UpdateChecker::checkFailed, this, [](const QString& err) {NoticeView::information(UPDATE_CONSTANTS::UPDATE_CHECKER::FAILED_UPDATE(), err);});

            // Crypt
            if (!this->crypto.init()) NoticeView::warning(UI_CONSTANTS::MAIN_WINDOW::FAILED(), UI_CONSTANTS::MAIN_WINDOW::CRYPTO_INIT_FAILED());

            // Download Manager
            connect(this->downloadManager, &DOWNLOAD_DOWNLOAD_MANAGER::DownloadManager::downloadProgress, this, [this](const int idd, const int prog) {
                CORE::SharedStorage::instance().getDownload(idd)->setProgress(prog);
                this->dbClient->updateProgress(idd, prog, [](const QJsonObject&){});

                if (prog == 1000) {
                    CORE::SharedStorage::instance().getDownload(idd)->setDownloadState(true);
                    this->dbClient->updateDownloadState(idd, true, [](const QJsonObject&){});
                }

                const auto* widget = this->widgetsIndex.value(idd, nullptr);

                if (!widget) return;

                widget->disableButtons();
                widget->setProgress(prog);
            });

            connect(this->downloadManager, &DOWNLOAD_DOWNLOAD_MANAGER::DownloadManager::downloadNormalFinished, this, [this](const int idd) {
                this->dbClient->updateDownloadState(idd, true, [](const QJsonObject&){});

                const auto* widget = this->widgetsIndex.value(idd, nullptr);

                if (!widget) return;

                widget->enableButtons();
            });

            connect(this->downloadManager, &DOWNLOAD_DOWNLOAD_MANAGER::DownloadManager::downloadUnnormalFinished, this, [](const int idd) {
                const auto d = CORE::SharedStorage::instance().getDownload(idd);
                if (!d) return;

                NoticeView::information(UI_CONSTANTS::MAIN_WINDOW::INFORMATION(), UI_CONSTANTS::MAIN_WINDOW::UNNORMAL_EXIT_DOWNLOAD(d->getFilePath() + QDir::separator() + d->getSaveName() + UI_CONSTANTS::MAIN_WINDOW::POINT + d->getSuffix(), d->getTitle()));
            });

            connect(this->downloadManager, &DOWNLOAD_DOWNLOAD_MANAGER::DownloadManager::allFinished, this, []() {});
        }
    }

    void MainWindow::addTask() {
        if (auto* dc = new DownloadConfig(); dc->exec() == QDialog::Accepted) {
            const auto idd = dc->getId();
            const auto item = CORE::SharedStorage::instance().getDownload(idd);
            const auto& itemCopy = item;

            this->dbClient->addDownload(*itemCopy, [this, itemCopy, idd](const QJsonObject& resp) {
                if (resp[DB_CONSTANTS::JSON_FORMAT::STATUS].toString().compare(DB_CONSTANTS::JSON_FORMAT::STATUS_OK, Qt::CaseInsensitive) == 0) {
                    this->addListWidgetItem();

                    const auto idx = static_cast<int>(CORE::SharedStorage::instance().getDownloadsSize() - 1);
                    const auto page = idx / UI_CONSTANTS::MAIN_WINDOW::Q_LIST_WIDGET::PAGE_SIZE;

                    this->addDownloadCard(this->createDownloadCard(itemCopy));

                    this->idIndexMap.insert(idd);

                    if (this->loadedPages.contains(page)) this->loadedPages.remove(page);
                    this->loadPage(page);
                }

                else NoticeView::critical(UI_CONSTANTS::MAIN_WINDOW::CRITICAL(), resp[DB_CONSTANTS::JSON_FORMAT::MESSAGE][DB_CONSTANTS::JSON_FORMAT::USER_ID].toString());
            });
        }
    }

    void MainWindow::pageChanged(const int value) {
        constexpr auto pageHeight = UI_CONSTANTS::MAIN_WINDOW::Q_LIST_WIDGET::PAGE_SIZE * UI_CONSTANTS::MAIN_WINDOW::Q_LIST_WIDGET::ITEM_SIZE.second;

        const auto page = value / pageHeight;

        if (!this->loadedPages.contains(page)) this->loadPage(page);

        this->loadPage(page + 1);

        for (const auto p : this->loadedPages) {if (abs(p - page) > UI_CONSTANTS::MAIN_WINDOW::Q_LIST_WIDGET::DIFFERENCE_PAGES) this->unloadPage(p);}
    }

    void MainWindow::onActionTriggered() {
        const auto* act = qobject_cast<QAction*>(sender());
        if (!act) return;

        const auto target_translation_name = CORE::TRANSLATION::languageLocalCode(act->text()) + CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_TRANSLATION_DOC_SUFFIX;

        QMap<QString, QString> map;
        map.insert(CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_TRANSLATOR_KEY, target_translation_name);

        if (CORE::SYS_INFO::writeConfig(map, CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_ORGANIZATION, CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_TRANSLATION_PLIST)) {
            this->m_isRestarting = true;
            emit restartAppRequest();
        }

        else NoticeView::warning(UI_CONSTANTS::MAIN_WINDOW::WARNING(), UI_CONSTANTS::MAIN_WINDOW::FAILED_CHANGE_LANGUAGE(target_translation_name));
    }

    void MainWindow::handleImportData() {
        QFileDialog dialog {
            this,
            UI_CONSTANTS::MAIN_WINDOW::IMPORT_DATA(),
            QStandardPaths::writableLocation(QStandardPaths::DownloadLocation),
                UI_CONSTANTS::MAIN_WINDOW::DEFAULT_DATA_FILTER()
        };

        #ifdef Q_OS_MAC
            dialog.setOptions(QFileDialog::DontUseNativeDialog);
            dialog.setStyleSheet(UI_CONSTANTS::DOWNLOAD_CONFIG::STYLE);
        #endif

        dialog.setFilter(dialog.filter() | QDir::Hidden | QDir::NoDotAndDotDot);

        if (dialog.exec() == QFileDialog::Accepted) {
            if (const auto fullPath = dialog.selectedFiles().first(); !fullPath.isEmpty()) {
                if (QList<QSharedPointer<CONTAINER::Download>> dataList; this->crypto.loadEncrypted(fullPath, dataList)) {
                    if (CORE::SharedStorage::instance().getDownloadsSize() <= 0) {
                        int t_id = 0;

                        for (auto& d : dataList) {
                            CORE::SharedStorage::instance().addDownload(*d);
                            this->addListWidgetItem();
                            this->idIndexMap.insert(d->getId());
                            t_id = qMax(t_id, d->getId());
                            this->dbClient->addDownload(*d, [](const QJsonObject& resp) {if (resp[DB_CONSTANTS::JSON_FORMAT::STATUS].toString().compare(DB_CONSTANTS::JSON_FORMAT::STATUS_OK, Qt::CaseInsensitive) != 0) NoticeView::critical(UI_CONSTANTS::MAIN_WINDOW::CRITICAL(), resp[DB_CONSTANTS::JSON_FORMAT::MESSAGE][DB_CONSTANTS::JSON_FORMAT::USER_ID].toString());});
                        }

                        DownloadConfig::nextId = ++t_id;
                        this->loadPage(0);
                    }

                    else NoticeView::warning(UI_CONSTANTS::MAIN_WINDOW::FAILED(), UI_CONSTANTS::MAIN_WINDOW::FAILED_APPEND_DATA_LIST());
                }

                else NoticeView::warning(UI_CONSTANTS::MAIN_WINDOW::FAILED(), UI_CONSTANTS::MAIN_WINDOW::FAILED_IMPORT_DATA());
            }
        }
    }

    void MainWindow::handleExportData() {
        QFileDialog dialog {
            this,
            UI_CONSTANTS::MAIN_WINDOW::EXPORT_DATA(),
            QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + QDir::separator() + UI_CONSTANTS::MAIN_WINDOW::DEFAULT_EXPORTED_DATA_NAME,
                UI_CONSTANTS::MAIN_WINDOW::DEFAULT_DATA_FILTER()
        };

        #ifdef Q_OS_MAC
            dialog.setOptions(QFileDialog::DontUseNativeDialog);
            dialog.setStyleSheet(UI_CONSTANTS::DOWNLOAD_CONFIG::STYLE);
        #elif defined(Q_OS_WIN)
        #elif defined(Q_OS_LINUX)
            dialog.setFileMode(QFileDialog::AnyFile);
            dialog.setOption(QFileDialog::ShowDirsOnly, false);
            dialog.setAcceptMode(QFileDialog::AcceptSave);
        #endif

        dialog.setFilter(dialog.filter() | QDir::Hidden | QDir::NoDotAndDotDot);

        if (dialog.exec() == QFileDialog::Accepted) {
            const auto fullPath = dialog.selectedFiles().first();
            const auto fn = (fullPath + UI_CONSTANTS::MAIN_WINDOW::DEFAULT_DATA_SUFFIX).trimmed();

            if (!fullPath.isEmpty()) {
                if (const auto dat = CORE::SharedStorage::instance().getDownloads()) {
                    if (this->crypto.saveEncrypted(fn, *dat)) {
                        NoticeView::information(UI_CONSTANTS::MAIN_WINDOW::SUCCESS(), UI_CONSTANTS::MAIN_WINDOW::SUCCESS_EXPORT_DATA());
                        return;
                    }
                }

                NoticeView::information(UI_CONSTANTS::MAIN_WINDOW::FAILED(), UI_CONSTANTS::MAIN_WINDOW::FAILED_EXPORT_DATA());
            }

            else NoticeView::warning(UI_CONSTANTS::MAIN_WINDOW::WARNING(), UI_CONSTANTS::DOWNLOAD_CONFIG::INVALID_FILE_PATH(fn));
        }
    }

    void MainWindow::handleClearStatus() const {
        if (CORE::SharedStorage::instance().getDownloadsSize() > 0) {
            const auto downloads = CORE::SharedStorage::instance().getDownloads();
            if (!downloads) return;

            for (const auto& d : *downloads) {
                const auto idd = d->getId();

                d->setProgress(0);
                d->setDownloadState(false);

                this->dbClient->updateProgress(idd, 0, [](const QJsonObject&) {});
                this->dbClient->updateDownloadState(idd, false, [](const QJsonObject&) {});

                if (const auto* card = this->widgetsIndex.value(idd)) {
                    card->setProgress(0);
                    card->enableButtons();
                }
            }
        }
    }

    void MainWindow::handleEditRequest() const {
        const auto* widget = qobject_cast<DownloadCard*>(sender());

        const auto idd = widget->getId();

        auto* dc = new DownloadConfig();

        const auto d = *CORE::SharedStorage::instance().getDownload(idd);
        CORE::SharedStorage::instance().removeDownload(d);

        dc->requestEdit(d);
        if (dc->exec() == QDialog::Accepted) {
            const auto new_d = CORE::SharedStorage::instance().getDownload(idd);

            this->dbClient->removeDownload(d.getId(), [](const QJsonObject&) {});
            this->dbClient->addDownload(*new_d, [](const QJsonObject&) {});

            widget->setFileName(new_d->getFilePath() + QDir::separator() + new_d->getSaveName() + UI_CONSTANTS::MAIN_WINDOW::POINT + new_d->getSuffix());
            widget->setProgress(new_d->getProgress());
            widget->setProgress(0);

            NoticeView::information(UI_CONSTANTS::MAIN_WINDOW::SUCCESS(), UI_CONSTANTS::MAIN_WINDOW::CHANGE_SUCCESS());
        }

        else CORE::SharedStorage::instance().addDownload(d);
    }

    void MainWindow::handleDeleteRequest() {
        if (NoticeView::confirmation(UI_CONSTANTS::MAIN_WINDOW::CONFIRMATION(), UI_CONSTANTS::MAIN_WINDOW::CONFIRM_DELETION())) {
            const auto* widget = qobject_cast<DownloadCard*>(sender());

            const auto idd = widget->getId();
            const auto idx = this->idIndexMap.indexOf(idd);

            CORE::SharedStorage::instance().removeDownload(idd);

            this->dbClient->removeDownload(idd, [](const QJsonObject&) {});

            delete this->listWidget->takeItem(idx);

            this->idIndexMap.erase(idd);

            const int page = idx + 1 / UI_CONSTANTS::MAIN_WINDOW::Q_LIST_WIDGET::PAGE_SIZE;

            this->loadedPages.remove(page);
            this->loadPage(page);
        }
    }

    void MainWindow::handleStartRequest() const {if (!this->downloadManager->isRunning()) {if (CORE::SharedStorage::instance().getDownloadsSize() > 0) this->downloadManager->start();}}

    void MainWindow::handleStopRequest() {
        if (NoticeView::confirmation(UI_CONSTANTS::MAIN_WINDOW::STOP_ALL(), UI_CONSTANTS::MAIN_WINDOW::ASK_IF_STOP_ALL())) {
            this->downloadManager->stopAll();
            this->loadPage(0);
        }
    }

    void MainWindow::handleLoadHistories(const QList<CONTAINER::Download>& downloads) {
        int d_idx = 0;

        CORE::SharedStorage::instance().addDownloads(downloads);

        for (const auto& d : downloads) {
            this->addListWidgetItem();
            this->addDownloadCard(this->createDownloadCard(d));
            this->idIndexMap.insert(d.getId());

            d_idx = qMax(d_idx, d.getId());
        }

        DownloadConfig::nextId = ++d_idx;
        this->loadPage(0);
    }

    void MainWindow::removeAll() {
        if (NoticeView::confirmation(UI_CONSTANTS::MAIN_WINDOW::CONFIRMATION(), UI_CONSTANTS::MAIN_WINDOW::CONFIRM_DELETION())) {
            this->downloadManager->stopAll();
            this->listWidget->clear();
            this->widgetsIndex.clear();
            this->idIndexMap.clear();
            this->loadedPages.clear();

            CORE::SharedStorage::instance().clear();
            DownloadConfig::nextId = UI_CONSTANTS::DOWNLOAD_CONFIG::DEFAULT_NEXT_ID;

            this->dbClient->removeAllDownloads([](const QJsonObject&) {});
        }
    }

    void MainWindow::restartApp() {
        QProcess::startDetached(QCoreApplication::applicationFilePath(), QCoreApplication::arguments());
        emit quitApp();
    }

    void MainWindow::configuration() {
        SettingsView view;
        view.exec();
    }


    // Private

    DownloadCard* MainWindow::createDownloadCard(const CONTAINER::Download& download) {return this->createDownloadCard(QSharedPointer<CONTAINER::Download>::create(download));}

    DownloadCard* MainWindow::createDownloadCard(const QSharedPointer<CONTAINER::Download>& download) {
        auto* t_c = new DownloadCard(download->getId(), download->getTitle(), download->getFilePath() + QDir::separator() + download->getSaveName() + UI_CONSTANTS::MAIN_WINDOW::POINT + download->getSuffix(), this->listWidget);

        connect(t_c, &DownloadCard::requestEdit, this, &MainWindow::handleEditRequest);
        connect(t_c, &DownloadCard::requestRemove, this, &MainWindow::handleDeleteRequest);

        return t_c;
    }

    void MainWindow::addDownloadCard(DownloadCard* dc) {this->widgetsIndex.insert(dc->getId(), dc);}

    DownloadCard* MainWindow::getDownloadCard(const int idd) const {return this->widgetsIndex.value(idd, nullptr);}

    void MainWindow::addListWidgetItem() const {
        auto* item = new QListWidgetItem();
        item->setSizeHint(QSize(UI_CONSTANTS::MAIN_WINDOW::Q_LIST_WIDGET::ITEM_SIZE.first,UI_CONSTANTS::MAIN_WINDOW::Q_LIST_WIDGET::ITEM_SIZE.second));
        this->listWidget->addItem(item);
    }

    void MainWindow::addListWidgetItems(const int num) const {if (num >= 1) {for (int i = 0; i < num; i++) {this->addListWidgetItem();}}}

    void MainWindow::removeListWidgetItem(const int page) const {this->listWidget->setItemWidget(this->listWidget->item(page), nullptr);}

    void MainWindow::loadPage(const int page) {
        if (this->loadedPages.contains(page)) return;

        const int start = page * UI_CONSTANTS::MAIN_WINDOW::Q_LIST_WIDGET::PAGE_SIZE;
        const int end = qMin(start + UI_CONSTANTS::MAIN_WINDOW::Q_LIST_WIDGET::PAGE_SIZE, static_cast<int>(CORE::SharedStorage::instance().getDownloadsSize()));

        for (int i = start; i < end; ++i) {
            const int idd = this->idIndexMap.idAt(i);
            if (idd == -1) continue;

            QListWidgetItem* item = this->listWidget->item(i);
            if (!item) continue;

            if (this->listWidget->itemWidget(item)) continue;

            auto d = CORE::SharedStorage::instance().getDownload(idd);
            if (!d) continue;

            auto* card = new DownloadCard(idd, d->getTitle(), d->getFilePath() + QDir::separator() + d->getSaveName() + UI_CONSTANTS::MAIN_WINDOW::POINT + d->getSuffix(), this->listWidget);
            this->widgetsIndex.insert(card->getId(), card);

            const auto prog = d->getProgress();
            card->setProgress(prog);
            if (prog > 0 && !d->getDownloadState()) card->disableButtons();

            connect(card, &DownloadCard::requestEdit, this, &MainWindow::handleEditRequest);
            connect(card, &DownloadCard::requestRemove, this, &MainWindow::handleDeleteRequest);

            this->addDownloadCard(card);
            this->listWidget->setItemWidget(item, card);
        }

        this->loadedPages.insert(page);
    }

    void MainWindow::unloadPage(const int page) {
        if (!this->loadedPages.contains(page)) return;

        const auto start = page * UI_CONSTANTS::MAIN_WINDOW::Q_LIST_WIDGET::PAGE_SIZE;
        const int end = qMin(start + UI_CONSTANTS::MAIN_WINDOW::Q_LIST_WIDGET::PAGE_SIZE, static_cast<int>(CORE::SharedStorage::instance().getDownloadsSize()));

        for (int i = start; i < end; ++i) {
            if (const auto tmp = this->idIndexMap.idAt(i); tmp != -1) {
                if (this->getDownloadCard(tmp)) {
                    this->listWidget->setItemWidget(this->listWidget->item(i), nullptr);
                    this->widgetsIndex.remove(tmp);
                }
            }
        }

        this->loadedPages.remove(page);
    }
}
