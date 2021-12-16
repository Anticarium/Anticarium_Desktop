#include <anticarium_desktop/ImageBuilder.h>
#include <anticarium_desktop/VideoManager.h>
#include <anticarium_desktop/config/ApplicationSettings.h>

VideoManager::VideoManager(QObject* parent) : QObject(parent) {
    udpReader = new UDPReader(this);

    connect(udpReader, &UDPReader::dataReadEvent, this, &VideoManager::onIncomingData);
}

void VideoManager::run() {
    udpReader->run();
}

void VideoManager::onIncomingData(const QByteArray& data) {
    auto settings = ApplicationSettings::instance();
    int width     = settings->getImageWidth();

    // Return if missing data in row
    if (data.size() != width * 3 + 3) {
        return;
    }

    auto imageRow = ImageBuilder::build(data);

    // Return if row number too big
    if (imageRow.position > settings->getImageHeight() - 1) {
        return;
    }

    // Return if row number too small
    if (imageRow.position < 0) {
        return;
    }

    emit imageRowReadyEvent(imageRow);
}
