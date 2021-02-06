#ifndef JTTP_H
#define JTTP_H

#include <QObject>
#include <QNetworkRequest>
#include <QTimer>
#include <QErrorMessage>
#include <QNetworkAccessManager>
#include "commonHeader.h"


class JTTP : public QObject
{
    Q_OBJECT
private:
    JTTP(QObject *parent = nullptr, QSettings * settings = nullptr);
    static JTTP * _jttp;

    //timer object that pings server for new data every now and then
    QTimer * _dataRequestTimer;

    //requests sensor data from server
    int getSensorData();

    QNetworkAccessManager * _manager;
    QNetworkRequest _sensorRequest;

    const QString GETSONSORURL;
    const QString JSONFROM;
public:
    JTTP() = delete;
    void operator=(const JTTP &) = delete;

    static JTTP * GetInstance(QObject *parent, QSettings * settings);

signals:

};

#endif // JTTP_H
