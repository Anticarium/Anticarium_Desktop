#pragma once

#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <nlohmann/json.hpp>
#include <shared_types/Control.h>
#include <shared_types/Regime.h>
#include <shared_types/RegimeId.h>
#include <shared_types/Regimes.h>
#include <shared_types/SavedRegimes.h>
#include <shared_types/SensorData.h>

class JTTP : public QObject {
    Q_OBJECT
  public:
    enum class REQUEST_DATA { CONTROL_DATA, SENSOR_DATA, REGIMES, REGIME_ID, REGIME, SAVED_REGIMES };
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
        { REQUEST_DATA::REGIME_ID, "regime_id" }, { REQUEST_DATA::REGIME, "regime" }, { REQUEST_DATA::SAVED_REGIMES, "saved_regimes" } };

    QMap<REQUEST_TYPE, QString> requestTypeMap = { { REQUEST_TYPE::REQUEST, "request" }, { REQUEST_TYPE::SEND, "send" } };

    // Builds url and does HTTP GET or POST
    void httpSend(REQUEST_TYPE requestType, REQUEST_DATA requestData, const nlohmann::json& passedJson = nlohmann::json());

  signals:
    void dataReceivedEvent(const shared_types::SensorData& newSensorData);
    void dataReceivedEvent(const shared_types::Control& newControl);
    void dataReceivedEvent(const shared_types::RegimeId& newRegimeId);
    void dataReceivedEvent(const shared_types::Regimes& newRegimes);
    void dataReceivedEvent(const shared_types::Regime& newRegime);
    void dataReceivedEvent(const shared_types::SavedRegimes& newSavedRegimes);

  private slots:
    void onDataArrived(QNetworkReply* reply);
  public slots:
    void onSendData(const shared_types::Regime& regime);
    void onSendData(const shared_types::Control& control);
    void onSendData(const shared_types::RegimeId& regimeId);
    void onRequestData(REQUEST_DATA requestType);
};
