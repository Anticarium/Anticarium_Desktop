#include "Jttp.h"

JTTP::JTTP(QObject* parent) : QObject(parent) {
    networkAccessManager = new QNetworkAccessManager(this);
    dataRequestTimer     = new QTimer(this);

    networkRequest.setUrl(QUrl("http://127.0.0.1:5000/"));

    connect(networkAccessManager, &QNetworkAccessManager::finished, this, &JTTP::onDataArrived);
    //    connect(dataRequestTimer, &QTimer::timeout, this, &JTTP::requestSensorData);

    dataRequestTimer->start(5000);
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
    // parses to json object
    nlohmann::json j = nlohmann::json::parse(answer.toStdString());

    if (content == "Sensor data") {
        shared_types::SensorData sensorData = j;
        emit dataReceivedEvent(sensorData);
    }
}

// TODO send passed model as json
void JTTP::onSendData(const shared_types::Control& control) {
    executeGet(REQUEST_TYPE::SEND, REQUEST_DATA::CONTROL_DATA);
}

void JTTP::onRequestData(REQUEST_DATA requestType) {
    executeGet(REQUEST_TYPE::REQUEST, requestType);
}

void JTTP::executeGet(REQUEST_TYPE requestType, REQUEST_DATA requestData) {
    QString requestTypeString = requestTypeMap[requestType];
    QString requestDataString = requestDataMap[requestData];
    QString url               = QString("http://127.0.0.1:5000/%1/%2").arg(requestTypeString).arg(requestDataString);
    networkRequest.setUrl(url);
    networkAccessManager->get(networkRequest);
}


JTTP::~JTTP() {
}
