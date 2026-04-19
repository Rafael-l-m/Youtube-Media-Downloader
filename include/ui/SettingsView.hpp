
#pragma once

#include <QDialog>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>

namespace UI {
    class SettingsView final : public QDialog {
        Q_OBJECT
    public:
        explicit SettingsView(QWidget* parent = nullptr);

    private slots:
        void searchPath(const QString& title, const QString& filter, QLineEdit* lineEdit);
        void saveSettings();

    private:
        QVBoxLayout* mainLayout;
        QGroupBox* toolsBox;
        QFormLayout* toolsForm;
        QGridLayout* toolsGrid;
        QLabel* ytDlpLab;
        QLineEdit* ytDlpEdit;
        QPushButton* ytDlpBtn;
        QLabel* ffmpegLab;
        QLineEdit* ffmpegEdit;
        QPushButton* ffmpegBtn;
        QLabel* nodeLab;
        QLineEdit* nodeEdit;
        QPushButton* nodeBtn;
        QHBoxLayout* buttonLayout;
        QPushButton* saveBtn;
    };
}
