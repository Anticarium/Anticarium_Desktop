#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget* parent)
: QMainWindow(parent), ui(new Ui::MainWindow),
  settings(new QSettings(QSettings::Format::IniFormat, QSettings::Scope::SystemScope, QCoreApplication::organizationName(), QCoreApplication::applicationName())) {
    // instanciate the singleton
    jttp = JTTP::getInstance();

    ui->setupUi(this);

    // updates displayed values
    //    connect(jttp, &JTTP::updateSensorDisplay, homeTab, &HomeTab::updateSensorDisplay);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onSetupData(const shared_types::TerrariumData& terrariumData) {
    ui->modeLabel->setText(terrariumData.getCurrentRegime());
    onControlUpdate(terrariumData.getControl());
}

void MainWindow::onControlUpdate(const shared_types::Control& control) {
    ui->windSlider->setValue(control.getWindPercentage());
    ui->lightSlider->setValue(control.getLightPercentage());
    ui->heatToggle->setChecked(control.isHeating());
    ui->rainToggle->setChecked(control.isRaining());
    ui->autoToggle->setChecked(control.isAuto());
}

void MainWindow::onSensorDataUpdate(const shared_types::SensorData& sensorData) {
    ui->temperatureValue->display(sensorData.getTemperature());
    ui->humidityValue->display(sensorData.getHumidity());
    ui->moistureValue->display(sensorData.getMoisture());
}
