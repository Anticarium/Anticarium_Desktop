#pragma once
#include <QObject>
#include <QSettings>

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

  private:
    static ApplicationSettings* applicationSettings;
    ApplicationSettings(const QString& directoryPath, QObject* parent = nullptr);

    QSettings* settings = nullptr;

    QString anticariumUrl;
    int sensorDataFetchTimeout = 0;
    int serverUDPPort          = 0;
    int imageWidth             = 0;
    int imageHeight            = 0;
};
