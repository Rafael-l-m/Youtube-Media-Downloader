
#pragma once

#include "core/CryptoManager.hpp"
#include "core/IdIndexMap.hpp"
#include "db/DbClient.hpp"
#include "db/DbServer.hpp"
#include "download/DownloadManager.hpp"
#include "ui/DownloadCard.hpp"
#include "update/UpdateChecker.hpp"
#include <QListWidget>
#include <QMainWindow>

namespace UI {
    class MainWindow final : public QMainWindow {
        Q_OBJECT
    public:
        explicit MainWindow(QWidget* parent = nullptr);

    signals:
        void errorOpenDB();
        void loadHistories(QList<CONTAINER::Download> downloads);
        void restartAppRequest() const;
        void quitApp();

    protected:
        void closeEvent(QCloseEvent* event) override;

    private slots:
        void startInitialization();
        void addTask();
        void pageChanged(int value);
        void onActionTriggered();
        void handleImportData();
        void handleExportData();
        void handleClearStatus() const;
        void handleEditRequest() const;
        void handleDeleteRequest();
        void handleStartRequest() const;
        void handleStopRequest();
        void handleLoadHistories(const QList<CONTAINER::Download>& downloads);
        void removeAll();
        void restartApp();
        static void configuration();

    private:
        DB::DbServer dbServer;
        QPointer<DB::DbClient> dbClient;
        int serverPort;

        // DownloadManager
        DOWNLOAD_DOWNLOAD_MANAGER::DownloadManager* downloadManager;

        // Check Update
        UPDATE::UpdateChecker* updateChecker;

        // id <-> index
        CORE::IdIndexMap idIndexMap;

        // id -> QWidget*
        QHash<int, DownloadCard*> widgetsIndex;
        DownloadCard* createDownloadCard(const CONTAINER::Download& download);
        DownloadCard* createDownloadCard(const QSharedPointer<CONTAINER::Download>& download);
        void addDownloadCard(DownloadCard* dc);
        [[nodiscard]] DownloadCard* getDownloadCard(int idd) const;

        // QListWidget*
        void addListWidgetItem() const;
        void addListWidgetItems(int num) const;
        void removeListWidgetItem(int page) const;

        // Pages
        QSet<int> loadedPages;
        void loadPage(int page);
        void unloadPage(int page);

        // Crypt
        CORE::CryptoManager crypto;

        // CloseEvent
        bool m_isRestarting = false;

        // MenuBar
        QMenuBar* bar;

        QMenu* fileMenu;
        QAction* importDownloadListAction;
        QAction* exportDownloadListAction;
        QAction* clearStatusAction;
        QAction* quitAction;

        QMenu* languageMenu;
        QAction* englishAction;
        QAction* chineseAction;
        QAction* chineseTraditionalAction;
        QAction* spanishAction;
        QAction* portugueseAction;
        QAction* frenchAction;
        QAction* germanAction;
        QAction* italianAction;
        QAction* arabicAction;
        QAction* russianAction;
        QAction* ukrainianAction;
        QAction* japaneseAction;
        QAction* koreanAction;

        QMenu* preferencesMenu;
        QAction* generalAction;

        QMenu* helpMenu;
        QAction* helpContentsAction;
        QAction* checkForUpdatesAction;
        QAction* reportIssuesAction;

        QWidget* central;
        QVBoxLayout* mainLayout;
        QHBoxLayout* topButtonLayout;
        QPushButton* startBtn;
        QPushButton* stopBtn;
        QListWidget* listWidget;
        QHBoxLayout* bottomButtonLayout;
        QPushButton* addBtn;
        QPushButton* removeBtn;
    };
}
