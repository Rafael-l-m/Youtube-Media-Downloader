
#pragma once

#include <QDialog>
#include <QPlainTextEdit>
#include <QProcess>

namespace UI {
    class ShowItags final : public QDialog {
        Q_OBJECT
    public:
        explicit ShowItags(const QString& url, QWidget* parent = nullptr);

    protected:
        void resizeEvent(QResizeEvent* event) override;

    private:
        void execute(const QString& url);

        QPlainTextEdit* textEdit;
        QProcess* process;
    };
}
