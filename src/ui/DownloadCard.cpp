
#include "constants/Ui_Constants.hpp"
#include "ui/DownloadCard.hpp"

namespace UI {
    // Public

    DownloadCard::DownloadCard(const int id, const QString& title, const QString& name, QWidget *parent) : GlassWidget(parent), id(id) {
        this->layout = new QHBoxLayout;

        this->progressBar = new QProgressBar(this);
        this->editBtn = new QPushButton(UI_CONSTANTS::DOWNLOAD_CARD::EDIT_BTN(), this);
        this->removeBtn = new QPushButton(UI_CONSTANTS::DOWNLOAD_CARD::REMOVE_BTN(), this);

        this->progressBar->setAlignment(Qt::AlignCenter);
        this->progressBar->setFixedHeight(UI_CONSTANTS::DOWNLOAD_CARD::PROGRESS_BAR_SIZE.second);
        this->progressBar->setValue(UI_CONSTANTS::DOWNLOAD_CARD::DEFAULT_VALUE_PROGRESS_BAR);
        this->progressBar->setRange(UI_CONSTANTS::DOWNLOAD_CARD::RANGE_PROGRESS_BAR.first, UI_CONSTANTS::DOWNLOAD_CARD::RANGE_PROGRESS_BAR.second);

        this->animation = new QPropertyAnimation(this->progressBar, UI_CONSTANTS::DOWNLOAD_CARD::DEFAULT_PROPERTY_NAME_PROGRESS_BAR);
        this->animation->setDuration(UI_CONSTANTS::DOWNLOAD_CARD::DURATION_ANIMATION);
        this->animation->setEasingCurve(QEasingCurve::OutCubic);

        this->title = new QTextBrowser(this);
        this->title->setFixedHeight(UI_CONSTANTS::DOWNLOAD_CARD::TEXT_BROWSER_SIZE.second);
        this->title->setAttribute(Qt::WA_TranslucentBackground);
        this->title->setLineWrapMode(QTextEdit::NoWrap);
        this->title->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        this->title->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->title->setStyleSheet(UI_CONSTANTS::DOWNLOAD_CARD::STYLE_TEXT_BROWSER);
        this->title->setText(title);

        this->fileName = new QTextBrowser(this);
        this->fileName->setFixedHeight(UI_CONSTANTS::DOWNLOAD_CARD::TEXT_BROWSER_SIZE.second);
        this->fileName->setAttribute(Qt::WA_TranslucentBackground);
        this->fileName->setLineWrapMode(QTextEdit::NoWrap);
        this->fileName->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        this->fileName->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->fileName->setStyleSheet(UI_CONSTANTS::DOWNLOAD_CARD::STYLE_TEXT_BROWSER);
        this->fileName->setText(name);

        this->title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        this->fileName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        this->progressBar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        this->editBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        this->removeBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        this->layout->addWidget(this->title, 3);
        this->layout->addWidget(this->fileName, 3);
        this->layout->addWidget(this->progressBar, 2);
        this->layout->addWidget(this->editBtn, 0);
        this->layout->addWidget(this->removeBtn, 0);
        this->layout->setSpacing(UI_CONSTANTS::DOWNLOAD_CARD::DEFAULT_SPACING_LAYOUT);

        this->setLayout(this->layout);
        this->setStyleSheet(UI_CONSTANTS::DOWNLOAD_CARD::STYLE);

        connect(this->editBtn, &QPushButton::clicked, this, [this](){emit requestEdit(this);});
        connect(this->removeBtn, &QPushButton::clicked, this, [this](){emit requestRemove(this);});
    }

    int DownloadCard::getId() const {return this->id;}

    int DownloadCard::getProgress() const {return this->progressBar->value();}

    void DownloadCard::setFileName(const QString& newFileName) const {this->fileName->setText(newFileName);}

    void DownloadCard::setProgress(const int newProgress) const {
        this->animation->setStartValue(this->progressBar->value());
        this->animation->setEndValue(newProgress);
        this->animation->start();
    }

    void DownloadCard::enableButtons() const {this->editBtn->setEnabled(true); this->removeBtn->setEnabled(true);}

    void DownloadCard::disableButtons() const {this->editBtn->setEnabled(false); this->removeBtn->setEnabled(false);}
}
