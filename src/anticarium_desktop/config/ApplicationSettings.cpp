#include <anticarium_desktop/config/ApplicationSettings.h>
#include <shared_types/ControlSerializer.hpp>
ApplicationSettings* ApplicationSettings::applicationSettings = nullptr;

ApplicationSettings::ApplicationSettings(const QString& directoryPath, QObject* parent) : QObject(parent) {
    settings               = new QSettings(directoryPath, QSettings::IniFormat, this);
    anticariumUrl          = settings->value("Anticarium_Server_URL", "").toString();
    sensorDataFetchTimeout = settings->value("Sensor_Data_fetch_timeout", 5000).toInt();
    serverUDPPort          = settings->value("Server_UDP_Port", 0).toInt();
    imageWidth             = settings->value("Image_Width", 0).toInt();
    imageHeight            = settings->value("Image_Height", 0).toInt();
}

int ApplicationSettings::getImageHeight() const {
    return imageHeight;
}

int ApplicationSettings::getImageWidth() const {
    return imageWidth;
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

QString ApplicationSettings::getAnticariumUrl() const {
    return anticariumUrl;
}

int ApplicationSettings::getSensorDataFetchTimeout() const {
    return sensorDataFetchTimeout;
}

int ApplicationSettings::getServerUDPPort() const {
    return serverUDPPort;
}
