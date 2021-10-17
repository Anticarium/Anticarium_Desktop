#ifndef MAINWINDOWMANAGER_H
#define MAINWINDOWMANAGER_H

#include <anticarium_desktop/Jttp.h>
#include <shared_types/Control.h>
#include <shared_types/Regime.h>
#include <shared_types/Regimes.h>
#include <shared_types/SensorData.h>

class MainWindowManager : public QObject {
    Q_OBJECT
  public:
    MainWindowManager(QObject* parent = nullptr);
    void sendData(const shared_types::Control& control);

  signals:
    void sendDataEvent(const shared_types::Control& control);
    void sendDataEvent(const shared_types::RegimeName& regimeName);
    void requestDataEvent(JTTP::REQUEST_DATA requestData);
    void displayDataEvent(const shared_types::SensorData& newSensorData);
    void displayDataEvent(const shared_types::Regimes& newRegimes);
    void displayDataEvent(const shared_types::Control& newControl);
    void displayDataEvent(const shared_types::RegimeName& newRegimeName);
    void displayDataEvent(const shared_types::Regime& newRegime);
  public slots:
    void onMoistureSliderMoved(int value);
    void onHeatSliderMoved(int value);
    void onWindSliderMoved(int value);
    void onLightSliderMoved(int value);
    void onRegimeListChoice(const QString& currentText);

    // Stores incoming Control data
    void onDataReceived(const shared_types::Control& control);

  private:
    shared_types::Control control;
};

#endif // MAINWINDOWMANAGER_H
