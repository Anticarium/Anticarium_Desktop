#ifndef MAINWINDOWMANAGER_H
#define MAINWINDOWMANAGER_H

#include <Jttp.h>
#include <QObject>
#include <shared_types/Control.h>
#include <shared_types/SensorData.h>
#include <shared_types/TerrariumData.h>

class MainWindowManager : public QObject {
    Q_OBJECT
  public:
    MainWindowManager(QObject* parent = nullptr);
    // updates displayed values
    void sendControlData(const shared_types::Control& control);
    const shared_types::Control& getData() const;
    const shared_types::SensorData& getSensorData() const;
  signals:
    void sendDataEvent(const shared_types::Control& control);
    void requestDataEvent(JTTP::REQUEST_DATA requestData);
    void displayDataEvent(const shared_types::SensorData& newSensorData);
  private slots:

  private:
    shared_types::SensorData sensorData;
};

#endif // MAINWINDOWMANAGER_H
