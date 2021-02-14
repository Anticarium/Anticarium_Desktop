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
    //private constructor for singleton
    JTTP(QObject *parent = nullptr, QSettings * settings = nullptr);
    static JTTP * _jttp;
    ~JTTP();
    //timer object that pings server for new data every now and then
    QTimer * _dataRequestTimer;

    //HTTP communication objects
    QNetworkAccessManager * _manager;
    QNetworkRequest _sensorRequest;
    QNetworkReply * _sensorReply;

public:
    //singleton design pattern
    JTTP() = delete;
    void operator=(const JTTP &) = delete;

    //main singleton constructor
    static JTTP * GetInstance(QObject *parent, QSettings * settings);

signals:
    //updates home tab displayed values
    void updateSensorDisplay(const json & jData);
private slots:
    //timer requests data
    void requestSensorData();
    //reads sensor data and emits display update signal
    void getSensorData(QNetworkReply * reply);


};

#endif // JTTP_H
