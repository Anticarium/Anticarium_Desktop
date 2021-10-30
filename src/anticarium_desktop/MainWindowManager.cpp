#include <QCoreApplication>
#include <QTimer>
#include <anticarium_desktop/MainWindowManager.h>
#include <anticarium_desktop/widgets/MainWindow.h>

MainWindowManager::MainWindowManager(QObject* parent) : QObject(parent) {
}

void MainWindowManager::sendData(const shared_types::Control& control) {
    this->control = control;
    emit sendDataEvent(control);
}

void MainWindowManager::initialize() {
    JTTP* jttp         = JTTP::instance();
    QTimer* fetchTimer = new QTimer(this);
    connect(this, qOverload<const shared_types::Control&>(&MainWindowManager::sendDataEvent), jttp, qOverload<const shared_types::Control&>(&JTTP::onSendData));
    connect(this, qOverload<const shared_types::RegimeId&>(&MainWindowManager::sendDataEvent), jttp, qOverload<const shared_types::RegimeId&>(&JTTP::onSendData));
    connect(fetchTimer, &QTimer::timeout, jttp, [&]() { emit requestDataEvent(JTTP::REQUEST_DATA::SENSOR_DATA); });
    connect(this, &MainWindowManager::requestDataEvent, jttp, &JTTP::onRequestData);
    connect(jttp, qOverload<const shared_types::Regimes&>(&JTTP::dataReceivedEvent), this, qOverload<const shared_types::Regimes&>(&MainWindowManager::displayDataEvent));
    connect(jttp, qOverload<const shared_types::RegimeId&>(&JTTP::dataReceivedEvent), this, qOverload<const shared_types::RegimeId&>(&MainWindowManager::displayDataEvent));
    connect(jttp, qOverload<const shared_types::SensorData&>(&JTTP::dataReceivedEvent), this, qOverload<const shared_types::SensorData&>(&MainWindowManager::displayDataEvent));
    connect(jttp, qOverload<const shared_types::Regime&>(&JTTP::dataReceivedEvent), this, qOverload<const shared_types::Regime&>(&MainWindowManager::displayDataEvent));
    connect(jttp, qOverload<const shared_types::Control&>(&JTTP::dataReceivedEvent), this, qOverload<const shared_types::Control&>(&MainWindowManager::displayDataEvent));
    connect(jttp, qOverload<const shared_types::Control&>(&JTTP::dataReceivedEvent), this, qOverload<const shared_types::Control&>(&MainWindowManager::onDataReceived));
    fetchTimer->start(5000);

    // Request data for the first time on first time loading
    emit requestDataEvent(JTTP::REQUEST_DATA::SENSOR_DATA);
    emit requestDataEvent(JTTP::REQUEST_DATA::REGIMES);
    emit requestDataEvent(JTTP::REQUEST_DATA::REGIME_ID);
    emit requestDataEvent(JTTP::REQUEST_DATA::CONTROL_DATA);
}

void MainWindowManager::onMoistureSliderMoved(int value) {
    control.getRegimeValue().setMoisture(value);
    sendData(control);
}

void MainWindowManager::onHeatSliderMoved(int value) {
    control.getRegimeValue().setTemperature(value / MainWindow::SLIDER_MULTIPLIER);
    sendData(control);
}

void MainWindowManager::onWindSliderMoved(int value) {
    control.setWindPercentage(value);
    sendData(control);
}

void MainWindowManager::onLightSliderMoved(int value) {
    control.setLightPercentage(value);
    sendData(control);
}

void MainWindowManager::onRegimeListActivated(int index) {
    shared_types::RegimeId regimeId;
    regimeId.setId(index);
    emit sendDataEvent(regimeId);
    emit requestDataEvent(JTTP::REQUEST_DATA::REGIME);
}

void MainWindowManager::onDataReceived(const shared_types::Control& control) {
    this->control = control;
}
