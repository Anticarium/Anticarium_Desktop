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

        unsigned char r = row[position];
        unsigned char g = row[position + 1];
        unsigned char b = row[position + 2];

        // Change invalid values
        unsigned char rgb[] = { r, g, b };
        for (auto& i : rgb) {
            if (i > 255) {
                i = 255;
            }
            if (i < 0) {
                i = 0;
            }
        }

        QColor color(r, g, b);
        pixels.setPixelColor(i, 0, color.rgb());
    }

    imageRow.pixmap = QPixmap::fromImage(pixels);

    return imageRow;
}
