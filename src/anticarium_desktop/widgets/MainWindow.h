#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Jttp.h"
#include <MainWindowManager.h>
#include <QMainWindow>
#include <QSettings>

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
    // makes HTTP calls to the server and processes received data
    JTTP* jttp                 = nullptr;
    MainWindowManager* manager = nullptr;
    void connectUiInputs();
    void disconnectUiInputs();
};
#endif // MAINWINDOW_H
