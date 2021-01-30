#include "clickablewidget.h"

ClickableWidget::ClickableWidget(QWidget* parent, Qt::WindowFlags f)
    : QWidget(parent) {

}

ClickableWidget::~ClickableWidget() {}

void ClickableWidget::mousePressEvent(QMouseEvent* event) {
    emit clicked(this);
}

void ClickableWidget::paintEvent(QPaintEvent * pE)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
