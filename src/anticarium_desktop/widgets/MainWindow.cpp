#include "MainWindow.h"
#include "ui_mainwindow.h"

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
    ui->heatToggle->setChecked(control.isHeating());
    ui->rainToggle->setChecked(control.isRaining());
    ui->autoToggle->setChecked(control.isAuto());
    connectUiInputs();
}

void MainWindow::displayData(const shared_types::SensorData& sensorData) {
    ui->temperatureValue->display(sensorData.getTemperature());
    ui->humidityValue->display(sensorData.getHumidity());
    ui->moistureValue->display(sensorData.getMoisture());
}

void MainWindow::connectUiInputs() {
    connect(ui->autoToggle, &QCheckBox::stateChanged, manager, &MainWindowManager::onAutoCheckBoxChanged);
    connect(ui->rainToggle, &QCheckBox::stateChanged, manager, &MainWindowManager::onRainToggleCheckBoxChanged);
    connect(ui->heatToggle, &QCheckBox::stateChanged, manager, &MainWindowManager::onHeatToggleCheckBoxChanged);
    connect(ui->windSlider, &QSlider::valueChanged, manager, &MainWindowManager::onWindSliderMoved);
    connect(ui->lightSlider, &QSlider::valueChanged, manager, &MainWindowManager::onLightSliderMoved);
}

void MainWindow::disconnectUiInputs() {
    disconnect(ui->autoToggle, &QCheckBox::stateChanged, manager, &MainWindowManager::onAutoCheckBoxChanged);
    disconnect(ui->rainToggle, &QCheckBox::stateChanged, manager, &MainWindowManager::onRainToggleCheckBoxChanged);
    disconnect(ui->heatToggle, &QCheckBox::stateChanged, manager, &MainWindowManager::onHeatToggleCheckBoxChanged);
    disconnect(ui->windSlider, &QSlider::valueChanged, manager, &MainWindowManager::onWindSliderMoved);
    disconnect(ui->lightSlider, &QSlider::valueChanged, manager, &MainWindowManager::onLightSliderMoved);
}
