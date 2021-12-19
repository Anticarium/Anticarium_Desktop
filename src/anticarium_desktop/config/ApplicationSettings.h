#pragma once
#include <QObject>
#include <QSettings>
#include <spdlog/spdlog.h>

class ApplicationSettings : public QObject {
    Q_OBJECT
  public:
    ApplicationSettings() = delete;
    void operator=(const ApplicationSettings&) = delete;
    static ApplicationSettings* instance(const QString& directoryPath, QObject* parent = nullptr);
    static ApplicationSettings* instance();
    virtual ~ApplicationSettings();

    QString getAnticariumUrl() const;
    int getSensorDataFetchTimeout() const;
    int getServerUDPPort() const;
    int getImageWidth() const;
    int getImageHeight() const;
    const QString& getAnticariumUDPUrl() const;
    spdlog::level::level_enum getLogLevel() const;

  private:
    static ApplicationSettings* applicationSettings;
    ApplicationSettings(const QString& directoryPath, QObject* parent = nullptr);

    QSettings* settings = nullptr;

    QString anticariumUrl;
    QString anticariumUDPUrl;
    int sensorDataFetchTimeout         = 0;
    int serverUDPPort                  = 0;
    int imageWidth                     = 0;
    int imageHeight                    = 0;
    spdlog::level::level_enum logLevel = spdlog::level::trace;
};
