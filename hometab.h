#ifndef HOMETAB_H
#define HOMETAB_H

#include <QWidget>
#include "jttp.h"
#include <iostream>

namespace Ui {
class HomeTab;
}

class HomeTab : public QWidget
{
    Q_OBJECT

public:
    explicit HomeTab(QWidget *parent = nullptr);
    ~HomeTab();

private:
    Ui::HomeTab *ui;

public slots:
    //updates displayed values
    void updateSensorDisplay(const json& jData);
};

#endif // HOMETAB_H
