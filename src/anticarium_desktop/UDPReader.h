#pragma once

#include <QTimer>
#include <QUdpSocket>

class UDPReader : public QObject {
    Q_OBJECT
  public:
    UDPReader(QObject* parent = nullptr);

    void run();

  signals:
    // Emits when data is read and ready to be processed
    // Datagram payload as argument
    void dataReadEvent(const QByteArray& data);

  private slots:
    // Starts requesting data from server
    void onRequestHandshake();

    // Reads data and stops handshake requests
    void onDataArrived();

  private:
    enum Timeout
    { HANDSHAKE = 1000 };


    QUdpSocket* udp        = nullptr;
    QTimer* handshakeTimer = nullptr;
};
