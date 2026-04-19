
#include "ui/NoticeView.hpp"
#include <QDir>
#include <QPushButton>

namespace UI {
    // Public

    bool NoticeView::confirmation(const QString& title, const QString& inform, QWidget* parent) {
        const auto RESOURCES_PATH = UI_CONSTANTS::NOTICE_VIEW::RESOURCES_PATH();
        const auto ICON = RESOURCES_PATH + QDir::separator() + UI_CONSTANTS::NOTICE_VIEW::ICON_NAME;
        const auto PIC= RESOURCES_PATH + QDir::separator() + UI_CONSTANTS::NOTICE_VIEW::PIC_CONFIRM_NAME;

        NoticeView box(title, inform, NoticeType::CONFIRMATION, ICON, PIC, parent);

        return box.exec() == Accepted;
    }

    void NoticeView::information(const QString& title, const QString& inform, QWidget* parent) {
        const auto RESOURCES_PATH = UI_CONSTANTS::NOTICE_VIEW::RESOURCES_PATH();
        const auto ICON = RESOURCES_PATH + QDir::separator() + UI_CONSTANTS::NOTICE_VIEW::ICON_NAME;
        const auto PIC= RESOURCES_PATH + QDir::separator() + UI_CONSTANTS::NOTICE_VIEW::PIC_INFORM_NAME;

        NoticeView box(title, inform, NoticeType::INFORMATION, ICON, PIC, parent);

        box.exec();
    }

    void NoticeView::warning(const QString& title, const QString& inform, QWidget* parent) {
        const auto RESOURCES_PATH = UI_CONSTANTS::NOTICE_VIEW::RESOURCES_PATH();
        const auto ICON = RESOURCES_PATH + QDir::separator() + UI_CONSTANTS::NOTICE_VIEW::ICON_NAME;
        const auto PIC= RESOURCES_PATH + QDir::separator() + UI_CONSTANTS::NOTICE_VIEW::PIC_WARN_NAME;

        NoticeView box(title, inform, NoticeType::WARNING, ICON, PIC, parent);

        box.exec();
    }

    void NoticeView::critical(const QString& title, const QString& inform, QWidget* parent) {
        const auto RESOURCES_PATH = UI_CONSTANTS::NOTICE_VIEW::RESOURCES_PATH();
        const auto ICON = RESOURCES_PATH + QDir::separator() + UI_CONSTANTS::NOTICE_VIEW::ICON_NAME;
        const auto PIC= RESOURCES_PATH + QDir::separator() + UI_CONSTANTS::NOTICE_VIEW::PIC_CRITIC_NAME;

        NoticeView box(title, inform, NoticeType::CRITICAL, ICON, PIC, parent);

        box.exec();
    }


    // Private

    NoticeView::NoticeView(QString title, QString message, const NoticeType type, const QString& windowIconPath, const QString& imagePath, QWidget* parent) : QDialog(parent), title(std::move(title)), windowIcon(QIcon(windowIconPath)), image(QIcon(imagePath)), message(std::move(message)), mainLayout(nullptr) {
        this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

        if (!this->windowIcon.isNull()) this->setWindowIcon(this->windowIcon);

        this->mainLayout = new QVBoxLayout(this);

        // Top Section
        this->topLayout = new QHBoxLayout;

        // Top Left
        if (!this->image.isNull()) {
            this->imageLabel = new QLabel(this);
            this->imageLabel->setPixmap(this->image.pixmap(UI_CONSTANTS::NOTICE_VIEW::SHOW_ICON_SIZE.first, UI_CONSTANTS::NOTICE_VIEW::SHOW_ICON_SIZE.second));
            this->topLayout->addWidget(this->imageLabel);
        }

        // Top Right
        this->topRightLayout = new QVBoxLayout();

        this->textLabel = new QLabel(this->message, this);
        this->textLabel->setWordWrap(true);

        this->topRightLayout->addWidget(this->textLabel);

        // Button Layout
        this->buttonLayout = new QHBoxLayout;

        this->acceptBtn = new QPushButton(UI_CONSTANTS::NOTICE_VIEW::YES_BTN(), this);
        this->rejectBtn = new QPushButton(UI_CONSTANTS::NOTICE_VIEW::NO_BTN(), this);

        connect(this->acceptBtn, &QPushButton::clicked, this, &NoticeView::accept);
        connect(this->rejectBtn, &QPushButton::clicked, this, &NoticeView::reject);

        if (type != NoticeType::CONFIRMATION) this->rejectBtn->setVisible(false);

        this->buttonLayout->addStretch();
        this->buttonLayout->addWidget(this->acceptBtn);
        this->buttonLayout->addWidget(this->rejectBtn);

        this->topRightLayout->addLayout(this->buttonLayout);

        this->topLayout->addLayout(this->topRightLayout);

        this->mainLayout->addLayout(this->topLayout);

        this->setModal(true);  // modal window: disable interaction with the main window
        this->setWindowTitle(this->title);
        this->setLayout(this->mainLayout);
        this->setFixedSize(this->QDialog::sizeHint());  // Can not resize
        this->setStyleSheet(UI_CONSTANTS::NOTICE_VIEW::STYLE);
    }
}
