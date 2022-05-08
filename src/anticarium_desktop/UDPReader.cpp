#include <QNetworkDatagram>
#include <anticarium_desktop/UDPReader.h>
#include <anticarium_desktop/config/ApplicationSettings.h>
#include <spdlog/spdlog.h>

const QString UDPReader::HEARTBEAT_MESSAGE = "client_ready";

UDPReader::UDPReader(QObject* parent) : QObject(parent) {
    udp            = new QUdpSocket(this);
    heartbeatTimer = new QTimer(this);
    reconnectTimer = new QTimer(this);

    heartbeatTimer->setInterval(Timeout::HEARTBEAT);
    reconnectTimer->setInterval(Timeout::RECONNECT);
    reconnectTimer->setSingleShot(true);

    // To send data using port defined in settings. Port forwarding for this port must be done
    // in client's router
    const auto& settings = *ApplicationSettings::instance();
    udp->bind(settings.getClientUDPPort());

    connect(heartbeatTimer, &QTimer::timeout, this, &UDPReader::onHeartbeat);
    connect(reconnectTimer, &QTimer::timeout, heartbeatTimer, qOverload<>(&QTimer::start));
    connect(udp, &QUdpSocket::readyRead, this, &UDPReader::onDataArrived);
}

UDPReader::~UDPReader() {
}

void UDPReader::run() {
    // Start heartbeat
    heartbeatTimer->start();
}

void UDPReader::onHeartbeat() {
    SPDLOG_INFO("UDP heartbeat");

    auto settings = ApplicationSettings::instance();

    QByteArray datagram = HEARTBEAT_MESSAGE.toUtf8();

    QHostAddress address = QHostAddress(settings->getAnticariumUDPUrl());
    quint16 port         = settings->getServerUDPPort();

    udp->writeDatagram(datagram, address, port);
}

void UDPReader::onDataArrived() {
    auto settings = ApplicationSettings::instance();

    while (udp->hasPendingDatagrams()) {
        auto datagram = udp->receiveDatagram();
        if (datagram.senderAddress().toString().contains(settings->getAnticariumUDPUrl())) {
            // Reset reconnection timer, because of incoming data
            reconnectTimer->stop();
            reconnectTimer->start();

            emit dataReadEvent(datagram.data());
        }
    }
}
