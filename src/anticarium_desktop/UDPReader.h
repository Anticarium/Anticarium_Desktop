#pragma once

#include <QTimer>
#include <QUdpSocket>

class UDPReader : public QObject {
    Q_OBJECT
  public:
    UDPReader(QObject* parent = nullptr);
    ~UDPReader();
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
    {
        HANDSHAKE = 1000,
        RECONNECT = 5000
    };

    QUdpSocket* udp        = nullptr;
    QTimer* handshakeTimer = nullptr;
    QTimer* reconnectTimer = nullptr;

    static const QString HANDSHAKE_MESSAGE;
};
