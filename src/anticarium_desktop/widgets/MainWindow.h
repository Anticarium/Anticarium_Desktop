#pragma once

#include <MainWindowManager.h>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  public slots:
    void displayData(const shared_types::TerrariumData& terrariumData);
    void displayData(const shared_types::Control& control);
    void displayData(const shared_types::SensorData& sensorData);

  private:
    Ui::MainWindow* ui;
    MainWindowManager* manager = nullptr;
    void connectUiInputs();
    void disconnectUiInputs();
};
