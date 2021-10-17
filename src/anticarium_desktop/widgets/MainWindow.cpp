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
    ui->saveButton->setEnabled(false);
}

void MainWindow::onEnableSaveButton(int value) {
    disconnectUiInputs();
    ui->saveButton->setEnabled(true);
    ui->modeLabel->setText("Custom");
    ui->regimeList->setCurrentIndex(-1);
    connectUiInputs();
}

void MainWindow::onMoistureSliderMoved(int value) {
    ui->moistureLabel->setText(QString("%1%").arg(QString::number(value)));
}

void MainWindow::onHeatSliderMoved(int value) {
    QString stringValue;
    float displayFloat = value / static_cast<float>(SLIDER_MULTIPLIER);
    stringValue.sprintf("%.1f°C", displayFloat);
    ui->heatLabel->setText(stringValue);
}

void MainWindow::onWindSliderMoved(int value) {
    ui->windLabel->setText(QString("%1%").arg(QString::number(value)));
}

void MainWindow::onLightSliderMoved(int value) {
    ui->lightLabel->setText(QString("%1%").arg(QString::number(value)));
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
    connect(ui->moistureSlider, &QSlider::valueChanged, this, &MainWindow::onMoistureSliderMoved);
    connect(ui->moistureSlider, &QSlider::valueChanged, this, &MainWindow::onEnableSaveButton);
    connect(ui->heatSlider, &QSlider::valueChanged, manager, &MainWindowManager::onHeatSliderMoved);
    connect(ui->heatSlider, &QSlider::valueChanged, this, &MainWindow::onHeatSliderMoved);
    connect(ui->heatSlider, &QSlider::valueChanged, this, &MainWindow::onEnableSaveButton);
    connect(ui->windSlider, &QSlider::valueChanged, manager, &MainWindowManager::onWindSliderMoved);
    connect(ui->windSlider, &QSlider::valueChanged, this, &MainWindow::onWindSliderMoved);
    connect(ui->lightSlider, &QSlider::valueChanged, manager, &MainWindowManager::onLightSliderMoved);
    connect(ui->lightSlider, &QSlider::valueChanged, this, &MainWindow::onLightSliderMoved);
    connect(ui->regimeList, &QComboBox::textActivated, manager, &MainWindowManager::onRegimeListChoice);
}

void MainWindow::disconnectUiInputs() {
    disconnect(ui->moistureSlider, &QSlider::valueChanged, manager, &MainWindowManager::onMoistureSliderMoved);
    disconnect(ui->moistureSlider, &QSlider::valueChanged, this, &MainWindow::onEnableSaveButton);
    disconnect(ui->heatSlider, &QSlider::valueChanged, manager, &MainWindowManager::onHeatSliderMoved);
    disconnect(ui->heatSlider, &QSlider::valueChanged, this, &MainWindow::onEnableSaveButton);
    disconnect(ui->windSlider, &QSlider::valueChanged, manager, &MainWindowManager::onWindSliderMoved);
    disconnect(ui->lightSlider, &QSlider::valueChanged, manager, &MainWindowManager::onLightSliderMoved);
    disconnect(ui->regimeList, &QComboBox::textActivated, manager, &MainWindowManager::onRegimeListChoice);
}
