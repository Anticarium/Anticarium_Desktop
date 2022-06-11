#include <anticarium_desktop/DisplayRegimesManager.h>

DisplayRegimesManager::DisplayRegimesManager(QObject* parent) : QObject(parent) {
}

void DisplayRegimesManager::initialize() {
    auto jttp = JTTP::instance();
    connect(jttp, qOverload<const shared_types::SavedRegimes&>(&JTTP::dataReceivedEvent), this,
            qOverload<const shared_types::SavedRegimes&>(&DisplayRegimesManager::displayDataEvent));
    connect(jttp, qOverload<const shared_types::SavedRegimes&>(&JTTP::dataReceivedEvent), this,
            qOverload<const shared_types::SavedRegimes&>(&DisplayRegimesManager::onDataReceived));
    connect(this, &DisplayRegimesManager::sendDataEvent, jttp, qOverload<const shared_types::RegimeId&>(&JTTP::onSendData));
    connect(this, &DisplayRegimesManager::requestDataEvent, jttp, &JTTP::onRequestData);

    emit requestDataEvent(JTTP::REQUEST_DATA::SAVED_REGIMES);
}

void DisplayRegimesManager::deleteRegime(int id) {
    shared_types::RegimeId regimeId;
    regimeId.setId(id + DELETION_START);
    emit sendDataEvent(regimeId);
}

void DisplayRegimesManager::onDataReceived(const shared_types::SavedRegimes& savedRegimes) {
    this->savedRegimes = savedRegimes;
}

shared_types::Regime DisplayRegimesManager::getRegimeAt(int index) {
    return savedRegimes.getSavedRegimes()[index];
}
