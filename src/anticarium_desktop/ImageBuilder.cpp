#include <QDebug>
#include <anticarium_desktop/ImageBuilder.h>
#include <anticarium_desktop/config/ApplicationSettings.h>

ImageRow ImageBuilder::build(const QByteArray& row) {
    auto settings = ApplicationSettings::instance();
    ImageRow imageRow;

    // Get passed row value
    unsigned char positionValue[2] = {};

    positionValue[0] = row[2];
    positionValue[1] = row[1];

    imageRow.position = *reinterpret_cast<uint16_t*>(positionValue);

    int imageWidth = settings->getImageWidth();
    QImage pixels(imageWidth, 1, QImage::QImage::Format_RGB32);
    for (int i = 0; i < imageWidth; i++) {
        int position = (i + 1) * 3;

        QColor color(row[position], row[position + 1], row[position + 2]);
        pixels.setPixelColor(i, 0, color.rgb());
    }

    imageRow.pixmap = QPixmap::fromImage(pixels);

    return imageRow;
}
