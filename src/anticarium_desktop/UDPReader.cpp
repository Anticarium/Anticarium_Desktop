#include <QNetworkDatagram>
#include <anticarium_desktop/UDPReader.h>
#include <anticarium_desktop/config/ApplicationSettings.h>

UDPReader::UDPReader(QObject* parent) : QObject(parent) {
    udp            = new QUdpSocket(this);
    handshakeTimer = new QTimer(this);

    handshakeTimer->setInterval(Timeout::HANDSHAKE);

    connect(handshakeTimer, &QTimer::timeout, this, &UDPReader::onRequestHandshake);
    connect(udp, &QUdpSocket::readyRead, this, &UDPReader::onDataArrived);
}

void UDPReader::run() {
    auto settings = ApplicationSettings::instance();

    // Bind to udp server
    QHostAddress hostAddress(settings->getAnticariumUrl());
    int port = settings->getServerUDPPort();

    udp->connectToHost(hostAddress, port);

    // Start handshake requests
    handshakeTimer->start();
}

void UDPReader::onRequestHandshake() {
    QByteArray datagram = "client_ready";

    udp->writeDatagram(datagram);
}

void UDPReader::onDataArrived() {
    // Stop handshake timer
    if (handshakeTimer->isActive()) {
        handshakeTimer->stop();
    }

    while (udp->hasPendingDatagrams()) {
        auto datagram = udp->receiveDatagram();
        emit dataReadEvent(datagram.data());
    }
}
