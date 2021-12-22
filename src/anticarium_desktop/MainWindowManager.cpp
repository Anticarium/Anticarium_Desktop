#include <QCoreApplication>
#include <QGraphicsItem>
#include <QTimer>
#include <anticarium_desktop/MainWindowManager.h>
#include <anticarium_desktop/VideoManager.h>
#include <anticarium_desktop/config/ApplicationSettings.h>
#include <anticarium_desktop/widgets/MainWindow.h>

MainWindowManager::MainWindowManager(QObject* parent) : QObject(parent) {
    videoScene = new QGraphicsScene(this);
}

MainWindowManager::~MainWindowManager() {
    videoManagerThread->quit();
    videoManagerThread->wait();
}

void MainWindowManager::sendData(const shared_types::Control& control) {
    emit sendDataEvent(control);
}

void MainWindowManager::initialize() {
    initializeVideoScene();
    initializeVideoManager();
    initializeJttp();
}

void MainWindowManager::sendMoistureValue(int value) {
    shared_types::RegimeValue regimeValue = control.getRegimeValue();
    regimeValue.setMoisture(value);
    control.setRegimeValue(regimeValue);
    sendData(control);
}

void MainWindowManager::sendHeatValue(int value) {
    shared_types::RegimeValue regimeValue = control.getRegimeValue();
    regimeValue.setTemperature(static_cast<float>(value) / MainWindow::SLIDER_MULTIPLIER);
    control.setRegimeValue(regimeValue);
    sendData(control);
}

void MainWindowManager::sendWindValue(int value) {
    control.setWindPercentage(value);
    sendData(control);
}

void MainWindowManager::sendLightValue(int value) {
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

void MainWindowManager::onDataReceived(const shared_types::Regime& regime) {
    shared_types::RegimeValue regimeValue = regime.getRegimeValue();
    control.setRegimeValue(regimeValue);
}

void MainWindowManager::updateImageRow(const ImageRow& row) {
    // Get current row
    auto currentRowItem = videoScene->items()[row.position];
    auto pixmapItem     = qgraphicsitem_cast<QGraphicsPixmapItem*>(currentRowItem);

    // Update row
    if (pixmapItem) {
        pixmapItem->setPixmap(row.pixmap);
    }
}

void MainWindowManager::initializeVideoScene() {
    auto settings = ApplicationSettings::instance();

    int width  = settings->getImageWidth();
    int height = settings->getImageHeight();

    // Create pixmap rows
    QSize size(width, 1);
    for (int i = 0; i < height; i++) {
        QPixmap pixmap(size);
        auto row = videoScene->addPixmap(pixmap);
        row->setOffset(0, i);
    }
}

void MainWindowManager::initializeJttp() {
    ApplicationSettings* settings = ApplicationSettings::instance();
    JTTP* jttp                    = JTTP::instance();
    QTimer* fetchTimer            = new QTimer(this);
    connect(this, qOverload<const shared_types::Control&>(&MainWindowManager::sendDataEvent), jttp, qOverload<const shared_types::Control&>(&JTTP::onSendData));
    connect(this, qOverload<const shared_types::RegimeId&>(&MainWindowManager::sendDataEvent), jttp, qOverload<const shared_types::RegimeId&>(&JTTP::onSendData));
    connect(fetchTimer, &QTimer::timeout, jttp, [&]() { emit requestDataEvent(JTTP::REQUEST_DATA::SENSOR_DATA); });
    connect(this, &MainWindowManager::requestDataEvent, jttp, &JTTP::onRequestData);
    connect(jttp, qOverload<const shared_types::Regimes&>(&JTTP::dataReceivedEvent), this,
            qOverload<const shared_types::Regimes&>(&MainWindowManager::displayDataEvent));
    connect(jttp, qOverload<const shared_types::RegimeId&>(&JTTP::dataReceivedEvent), this,
            qOverload<const shared_types::RegimeId&>(&MainWindowManager::displayDataEvent));
    connect(jttp, qOverload<const shared_types::SensorData&>(&JTTP::dataReceivedEvent), this,
            qOverload<const shared_types::SensorData&>(&MainWindowManager::displayDataEvent));
    connect(jttp, qOverload<const shared_types::Regime&>(&JTTP::dataReceivedEvent), this,
            qOverload<const shared_types::Regime&>(&MainWindowManager::displayDataEvent));
    connect(jttp, qOverload<const shared_types::Control&>(&JTTP::dataReceivedEvent), this,
            qOverload<const shared_types::Control&>(&MainWindowManager::displayDataEvent));
    connect(jttp, qOverload<const shared_types::Control&>(&JTTP::dataReceivedEvent), this,
            qOverload<const shared_types::Control&>(&MainWindowManager::onDataReceived));
    connect(jttp, qOverload<const shared_types::Regime&>(&JTTP::dataReceivedEvent), this,
            qOverload<const shared_types::Regime&>(&MainWindowManager::onDataReceived));
    fetchTimer->start(settings->getSensorDataFetchTimeout());

    // Request data for the first time on first time loading
    emit requestDataEvent(JTTP::REQUEST_DATA::SENSOR_DATA);
    emit requestDataEvent(JTTP::REQUEST_DATA::REGIMES);
    emit requestDataEvent(JTTP::REQUEST_DATA::CONTROL_DATA);
    emit requestDataEvent(JTTP::REQUEST_DATA::REGIME_ID);
}

void MainWindowManager::initializeVideoManager() {
    auto videoManager  = new VideoManager();
    videoManagerThread = new QThread(this);

    videoManager->moveToThread(videoManagerThread);

    connect(videoManagerThread, &QThread::started, videoManager, &VideoManager::run);
    connect(videoManager, &VideoManager::imageRowReadyEvent, this, &MainWindowManager::updateImageRow);

    videoManagerThread->start();
}

QGraphicsScene* MainWindowManager::getVideoScene() const {
    return videoScene;
}
