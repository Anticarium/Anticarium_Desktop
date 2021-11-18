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

    QString getAnticariumUrl();
    int getSensorDataFetchTimeout();

  private:
    static ApplicationSettings* applicationSettings;
    ApplicationSettings(const QString& directoryPath, QObject* parent = nullptr);

    QSettings* settings = nullptr;

    QString anticariumUrl;
    int sensorDataFetchTimeout = 0;
};
