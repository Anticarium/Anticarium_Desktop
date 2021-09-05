#ifndef JTTP_H
#define JTTP_H

#include <QErrorMessage>
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>
#include <nlohmann/json.hpp>
#include <shared_types/TerrariumDataSerializer.hpp>

;

class JTTP : public QObject {
    Q_OBJECT
  public:
    enum class REQUEST_DATA { CONTROL_DATA, SENSOR_DATA, TERRARIUM_DATA, CURRENT_REGIME_DATA };
    enum class REQUEST_TYPE { REQUEST, SEND };
    // singleton design pattern
    JTTP()       = delete;
    void operator=(const JTTP&) = delete;

    // Constructs and returns pointer to objet
    static JTTP* getInstance(QObject* parent);
    // Returns pointer to object
    static JTTP* getInstance();

  private:
    // private constructor for singleton
    JTTP(QObject* parent = nullptr);
    static JTTP* jttp;
    ~JTTP();
    // timer object that pings server for new data every now and then
    QTimer* dataRequestTimer;

    // HTTP communication objects
    QNetworkAccessManager* networkAccessManager;

    QNetworkRequest networkRequest;

    QNetworkReply* sensorReply;

    QMap<REQUEST_DATA, QString> requestDataMap = { { REQUEST_DATA::CONTROL_DATA, "control_data" }, { REQUEST_DATA::SENSOR_DATA, "sensor_data" }, { REQUEST_DATA::TERRARIUM_DATA, "terrarium_data" },
        { REQUEST_DATA::CURRENT_REGIME_DATA, "current_regime_data" } };

    QMap<REQUEST_TYPE, QString> requestTypeMap = { { REQUEST_TYPE::REQUEST, "request" }, { REQUEST_TYPE::SEND, "send" } };

    // Builds url and does HTTP GET
    void executeGet(REQUEST_TYPE requestType, REQUEST_DATA requestData);

  signals:
    void getSensorDataEvent(const nlohmann::json& jData);
  private slots:
    void onDataArrived(QNetworkReply* reply);
  public slots:
    void onSendData(const shared_types::Control& control);
    void onRequestData(REQUEST_DATA requestType);
};

#endif // JTTP_H
