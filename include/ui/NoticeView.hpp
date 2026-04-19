
#pragma once

#include "constants/Ui_Constants.hpp"
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>

namespace UI {
    class NoticeView final : public QDialog {
        Q_OBJECT
    public:
        static bool confirmation(const QString& title, const QString& inform, QWidget* parent = nullptr);

        static void information(const QString& title, const QString& inform, QWidget* parent = nullptr);

        static void warning(const QString& title, const QString& inform, QWidget* parent = nullptr);

        static void critical(const QString& title, const QString& inform, QWidget* parent = nullptr);

    private:
        enum class NoticeType {
            CONFIRMATION,
            INFORMATION,
            WARNING,
            CRITICAL
        };

        NoticeView(QString title, QString message, NoticeType type, const QString& windowIconPath = QString(), const QString& imagePath = QString(), QWidget* parent = nullptr);

        const QString title;
        const QIcon windowIcon;
        const QIcon image;
        const QString message;

        QVBoxLayout* mainLayout;
        QHBoxLayout* topLayout;
        QLabel* imageLabel;
        QVBoxLayout* topRightLayout;
        QLabel* textLabel;
        QHBoxLayout* buttonLayout;
        QPushButton* acceptBtn;
        QPushButton* rejectBtn;
    };
}
