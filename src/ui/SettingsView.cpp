
#include "core/BasicTools.hpp"
#include "ui/NoticeView.hpp"
#include "ui/SettingsView.hpp"
#include <QFileDialog>
#include <QPushButton>

namespace UI {
    // Public

    SettingsView::SettingsView(QWidget* parent) : QDialog(parent) {
        this->mainLayout = new QVBoxLayout;

        // Tools Settings
        this->toolsBox = new QGroupBox(UI_CONSTANTS::SETTINGS_VIEW::TOOLS_BOX());
        this->toolsForm = new QFormLayout;
        this->toolsGrid = new QGridLayout;

        this->ytDlpLab = new QLabel(UI_CONSTANTS::SETTINGS_VIEW::YT_DLP_LAB(), this);
        this->ytDlpLab->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
        this->ytDlpEdit = new QLineEdit(this);
        this->ytDlpEdit->setEnabled(false);
        this->ytDlpEdit->setFixedSize(UI_CONSTANTS::SETTINGS_VIEW::LINEEDIT_SIZE.first, UI_CONSTANTS::SETTINGS_VIEW::LINEEDIT_SIZE.second);
        this->ytDlpBtn = new QPushButton(UI_CONSTANTS::SETTINGS_VIEW::SEARCH_LAB(), this);

        this->ffmpegLab = new QLabel(UI_CONSTANTS::SETTINGS_VIEW::FFMPEG_LAB(), this);
        this->ffmpegLab->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
        this->ffmpegEdit = new QLineEdit(this);
        this->ffmpegEdit->setEnabled(false);
        this->ffmpegEdit->setFixedSize(UI_CONSTANTS::SETTINGS_VIEW::LINEEDIT_SIZE.first, UI_CONSTANTS::SETTINGS_VIEW::LINEEDIT_SIZE.second);
        this->ffmpegBtn = new QPushButton(UI_CONSTANTS::SETTINGS_VIEW::SEARCH_LAB(), this);

        this->nodeLab = new QLabel(UI_CONSTANTS::SETTINGS_VIEW::NODE_LAB(), this);
        this->nodeLab->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
        this->nodeEdit = new QLineEdit(this);
        this->nodeEdit->setEnabled(false);
        this->nodeEdit->setFixedSize(UI_CONSTANTS::SETTINGS_VIEW::LINEEDIT_SIZE.first, UI_CONSTANTS::SETTINGS_VIEW::LINEEDIT_SIZE.second);
        this->nodeBtn = new QPushButton(UI_CONSTANTS::SETTINGS_VIEW::SEARCH_LAB(), this);

        if (const auto dir_yt_dlp = CORE::SYS_INFO::readConfig(CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_YT_DLP_KEY); dir_yt_dlp.isEmpty()) {if (const auto dir1 = CORE::SYS_INFO::findToolPath(UI_CONSTANTS::SETTINGS_VIEW::YT_DLP()); !dir1.isEmpty()) this->ytDlpEdit->setText(dir1);}
        else this->ytDlpEdit->setText(dir_yt_dlp);

        if (const auto dir_ffmpeg = CORE::SYS_INFO::readConfig(CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_FFMPEG_KEY); dir_ffmpeg.isEmpty()) {if (const auto dir2 = CORE::SYS_INFO::findToolPath(UI_CONSTANTS::SETTINGS_VIEW::FFMPEG()); !dir2.isEmpty()) this->ffmpegEdit->setText(dir2);}
        else this->ffmpegEdit->setText(dir_ffmpeg);

        if (const auto dir_node = CORE::SYS_INFO::readConfig(CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_NODE_JS_KEY); dir_node.isEmpty()) {if (const auto dir3 = CORE::SYS_INFO::findToolPath(UI_CONSTANTS::SETTINGS_VIEW::NODE_JS()); !dir3.isEmpty()) this->nodeEdit->setText(dir3);}
        else this->nodeEdit->setText(dir_node);

        this->toolsGrid->addWidget(ytDlpLab, 0, 0);
        this->toolsGrid->addWidget(this->ytDlpEdit, 0, 1);
        this->toolsGrid->addWidget(this->ytDlpBtn, 0, 2);
        this->toolsGrid->addWidget(this->ffmpegLab, 1, 0);
        this->toolsGrid->addWidget(this->ffmpegEdit, 1, 1);
        this->toolsGrid->addWidget(this->ffmpegBtn, 1, 2);
        this->toolsGrid->addWidget(this->nodeLab, 2, 0);
        this->toolsGrid->addWidget(this->nodeEdit, 2, 1);
        this->toolsGrid->addWidget(this->nodeBtn, 2, 2);

        this->toolsGrid->setHorizontalSpacing(UI_CONSTANTS::SETTINGS_VIEW::GRID_FIXED_SPACING.first);
        this->toolsGrid->setVerticalSpacing(UI_CONSTANTS::SETTINGS_VIEW::GRID_FIXED_SPACING.second);

        this->buttonLayout = new QHBoxLayout;
        this->saveBtn = new QPushButton(UI_CONSTANTS::SETTINGS_VIEW::SAVE_BTN(), this);

        this->buttonLayout->addStretch();
        this->buttonLayout->addWidget(this->saveBtn);
        this->buttonLayout->addStretch();

        this->toolsForm->addItem(this->toolsGrid);
        this->toolsBox->setLayout(this->toolsForm);
        this->mainLayout->addWidget(this->toolsBox);
        this->mainLayout->addLayout(this->buttonLayout);

        this->setLayout(this->mainLayout);
        this->setWindowIcon(QIcon(UI_CONSTANTS::NOTICE_VIEW::RESOURCES_PATH() + QDir::separator() + UI_CONSTANTS::NOTICE_VIEW::ICON_NAME));
        this->setWindowTitle(UI_CONSTANTS::SETTINGS_VIEW::WINDOW_TITLE());
        this->setFixedSize(UI_CONSTANTS::SETTINGS_VIEW::WINDOW_SIZE.first, UI_CONSTANTS::SETTINGS_VIEW::WINDOW_SIZE.second);
        this->setStyleSheet(UI_CONSTANTS::SETTINGS_VIEW::STYLE);

        connect(this->ytDlpBtn, &QPushButton::clicked, this,  [this]() {this->searchPath(UI_CONSTANTS::SETTINGS_VIEW::CHOOSE_YT_DLP(), UI_CONSTANTS::SETTINGS_VIEW::FILTER(), this->ytDlpEdit);});
        connect(this->ffmpegBtn, &QPushButton::clicked, this, [this]() {this->searchPath(UI_CONSTANTS::SETTINGS_VIEW::CHOOSE_FFMPEG(), UI_CONSTANTS::SETTINGS_VIEW::FILTER(), this->ffmpegEdit);});
        connect(this->nodeBtn, &QPushButton::clicked, this, [this]() {this->searchPath(UI_CONSTANTS::SETTINGS_VIEW::CHOOSE_NODE(), UI_CONSTANTS::SETTINGS_VIEW::FILTER(), this->nodeEdit);});
        connect(this->saveBtn, &QPushButton::clicked, this, &SettingsView::saveSettings);
    }


    // Private Slots

    void SettingsView::searchPath(const QString& title, const QString& filter, QLineEdit* lineEdit) {
        bool flag = true;

        if (!lineEdit->text().isEmpty()) {
            flag = false;

            if (NoticeView::confirmation(UI_CONSTANTS::SETTINGS_VIEW::TITLE_MODIFY(), UI_CONSTANTS::SETTINGS_VIEW::CONTENT_MODIFY())) flag = true;
        }

        if (flag) {
            QFileDialog dialog(
                this,
                title,
                QDir::homePath(),
                filter
            );

            #ifdef Q_OS_MAC
                dialog.setOption(QFileDialog::DontUseNativeDialog, true);
            #endif

            dialog.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
            dialog.setStyleSheet(UI_CONSTANTS::DOWNLOAD_CONFIG::STYLE);

            if (dialog.exec() == Accepted) {
                if (const auto filePath = dialog.selectedFiles().first(); CORE::SYS_INFO::checkExecutable(filePath).isEmpty()) NoticeView::critical(UI_CONSTANTS::SETTINGS_VIEW::ERROR(), UI_CONSTANTS::SETTINGS_VIEW::CONTENT_FAILED_CHANGE_PATH());

                else {
                    NoticeView::information(UI_CONSTANTS::SETTINGS_VIEW::SUCCESS(), UI_CONSTANTS::SETTINGS_VIEW::CONTENT_CHANGED_CORRECTLY_PATH());
                    lineEdit->setText(filePath);
                }
            }
        }
    }

    void SettingsView::saveSettings() {
        if (this->ytDlpEdit->text().isEmpty() || this->ffmpegEdit->text().isEmpty() || this->nodeEdit->text().isEmpty()) NoticeView::warning(UI_CONSTANTS::SETTINGS_VIEW::ERROR(), UI_CONSTANTS::SETTINGS_VIEW::TOOL_PATH_MUST_BE_PROVIDED());

        else {
            QMap<QString, QString> params;

            params.insert(CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_YT_DLP_KEY, this->ytDlpEdit->text());
            params.insert(CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_FFMPEG_KEY, this->ffmpegEdit->text());
            params.insert(CORE_CONSTANTS::SETTINGS_VIEW::DEFAULT_NODE_JS_KEY, this->nodeEdit->text());

            if (CORE::SYS_INFO::writeConfig(params)) {
                NoticeView::information(UI_CONSTANTS::SETTINGS_VIEW::SUCCESS(), UI_CONSTANTS::SETTINGS_VIEW::CONFIG_SAVED_CORRECTLY());
                accept();
            }

            else {
                NoticeView::warning(UI_CONSTANTS::SETTINGS_VIEW::FAILED(), UI_CONSTANTS::SETTINGS_VIEW::CONFIG_SAVED_FAILED());
                reject();
            }
        }
    }
}
