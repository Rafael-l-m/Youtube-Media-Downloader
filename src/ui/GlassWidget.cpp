
#include "constants/Ui_Constants.hpp"
#include "ui/GlassWidget.hpp"
#include <QGraphicsBlurEffect>
//#include <QMouseEvent>
#include <QPainter>

namespace UI {
    // Public

    GlassWidget::GlassWidget(QWidget* parent) : QWidget(parent) {
        this->setAttribute(Qt::WA_TranslucentBackground);
        this->setWindowFlags(Qt::FramelessWindowHint);

        this->blurLayer = new QWidget(this);
        this->blurLayer->setGeometry(rect());
        this->blurLayer->lower();

        auto* blur = new QGraphicsBlurEffect(this->blurLayer);
        blur->setBlurRadius(UI_CONSTANTS::GLASS_WIDGET::BLUR_RADIUS);
        this->blurLayer->setGraphicsEffect(blur);
    }


    // Protected

    void GlassWidget::paintEvent(QPaintEvent*) {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        const QRect r = rect().adjusted(UI_CONSTANTS::GLASS_WIDGET::Q_RECT_ADJUSTED[0], UI_CONSTANTS::GLASS_WIDGET::Q_RECT_ADJUSTED[1], UI_CONSTANTS::GLASS_WIDGET::Q_RECT_ADJUSTED[2], UI_CONSTANTS::GLASS_WIDGET::Q_RECT_ADJUSTED[3]);

        p.setBrush(UI_CONSTANTS::GLASS_WIDGET::COLOR_PAINT_SET_BRUSH_1);
        p.setPen(Qt::NoPen);
        p.drawRoundedRect(r, UI_CONSTANTS::GLASS_WIDGET::RADIUS_DRAW_ROUNDED_RECT.first, UI_CONSTANTS::GLASS_WIDGET::RADIUS_DRAW_ROUNDED_RECT.second);

        p.setBrush(UI_CONSTANTS::GLASS_WIDGET::COLOR_PAINT_SET_BRUSH_2);
        p.drawRoundedRect(r, UI_CONSTANTS::GLASS_WIDGET::RADIUS_DRAW_ROUNDED_RECT.first, UI_CONSTANTS::GLASS_WIDGET::RADIUS_DRAW_ROUNDED_RECT.second);

        p.setPen(QPen(UI_CONSTANTS::GLASS_WIDGET::COLOR_PEN_SET_BRUSH, UI_CONSTANTS::GLASS_WIDGET::PEN_WIDTH));
        p.setBrush(Qt::NoBrush);
        p.drawRoundedRect(r, UI_CONSTANTS::GLASS_WIDGET::RADIUS_DRAW_ROUNDED_RECT.first, UI_CONSTANTS::GLASS_WIDGET::RADIUS_DRAW_ROUNDED_RECT.second);

        QLinearGradient highlight(UI_CONSTANTS::GLASS_WIDGET::HIGHLIGHTS_START[0], UI_CONSTANTS::GLASS_WIDGET::HIGHLIGHTS_START[1], UI_CONSTANTS::GLASS_WIDGET::HIGHLIGHTS_START[2], height() / UI_CONSTANTS::GLASS_WIDGET::DIVISOR_HIGHLIGHT_Y_FINAL_STOP);
        highlight.setColorAt(UI_CONSTANTS::GLASS_WIDGET::HIGHLIGHT_POS.first, UI_CONSTANTS::GLASS_WIDGET::COLOR_HIGHLIGHT_1);
        highlight.setColorAt(UI_CONSTANTS::GLASS_WIDGET::HIGHLIGHT_POS.second, UI_CONSTANTS::GLASS_WIDGET::COLOR_HIGHLIGHT_2);

        p.setBrush(highlight);
        p.setPen(Qt::NoPen);
        p.drawRoundedRect(r, UI_CONSTANTS::GLASS_WIDGET::RADIUS_DRAW_ROUNDED_RECT.first, UI_CONSTANTS::GLASS_WIDGET::RADIUS_DRAW_ROUNDED_RECT.second);
    }

    void GlassWidget::mousePressEvent(QMouseEvent* e) {
        // this->dragPos = e->globalPosition().toPoint() - frameGeometry().topLeft();
        QWidget::mousePressEvent(e);
    }

    void GlassWidget::mouseMoveEvent(QMouseEvent* e) {
        //if (e->buttons() & Qt::LeftButton) move(e->globalPosition().toPoint()- this->dragPos);
    }

    void GlassWidget::resizeEvent(QResizeEvent* e) {QWidget::resizeEvent(e); this->blurLayer->setGeometry(rect());}
}
