#ifndef HOMETAB_H
#define HOMETAB_H

#include <QWidget>
#include "jttp.h"
#include <iostream>
#include <QPushButton>
#include <QButtonGroup>

namespace Ui {
class HomeTab;
}

class HomeTab : public QWidget
{
    Q_OBJECT

public:
    explicit HomeTab(QWidget *parent = nullptr, JTTP * jttp = nullptr);
    ~HomeTab();
    //returns auto button object pointer
    QPushButton * getAutoButton() const;
private:
    Ui::HomeTab *ui;
    //autobutton pointer
    QPushButton * aB;
    JTTP * _jttp;
public slots:
    //updates displayed values
    void updateSensorDisplay(const json& jData);
    void autoPressed();
};

#endif // HOMETAB_H
