#include "ui_mainwindow.h"
#include <QDebug>
#include <anticarium_desktop/widgets/MainWindow.h>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    manager = new MainWindowManager(this);
    connect(manager, qOverload<const shared_types::SensorData&>(&MainWindowManager::displayDataEvent), this, qOverload<const shared_types::SensorData&>(&MainWindow::displayData));
    connect(manager, qOverload<const shared_types::Control&>(&MainWindowManager::displayDataEvent), this, qOverload<const shared_types::Control&>(&MainWindow::displayData));
    connect(manager, qOverload<const shared_types::RegimeName&>(&MainWindowManager::displayDataEvent), this, qOverload<const shared_types::RegimeName&>(&MainWindow::displayData));
    connect(manager, qOverload<const shared_types::Regimes&>(&MainWindowManager::displayDataEvent), this, qOverload<const shared_types::Regimes&>(&MainWindow::displayData));
    connect(manager, qOverload<const shared_types::Regime&>(&MainWindowManager::displayDataEvent), this, qOverload<const shared_types::Regime&>(&MainWindow::displayData));
    connectUiInputs();

    manager->initialize();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::displayData(const shared_types::RegimeName& regimeName) {
    disconnectUiInputs();
    ui->modeLabel->setText(regimeName.getName());
    connectUiInputs();
}

void MainWindow::displayData(const shared_types::RegimeValue& regimeValue) {
    disconnectUiInputs();
    ui->heatSlider->setValue(regimeValue.getTemperature() * SLIDER_MULTIPLIER);
    ui->moistureSlider->setValue(regimeValue.getMoisture());
    connectUiInputs();
}

void MainWindow::displayData(const shared_types::Regime& regime) {
    displayData(regime.getRegimeName());
    displayData(regime.getRegimeValue());
}

void MainWindow::displayData(const shared_types::Control& control) {
    disconnectUiInputs();
    ui->windSlider->setValue(control.getWindPercentage());
    ui->lightSlider->setValue(control.getLightPercentage());
    displayData(control.getRegimeValue());
    connectUiInputs();
}

void MainWindow::displayData(const shared_types::SensorData& sensorData) {
    disconnectUiInputs();
    ui->temperatureValue->display(sensorData.getTemperature());
    ui->humidityValue->display(sensorData.getHumidity());
    ui->moistureValue->display(sensorData.getMoisture());
    connectUiInputs();
}

void MainWindow::displayData(const shared_types::Regimes& regimes) {
    disconnectUiInputs();
    ui->regimeList->clear();
    std::vector<QString> regimesVector = regimes.getRegimes();
    for (const QString& i : regimesVector) {
        ui->regimeList->addItem(i);
    }

    int regimeListId = ui->regimeList->findText(ui->modeLabel->text());
    if (regimeListId != -1) {
        ui->regimeList->setCurrentIndex(regimeListId);
    }
    connectUiInputs();
}

void MainWindow::connectUiInputs() {
    connect(ui->moistureSlider, &QSlider::valueChanged, manager, &MainWindowManager::onMoistureSliderMoved);
    connect(ui->heatSlider, &QSlider::valueChanged, manager, &MainWindowManager::onHeatSliderMoved);
    connect(ui->windSlider, &QSlider::valueChanged, manager, &MainWindowManager::onWindSliderMoved);
    connect(ui->lightSlider, &QSlider::valueChanged, manager, &MainWindowManager::onLightSliderMoved);
    connect(ui->regimeList, &QComboBox::textActivated, manager, &MainWindowManager::onRegimeListChoice);
}

void MainWindow::disconnectUiInputs() {
    disconnect(ui->moistureSlider, &QSlider::valueChanged, manager, &MainWindowManager::onMoistureSliderMoved);
    disconnect(ui->heatSlider, &QSlider::valueChanged, manager, &MainWindowManager::onHeatSliderMoved);
    disconnect(ui->windSlider, &QSlider::valueChanged, manager, &MainWindowManager::onWindSliderMoved);
    disconnect(ui->lightSlider, &QSlider::valueChanged, manager, &MainWindowManager::onLightSliderMoved);
    disconnect(ui->regimeList, &QComboBox::textActivated, manager, &MainWindowManager::onRegimeListChoice);
}
