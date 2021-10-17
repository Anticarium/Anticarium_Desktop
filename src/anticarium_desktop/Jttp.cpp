#include <QHttpMultiPart>
#include <anticarium_desktop/Jttp.h>
#include <shared_types/ControlSerializer.hpp>
#include <shared_types/RegimeNameSerializer.hpp>
#include <shared_types/RegimeSerializer.hpp>
#include <shared_types/RegimesSerializer.hpp>
#include <shared_types/SensorDataSerializer.hpp>

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
        qDebug() << "QNetworkError: " << reply->errorString();
        return;
    } else {
        content = reply->rawHeader("Anticarium content description");
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
    } else if (content == "Regime name") {
        jsonReply = nlohmann::json::parse(answer.toStdString());

        shared_types::RegimeName regimeName = jsonReply;
        emit dataReceivedEvent(regimeName);
    } else if (content == "Regime") {
        jsonReply = nlohmann::json::parse(answer.toStdString());

        shared_types::Regime regime = jsonReply;
        emit dataReceivedEvent(regime);
    }
}

void JTTP::onSendData(const shared_types::Control& control) {
    httpSend(REQUEST_TYPE::SEND, REQUEST_DATA::CONTROL_DATA, control);
}

void JTTP::onSendData(const shared_types::RegimeName& regimeName) {
    httpSend(REQUEST_TYPE::SEND, REQUEST_DATA::REGIME_NAME, regimeName);
}

void JTTP::onRequestData(REQUEST_DATA requestType) {
    httpSend(REQUEST_TYPE::REQUEST, requestType);
}

void JTTP::httpSend(REQUEST_TYPE requestType, REQUEST_DATA requestData, const nlohmann::json& passedJson) {
    QString requestTypeString = requestTypeMap[requestType];
    QString requestDataString = requestDataMap[requestData];
    QString url               = QString("http://127.0.0.1:5000/%1/%2").arg(requestTypeString).arg(requestDataString);
    QNetworkRequest networkRequest;
    networkRequest.setUrl(url);

    if (requestType == REQUEST_TYPE::SEND) {
        post(networkAccessManager, networkRequest, passedJson);
    } else if (requestType == REQUEST_TYPE::REQUEST) {
        networkAccessManager->get(networkRequest);
    }
}

void JTTP::post(QNetworkAccessManager* accessManager, const QNetworkRequest& networkRequest, const nlohmann::json& passedJson) {
    QHttpMultiPart* httpMultiPart = new QHttpMultiPart(this);
    QHttpPart http;
    http.setBody(QString::fromStdString(passedJson.dump()).toUtf8());
    httpMultiPart->append(http);
    accessManager->post(networkRequest, httpMultiPart);
}


JTTP::~JTTP() {
}
