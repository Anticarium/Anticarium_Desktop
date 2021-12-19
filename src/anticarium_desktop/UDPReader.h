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
    // Requests data from server
    void onHeartbeat();

    // Reads data and stops handshake requests
    void onDataArrived();

  private:
    enum Timeout
    {
        HEARTBEAT = 1000,
        RECONNECT = 5000
    };

    QUdpSocket* udp        = nullptr;
    QTimer* heartbeatTimer = nullptr;
    QTimer* reconnectTimer = nullptr;

    static const QString HEARTBEAT_MESSAGE;
};
