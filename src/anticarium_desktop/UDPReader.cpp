#include <QNetworkDatagram>
#include <QNetworkProxy>
#include <anticarium_desktop/UDPReader.h>
#include <anticarium_desktop/config/ApplicationSettings.h>
#include <spdlog/spdlog.h>

const QString UDPReader::HANDSHAKE_MESSAGE = "client_ready";

UDPReader::UDPReader(QObject* parent) : QObject(parent) {
    udp            = new QUdpSocket(this);
    handshakeTimer = new QTimer(this);
    reconnectTimer = new QTimer(this);

    handshakeTimer->setInterval(Timeout::HANDSHAKE);
    reconnectTimer->setInterval(Timeout::RECONNECT);
    reconnectTimer->setSingleShot(true);

    connect(handshakeTimer, &QTimer::timeout, this, &UDPReader::onRequestHandshake);
    connect(reconnectTimer, &QTimer::timeout, handshakeTimer, qOverload<>(&QTimer::start));
    connect(udp, &QUdpSocket::readyRead, this, &UDPReader::onDataArrived);
}

void UDPReader::run() {
    // Start handshake requests
    handshakeTimer->start();
}

void UDPReader::onRequestHandshake() {
    SPDLOG_INFO("Initiating UDP handshake");
    QByteArray datagram = HANDSHAKE_MESSAGE.toUtf8();

    udp->writeDatagram(datagram, QHostAddress(3232235879), 5011);
}

void UDPReader::onDataArrived() {
    // Stop handshake timer
    if (handshakeTimer->isActive()) {
        SPDLOG_INFO("Successful UDP handshake");
        handshakeTimer->stop();
    }

    while (udp->hasPendingDatagrams()) {
        auto datagram = udp->receiveDatagram();
        if (datagram.senderAddress().toString().contains("192.168.1.103")) {
            // Reset reconnection timer, because of incoming data
            reconnectTimer->stop();
            reconnectTimer->start();


            emit dataReadEvent(datagram.data());
        }
    }
}
