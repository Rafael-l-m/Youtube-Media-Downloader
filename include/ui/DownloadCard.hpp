
#pragma once

#include "ui/GlassWidget.hpp"
#include <QProgressBar>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QTextBrowser>
#include <QVBoxLayout>

namespace UI {
    class DownloadCard final : public GlassWidget {
        Q_OBJECT
    public:
        explicit DownloadCard(int id, const QString& title, const QString& name, QWidget* parent = nullptr);

        [[nodiscard]] int getId() const;
        [[nodiscard]] int getProgress() const;

        void setFileName(const QString& newFileName) const;
        void setProgress(int newProgress) const;

        void enableButtons() const;
        void disableButtons() const;

    signals:
        void requestEdit(UI::DownloadCard* self);
        void requestRemove(UI::DownloadCard* self);

    private:
        const int id;

        QHBoxLayout* layout;
        QTextBrowser* title;
        QTextBrowser* fileName;
        QProgressBar* progressBar;
        QPropertyAnimation* animation;
        QPushButton* editBtn;
        QPushButton* removeBtn;
    };
}
