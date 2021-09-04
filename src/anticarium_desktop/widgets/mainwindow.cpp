#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget* parent)
: QMainWindow(parent), ui(new Ui::MainWindow),
  _settings(new QSettings(QSettings::Format::IniFormat, QSettings::Scope::SystemScope, QCoreApplication::organizationName(), QCoreApplication::applicationName())) {
    // instanciate the singleton
    jttp = JTTP::GetInstance(parent, _settings);

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
}

void MainWindow::onSensorDataUpdate(const shared_types::SensorData& sensorData) {
    ui->temperatureValue->display(sensorData.getTemperature());
    ui->humidityValue->display(sensorData.getHumidity());
    ui->moistureValue->display(sensorData.getMoisture());
}
