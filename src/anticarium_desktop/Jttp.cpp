#include <QCoreApplication>
#include <QHttpMultiPart>
#include <anticarium_desktop/Jttp.h>
#include <shared_types/ControlSerializer.hpp>
#include <shared_types/RegimeIdSerializer.hpp>
#include <shared_types/RegimeSerializer.hpp>
#include <shared_types/RegimesSerializer.hpp>
#include <shared_types/SavedRegimesSerializer.hpp>
#include <shared_types/SensorDataSerializer.hpp>
#include <spdlog/spdlog.h>

JTTP::JTTP(QObject* parent) : QObject(parent) {
    networkAccessManager = new QNetworkAccessManager(this);
    connect(networkAccessManager, &QNetworkAccessManager::finished, this, &JTTP::onDataArrived);
}

JTTP* JTTP::jttp = nullptr;

JTTP* JTTP::instance() {
    return jttp;
}

JTTP* JTTP::instance(QObject* parent) {
    if (jttp == nullptr) {
        jttp = new JTTP(parent);
    }
    return jttp;
}

void JTTP::onDataArrived(QNetworkReply* reply) {
    QString content = "";
    // checks if reply contains legitimate data
    if (reply->error()) {
        SPDLOG_ERROR(QString("QNetworkError: %1").arg(reply->errorString()).toStdString());
        return;
    } else {
        content = reply->rawHeader("Anticarium_content_description");
        SPDLOG_INFO(QString("Data arrived").toStdString());
    }

    // reads reply into QString
    QString answer = reply->readAll();
    nlohmann::json jsonReply;
    if (content == "Sensor data") {
        jsonReply = nlohmann::json::parse(answer.toStdString());

        shared_types::SensorData sensorData = jsonReply;
        emit dataReceivedEvent(sensorData);
    } else if (content == "Control") {
        jsonReply = nlohmann::json::parse(answer.toStdString());

        shared_types::Control control = jsonReply;
        emit dataReceivedEvent(control);
    } else if (content == "Regimes") {
        jsonReply = nlohmann::json::parse(answer.toStdString());

        shared_types::Regimes regimes = jsonReply;
        emit dataReceivedEvent(regimes);
    } else if (content == "Regime id") {
        jsonReply = nlohmann::json::parse(answer.toStdString());

        shared_types::RegimeId regimeId = jsonReply;
        emit dataReceivedEvent(regimeId);
    } else if (content == "Regime") {
        jsonReply = nlohmann::json::parse(answer.toStdString());

        shared_types::Regime regime = jsonReply;
        emit dataReceivedEvent(regime);
    } else if (content == "Saved regimes") {
        jsonReply = nlohmann::json::parse(answer.toStdString());

        shared_types::SavedRegimes savedRegimes = jsonReply;
        emit dataReceivedEvent(savedRegimes);
    }
}

void JTTP::onSendData(const shared_types::Regime& regime) {
    httpSend(REQUEST_TYPE::SEND, REQUEST_DATA::REGIME, regime);
}

void JTTP::onSendData(const shared_types::Control& control) {
    httpSend(REQUEST_TYPE::SEND, REQUEST_DATA::CONTROL_DATA, control);
}

void JTTP::onSendData(const shared_types::RegimeId& regimeId) {
    httpSend(REQUEST_TYPE::SEND, REQUEST_DATA::REGIME_ID, regimeId);
}

void JTTP::onRequestData(REQUEST_DATA requestType) {
    httpSend(REQUEST_TYPE::REQUEST, requestType);
}

void JTTP::httpSend(REQUEST_TYPE requestType, REQUEST_DATA requestData, const nlohmann::json& passedJson) {
    QString requestTypeString = requestTypeMap[requestType];
    QString requestDataString = requestDataMap[requestData];
    QString url               = QString("http://192.168.1.100:5000/%1/%2").arg(requestTypeString).arg(requestDataString);
    QNetworkRequest networkRequest;
    networkRequest.setUrl(url);

    if (requestType == REQUEST_TYPE::SEND) {
        networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        networkAccessManager->post(networkRequest, QByteArray::fromStdString(passedJson.dump()));
    } else if (requestType == REQUEST_TYPE::REQUEST) {
        networkAccessManager->get(networkRequest);
    }

    // Wait for request to finish executing
    QEventLoop loop;
    connect(networkAccessManager, &QNetworkAccessManager::finished, &loop, &QEventLoop::quit);
    loop.exec();

    SPDLOG_INFO(QString("Data %1, url: %2").arg(requestTypeString, url).toStdString());
}

JTTP::~JTTP() {
}
