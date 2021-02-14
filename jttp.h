#ifndef JTTP_H
#define JTTP_H

#include <QObject>
#include <QNetworkRequest>
#include <QTimer>
#include <QErrorMessage>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "commonHeader.h"


class JTTP : public QObject
{
    Q_OBJECT
private:
    JTTP(QObject *parent = nullptr, QSettings * settings = nullptr);
    static JTTP * _jttp;
    ~JTTP();
    //timer object that pings server for new data every now and then
    QTimer * _dataRequestTimer;

    //requests sensor data from server

    QNetworkAccessManager * _manager;
    QNetworkRequest _sensorRequest;
    QNetworkReply * _sensorReply;

    const QString GET_SONSOR_URL;
    const QString JSON_FROM;
public:
    JTTP() = delete;
    void operator=(const JTTP &) = delete;

    static JTTP * GetInstance(QObject *parent, QSettings * settings);

//signals:
private slots:
    //timer requests data
    void requestSensorData();
    void getSensorData(QNetworkReply * reply);


};

#endif // JTTP_H
