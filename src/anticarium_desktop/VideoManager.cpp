#include <QGraphicsItem>
#include <anticarium_desktop/ImageBuilder.h>
#include <anticarium_desktop/VideoManager.h>
#include <anticarium_desktop/config/ApplicationSettings.h>

VideoManager::VideoManager(QObject* parent) : QObject(parent) {
    udpReader  = new UDPReader(this);
    videoScene = new QGraphicsScene(this);
    initializeScene();

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

    auto imageRow = ImageBuilder::build(data, settings->getImageWidth());

    // Return if row number too big
    if (imageRow.position > settings->getImageHeight() - 1) {
        return;
    }

    // Return if row number too small
    if (imageRow.position < 0) {
        return;
    }

    updateImageRow(imageRow);
}

void VideoManager::updateImageRow(const ImageRow& row) {
    // Get current row
    auto currentRowItem = videoScene->items()[row.position];
    auto pixmapItem     = qgraphicsitem_cast<QGraphicsPixmapItem*>(currentRowItem);

    // Update row
    if (pixmapItem) {
        pixmapItem->setPixmap(row.pixmap);
    }
}

void VideoManager::initializeScene() {
    auto settings = ApplicationSettings::instance();

    int width  = settings->getImageWidth();
    int height = settings->getImageHeight();

    // Create pixmap rows
    QSize size(width, 1);
    for (int i = 0; i < height; i++) {
        QPixmap pixmap(size);
        auto row = videoScene->addPixmap(pixmap);
        row->setOffset(0, i);
    }
}

QGraphicsScene* VideoManager::getVideoScene() const {
    return videoScene;
}
