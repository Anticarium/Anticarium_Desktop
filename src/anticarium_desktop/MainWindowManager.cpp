#include <QTimer>
#include <anticarium_desktop/MainWindowManager.h>
#include <anticarium_desktop/widgets/MainWindow.h>

MainWindowManager::MainWindowManager(QObject* parent) : QObject(parent) {
    JTTP* jttp         = JTTP::instance();
    QTimer* fetchTimer = new QTimer(this);

    connect(this, &MainWindowManager::sendDataEvent, jttp, &JTTP::onSendData);
    connect(fetchTimer, &QTimer::timeout, jttp, [&]() { emit requestDataEvent(JTTP::REQUEST_DATA::SENSOR_DATA); });
    connect(this, &MainWindowManager::requestDataEvent, jttp, &JTTP::onRequestData);
    connect(jttp, qOverload<const shared_types::SensorData&>(&JTTP::dataReceivedEvent), this, qOverload<const shared_types::SensorData&>(&MainWindowManager::displayDataEvent));
    connect(jttp, qOverload<const shared_types::TerrariumData&>(&JTTP::dataReceivedEvent), this, qOverload<const shared_types::TerrariumData&>(&MainWindowManager::displayDataEvent));
    connect(jttp, qOverload<const shared_types::TerrariumData&>(&JTTP::dataReceivedEvent), this, qOverload<const shared_types::TerrariumData&>(&MainWindowManager::onDataReceived));
    fetchTimer->start(5000);

    // Request data for the first time on first time loading
    emit requestDataEvent(JTTP::REQUEST_DATA::TERRARIUM_DATA);
}

void MainWindowManager::sendData(const shared_types::Control& control) {
    this->control = control;
    emit sendDataEvent(control);
}

void MainWindowManager::onAutoCheckBoxChanged(int state) {
    control.setIsAuto(state);
    sendData(control);
}

void MainWindowManager::onMoistureSliderMoved(int value) {
    control.setMoisturePercentage(value);
    sendData(control);
}

void MainWindowManager::onHeatSliderMoved(int value) {
    control.setTemperature(value / MainWindow::SLIDER_MULTIPLIER);
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

void MainWindowManager::onDataReceived(const shared_types::TerrariumData& terrariumData) {
    control = terrariumData.getControl();
}
