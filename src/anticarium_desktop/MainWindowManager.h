#ifndef MAINWINDOWMANAGER_H
#define MAINWINDOWMANAGER_H

#include <anticarium_desktop/Jttp.h>
#include <shared_types/Control.h>
#include <shared_types/SensorData.h>
#include <shared_types/TerrariumData.h>

class MainWindowManager : public QObject {
    Q_OBJECT
  public:
    MainWindowManager(QObject* parent = nullptr);
    void sendData(const shared_types::Control& control);

  signals:
    void sendDataEvent(const shared_types::Control& control);
    void requestDataEvent(JTTP::REQUEST_DATA requestData);
    void displayDataEvent(const shared_types::SensorData& newSensorData);
    void displayDataEvent(const shared_types::TerrariumData& newTerrariumData);
  public slots:
    // slots for interface input
    void onAutoCheckBoxChanged(int state);
    void onMoistureSliderMoved(int value);
    void onHeatSliderMoved(int value);
    void onWindSliderMoved(int value);
    void onLightSliderMoved(int value);

    // Stores incoming Control data
    void onDataReceived(const shared_types::TerrariumData& terrariumData);

  private:
    shared_types::Control control;
};

#endif // MAINWINDOWMANAGER_H
