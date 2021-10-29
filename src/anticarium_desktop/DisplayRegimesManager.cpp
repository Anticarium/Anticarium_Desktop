#include "DisplayRegimesManager.h"

DisplayRegimesManager::DisplayRegimesManager(QObject* parent) : QObject(parent) {
}

void DisplayRegimesManager::initialize() {
    JTTP* jttp = JTTP::instance();
    connect(jttp, qOverload<const shared_types::SavedRegimes&>(&JTTP::dataReceivedEvent), this, qOverload<const shared_types::SavedRegimes&>(&DisplayRegimesManager::displayDataEvent));
    connect(jttp, qOverload<const shared_types::SavedRegimes&>(&JTTP::dataReceivedEvent), this, qOverload<const shared_types::SavedRegimes&>(&DisplayRegimesManager::onDataReceived));
    connect(this, &DisplayRegimesManager::requestDataEvent, jttp, &JTTP::onRequestData);

    emit requestDataEvent(JTTP::REQUEST_DATA::SAVED_REGIMES);
}

void DisplayRegimesManager::onDataReceived(const shared_types::SavedRegimes& savedRegimes) {
    this->savedRegimes = savedRegimes;
}

shared_types::Regime DisplayRegimesManager::getRegimeAt(int index) {
    return savedRegimes.getSavedRegimes()[index];
}
