#pragma once

#include <QGraphicsScene>
#include <QThread>
#include <anticarium_desktop/Jttp.h>
#include <anticarium_desktop/config/ImageRow.hpp>
#include <shared_types/Control.h>
#include <shared_types/Regime.h>
#include <shared_types/Regimes.h>
#include <shared_types/SensorData.h>

class MainWindowManager : public QObject {
    Q_OBJECT
  public:
    MainWindowManager(QObject* parent = nullptr);
    ~MainWindowManager();
    void sendData(const shared_types::Control& control);
    void initialize();

    void sendMoistureValue(int value);
    void sendHeatValue(int value);
    void sendWindValue(int value);
    void sendLightValue(int value);

    QGraphicsScene* getVideoScene() const;

  signals:
    void sendDataEvent(const shared_types::Control& control);
    void sendDataEvent(const shared_types::RegimeId& regimeId);
    void requestDataEvent(JTTP::REQUEST_DATA requestData);
    void displayDataEvent(const shared_types::SensorData& newSensorData);
    void displayDataEvent(const shared_types::Regimes& newRegimes);
    void displayDataEvent(const shared_types::Control& newControl);
    void displayDataEvent(const shared_types::RegimeId& newRegimeId);
    void displayDataEvent(const shared_types::Regime& newRegime);

  public slots:
    void onRegimeListActivated(int index);
    // Stores incoming Control data
    void onDataReceived(const shared_types::Control& control);
    // Stores RegimeData in this->control from incoming Regime
    void onDataReceived(const shared_types::Regime& regime);

  private:
    void updateImageRow(const ImageRow& row);

    void initializeVideoScene();
    void initializeJttp();
    void initializeVideoManager();
    shared_types::Control control;

    QThread* videoManagerThread = nullptr;

    QGraphicsScene* videoScene = nullptr;
};
