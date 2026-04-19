
#pragma once

#include <QWidget>

namespace UI {
    class GlassWidget : public QWidget {
        Q_OBJECT
    public:
        explicit GlassWidget(QWidget* parent = nullptr);

    protected:
        void paintEvent(QPaintEvent*) override;
        void mousePressEvent(QMouseEvent* e) override;
        void mouseMoveEvent(QMouseEvent* e) override;
        void resizeEvent(QResizeEvent* e) override;

    private:
        QPixmap noise;
        QPoint dragPos;
        QWidget* blurLayer;
    };
}
