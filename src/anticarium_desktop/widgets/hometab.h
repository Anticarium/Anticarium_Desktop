#pragma once

#include "jttp.h"
#include <QWidget>
#include <iostream>

namespace Ui {
class HomeTab;
}

class HomeTab : public QWidget {
    Q_OBJECT

  public:
    explicit HomeTab(QWidget* parent = nullptr);
    ~HomeTab();

  private:
    Ui::HomeTab* ui;

  public slots:
    // updates displayed values
    void updateSensorDisplay(const nlohmann::json& jData);
};
