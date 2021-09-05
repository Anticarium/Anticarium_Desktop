#include "MainWindowManager.h"

MainWindowManager::MainWindowManager(QObject* parent) : QObject(parent) {
    JTTP* jttp = JTTP::getInstance();
    connect(this, &MainWindowManager::sendData, jttp, &JTTP::onSendData);
}

void MainWindowManager::sendControlData(const shared_types::Control& control) {
    emit sendData(control);
}

const shared_types::Control& MainWindowManager::getData() const {
}
