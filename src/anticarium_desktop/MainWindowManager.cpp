#include "MainWindowManager.h"
#include <QTimer>

MainWindowManager::MainWindowManager(QObject* parent) : QObject(parent) {
    JTTP* jttp         = JTTP::instance();
    QTimer* fetchTimer = new QTimer(this);

    connect(this, &MainWindowManager::sendDataEvent, jttp, &JTTP::onSendData);
    connect(fetchTimer, &QTimer::timeout, jttp, [&]() { emit requestDataEvent(JTTP::REQUEST_DATA::SENSOR_DATA); });
    connect(this, &MainWindowManager::requestDataEvent, jttp, &JTTP::onRequestData);
    connect(jttp, &JTTP::dataReceivedEvent, this, &MainWindowManager::displayDataEvent);
    fetchTimer->start(5000);
}

void MainWindowManager::sendControlData(const shared_types::Control& control) {
    emit sendDataEvent(control);
}

const shared_types::Control& MainWindowManager::getData() const {
}

const shared_types::SensorData& MainWindowManager::getSensorData() const {
    return sensorData;
}
