#include "ui_mainwindow.h"
#include <anticarium_desktop/widgets/MainWindow.h>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    manager = new MainWindowManager(this);
    connect(manager, qOverload<const shared_types::SensorData&>(&MainWindowManager::displayDataEvent), this, qOverload<const shared_types::SensorData&>(&MainWindow::displayData));
    connect(manager, qOverload<const shared_types::TerrariumData&>(&MainWindowManager::displayDataEvent), this, qOverload<const shared_types::TerrariumData&>(&MainWindow::displayData));
    connectUiInputs();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::displayData(const shared_types::TerrariumData& terrariumData) {
    ui->modeLabel->setText(terrariumData.getCurrentRegime());
    displayData(terrariumData.getControl());
}

void MainWindow::displayData(const shared_types::Control& control) {
    disconnectUiInputs();
    ui->windSlider->setValue(control.getWindPercentage());
    ui->lightSlider->setValue(control.getLightPercentage());
    ui->heatSlider->setValue(control.getTemperature() * SLIDER_MULTIPLIER);
    ui->moistureSlider->setValue(control.getMoisturePercentage());

    connectUiInputs();
}

void MainWindow::displayData(const shared_types::SensorData& sensorData) {
    ui->temperatureValue->display(sensorData.getTemperature());
    ui->humidityValue->display(sensorData.getHumidity());
    ui->moistureValue->display(sensorData.getMoisture());
}

void MainWindow::connectUiInputs() {
    connect(ui->moistureSlider, &QSlider::valueChanged, manager, &MainWindowManager::onMoistureSliderMoved);
    connect(ui->heatSlider, &QSlider::valueChanged, manager, &MainWindowManager::onHeatSliderMoved);
    connect(ui->windSlider, &QSlider::valueChanged, manager, &MainWindowManager::onWindSliderMoved);
    connect(ui->lightSlider, &QSlider::valueChanged, manager, &MainWindowManager::onLightSliderMoved);
}

void MainWindow::disconnectUiInputs() {
    disconnect(ui->moistureSlider, &QSlider::valueChanged, manager, &MainWindowManager::onMoistureSliderMoved);
    disconnect(ui->heatSlider, &QSlider::valueChanged, manager, &MainWindowManager::onHeatSliderMoved);
    disconnect(ui->windSlider, &QSlider::valueChanged, manager, &MainWindowManager::onWindSliderMoved);
    disconnect(ui->lightSlider, &QSlider::valueChanged, manager, &MainWindowManager::onLightSliderMoved);
}
