#include "jttp.h"

JTTP::JTTP(QObject *parent, QSettings * settings) :
    QObject(parent),
    _dataRequestTimer(new QTimer(this)),
    _manager(new QNetworkAccessManager(this)),
    _sensorRequest(),
    GETSONSORURL("/getSensor"),
    JSONFROM(settings->value("Get_JSON_From").toString())
{
    //connects timeout to request function and executes this function every requestTimeout millis
    int dTM = settings->value("Data_Request_Timeout").toInt();
    if(!dTM){
        qWarning() << "NO TIMEOUT WAS SET" ;
    } else {
        connect(_dataRequestTimer, &QTimer::timeout, this, &JTTP::getSensorData);
        _dataRequestTimer->start(dTM);
    }

    //creates request for sensor data
    if(JSONFROM == "Emulator"){
        _sensorRequest.setUrl(QUrl(settings->value("Server_URL").toString()));
    } else {
        _sensorRequest.setUrl(QUrl(settings->value("Server_URL").toString() + GETSONSORURL));
    }
    _sensorRequest.setRawHeader("Data request", "Anticarium User");
    //TODO find a way how to clean up this pointer
    QNetworkReply * sensorReply = _manager->get(_sensorRequest);

//    connect(sensorReply, )
}

JTTP * JTTP::_jttp = nullptr;

JTTP * JTTP::GetInstance(QObject *parent, QSettings * settings){
    if(_jttp == nullptr){
        _jttp = new JTTP(parent, settings);
    }
    return _jttp;
}

int JTTP::getSensorData(){
    QNetworkRequest request;


    return 0;
}

JTTP::~JTTP(){
    delete _manager;
    delete _jttp;
    delete _dataRequestTimer;
}
