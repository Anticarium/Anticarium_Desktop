#pragma once

#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <nlohmann/json.hpp>
#include <shared_types/Control.h>
#include <shared_types/RegimeName.h>
#include <shared_types/Regimes.h>
#include <shared_types/SensorData.h>

class JTTP : public QObject {
    Q_OBJECT
  public:
    enum class REQUEST_DATA { CONTROL_DATA, SENSOR_DATA, REGIMES, REGIME_NAME };
    enum class REQUEST_TYPE { REQUEST, SEND };
    // singleton design pattern
    JTTP()       = delete;
    void operator=(const JTTP&) = delete;

    // Constructs and returns pointer to objet
    static JTTP* instance(QObject* parent);
    // Returns pointer to object
    static JTTP* instance();

  private:
    // private constructor for singleton
    JTTP(QObject* parent = nullptr);
    static JTTP* jttp;
    ~JTTP();

    // HTTP communication objects
    QNetworkAccessManager* networkAccessManager = nullptr;
    QNetworkRequest networkRequest;

    QMap<REQUEST_DATA, QString> requestDataMap = { { REQUEST_DATA::CONTROL_DATA, "control" }, { REQUEST_DATA::SENSOR_DATA, "sensor_data" }, { REQUEST_DATA::REGIMES, "regimes" },
        { REQUEST_DATA::REGIME_NAME, "regime_name" } };

    QMap<REQUEST_TYPE, QString> requestTypeMap = { { REQUEST_TYPE::REQUEST, "request" }, { REQUEST_TYPE::SEND, "send" } };

    // Builds url and does HTTP GET or POST
    void httpSend(REQUEST_TYPE requestType, REQUEST_DATA requestData, const nlohmann::json& passedJson = nlohmann::json());

    // POST data
    void post(QNetworkAccessManager* accessManager, const QNetworkRequest& networkRequest, const nlohmann::json& passedJson);
  signals:
    void dataReceivedEvent(const shared_types::SensorData& newSensorData);
    void dataReceivedEvent(const shared_types::Control& newControl);
    void dataReceivedEvent(const shared_types::RegimeName& newRegimeName);
    void dataReceivedEvent(const shared_types::Regimes& newRegimes);
  private slots:
    void onDataArrived(QNetworkReply* reply);
  public slots:
    void onSendData(const shared_types::Control& control);
    void onRequestData(REQUEST_DATA requestType);
};
