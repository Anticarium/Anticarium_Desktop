#include <anticarium_desktop/config/ApplicationSettings.h>
#include <shared_types/ControlSerializer.hpp>

ApplicationSettings* ApplicationSettings::applicationSettings = nullptr;

ApplicationSettings::ApplicationSettings(const QString& directoryPath, QObject* parent) : QObject(parent) {
    settings               = new QSettings(directoryPath, QSettings::IniFormat, this);
    anticariumUrl          = settings->value("Anticarium_Server_URL", "").toString();
    sensorDataFetchTimeout = settings->value("Sensor_Data_fetch_timeout", 5000).toInt();
}

ApplicationSettings* ApplicationSettings::instance(const QString& directoryPath, QObject* parent) {
    if (!applicationSettings) {
        applicationSettings = new ApplicationSettings(directoryPath, parent);
    }
    return applicationSettings;
}

ApplicationSettings* ApplicationSettings::instance() {
    return applicationSettings;
}

ApplicationSettings::~ApplicationSettings() {
    applicationSettings = nullptr;
}

QString ApplicationSettings::getAnticariumUrl() {
    return anticariumUrl;
}

int ApplicationSettings::getSensorDataFetchTimeout() {
    return sensorDataFetchTimeout;
}
