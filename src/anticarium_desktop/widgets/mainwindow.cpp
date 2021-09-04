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
