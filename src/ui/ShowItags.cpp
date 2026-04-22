
#include "constants/Core_Constants.hpp"
#include "constants/Ui_Constants.hpp"
#include "core/SharedStorage.hpp"
#include "ui/ShowItags.hpp"
#include <QDir>
#include <QIcon>

namespace UI {
    // Public

    ShowItags::ShowItags(const QString& url, QWidget* parent) : QDialog(parent) {
        this->textEdit = new QPlainTextEdit(this);
        this->textEdit->setGeometry(this->rect());
        this->textEdit->setReadOnly(true);

        QFont font(UI_CONSTANTS::SHOW_I_TAGS::FONT);
        font.setStyleHint(QFont::Monospace);
        font.setBold(true);
        this->textEdit->setFont(font);

        this->setWindowIcon(QIcon(UI_CONSTANTS::NOTICE_VIEW::RESOURCES_PATH() + QDir::separator() + UI_CONSTANTS::NOTICE_VIEW::ICON_NAME));
        this->setWindowTitle(UI_CONSTANTS::SHOW_I_TAGS::TITLE());
        this->setFixedSize(UI_CONSTANTS::SHOW_I_TAGS::WINDOW_SIZE.first, UI_CONSTANTS::SHOW_I_TAGS::WINDOW_SIZE.second);
        this->setStyleSheet(UI_CONSTANTS::SHOW_I_TAGS::STYLE);

        this->process = new QProcess(this);
        this->execute(url);
    }


    // Protected

    void ShowItags::resizeEvent(QResizeEvent *event) {
        this->textEdit->setGeometry(this->rect());
        QDialog::resizeEvent(event);
    }


    // Private
    void ShowItags::execute(const QString& url) {
        if (const auto url_t = url.trimmed(); !url_t.isEmpty()) {
            const auto tools = CORE::SharedStorage::instance().getToolsPath();

            auto env = QProcessEnvironment::systemEnvironment();
            env.insert(UI_CONSTANTS::SHOW_I_TAGS::PATH, tools->getNodePath() + QDir::listSeparator() + env.value(UI_CONSTANTS::SHOW_I_TAGS::PATH));

            this->process->setProcessEnvironment(env);
            this->process->setProgram(tools->getYtDlpPath());
            this->process->setArguments({CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::NO_PLAYLIST, CORE_CONSTANTS::YT_DLP_CLI_OPTIONS::INFO, url_t});

            connect(this->process, &QProcess::finished, this->process, &QObject::deleteLater);
            connect(this->process, &QProcess::readyReadStandardOutput, this, [this]() {const QString output = this->process->readAllStandardOutput(); this->textEdit->setPlainText(output);});
            connect(this->process, &QProcess::readyReadStandardError, this, [this]() {const QString error = this->process->readAllStandardError(); this->textEdit->setPlainText(error);});

            this->process->start();
        }
    }
}
