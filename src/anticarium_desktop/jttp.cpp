#include "jttp.h"

JTTP::JTTP(QObject *parent, QSettings * settings) :
    QObject(parent),
    _dataRequestTimer(new QTimer(this)),
    _manager(new QNetworkAccessManager(this)),
    _sensorRequest()
{
    //connects timeout to request function and executes this function every requestTimeout millis
    int dTM = settings->value("Data_Request_Timeout").toInt();
    if(!dTM){
        qWarning() << "NO TIMEOUT WAS SET" ;
    } else {
        connect(_dataRequestTimer, &QTimer::timeout, this, &JTTP::requestSensorData);
        _dataRequestTimer->start(dTM);
    }

    //creates request for sensor data
    QString sensorString = settings->value("Server_URL").toString() + settings->value("Sensor_Data_Link").toString();
    _sensorRequest.setUrl(QUrl(sensorString));

    _sensorRequest.setRawHeader("Data request", "Anticarium User");
//    _sensorRequest.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);

    //connects qnetworkAccessManager
    connect(_manager, &QNetworkAccessManager::finished,
            this, &JTTP::getSensorData);

    //requests data without timer for the first time
    requestSensorData();
}

JTTP * JTTP::_jttp = nullptr;

JTTP * JTTP::GetInstance(QObject *parent, QSettings * settings){
    if(_jttp == nullptr){
        _jttp = new JTTP(parent, settings);
    }
    return _jttp;
}

void JTTP::requestSensorData(){
    _manager->get(_sensorRequest);
}

void JTTP::getSensorData(QNetworkReply * reply){
    //checks if reply contains legitimate data
    if (reply->error()) {
        qDebug() << "QNetworkError: " << reply->errorString();
        return;
    }

    //reads reply into QString
    QString answer = reply->readAll();
    //parses to json object
    std::string jString = answer.toStdString();
    json j = json::parse(jString);

    //updates main window
    emit updateSensorDisplay(j);

    reply->deleteLater();
}

JTTP::~JTTP(){
    delete _sensorReply;
    delete _manager;
    delete _jttp;
    delete _dataRequestTimer;
}
