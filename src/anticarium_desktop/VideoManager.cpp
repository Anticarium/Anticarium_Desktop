#include <anticarium_desktop/ImageBuilder.h>
#include <anticarium_desktop/VideoManager.h>

VideoManager::VideoManager(QObject* parent) : QObject(parent) {
    udpReader = new UDPReader(this);

    connect(udpReader, &UDPReader::dataReadEvent, this, &VideoManager::onIncomingData);
}

void VideoManager::run() {
    udpReader->run();
}

void VideoManager::onIncomingData(const QByteArray& data) {
    auto result = ImageBuilder::build(data);

    emit imageRowReadyEvent(result);
}
