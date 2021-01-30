#ifndef CICKABLEWIDGET_H
#define CICKABLEWIDGET_H

#include <QWidget>
#include <Qt>
#include <QStyleOption>
#include <QPainter>

class ClickableWidget : public QWidget {
    Q_OBJECT

public:
    explicit ClickableWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~ClickableWidget();

    //for applying stylesheet in custom element
    void ClickableWidget::paintEvent(QPaintEvent * pE);

signals:
    void clicked(ClickableWidget* currentWidget);

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // CICKABLEWIDGET_H
