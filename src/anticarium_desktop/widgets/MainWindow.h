#pragma once

#include <QMainWindow>
#include <anticarium_desktop/MainWindowManager.h>

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
    static const int SLIDER_MULTIPLIER = 10;
  public slots:
    void displayData(const shared_types::Regimes& regimes);
    void displayData(const shared_types::Control& control);
    void displayData(const shared_types::SensorData& sensorData);
    void displayData(const shared_types::RegimeName& regimeName);
    void displayData(const shared_types::Regime& regime);
    void displayData(const shared_types::RegimeValue& regimeValue);
  private slots:
    void onEnableSaveButton(int value);
    void onMoistureSliderMoved(int value);
    void onHeatSliderMoved(int value);
    void onWindSliderMoved(int value);
    void onLightSliderMoved(int value);

  private:
    Ui::MainWindow* ui;
    MainWindowManager* manager = nullptr;
    void connectUiInputs();
    void disconnectUiInputs();
};
