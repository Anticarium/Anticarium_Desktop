#include <anticarium_desktop/RowBuilder.h>
#include <anticarium_desktop/config/ApplicationSettings.h>

RowBuilder::RowBuilder(QObject* parent) : QObject(parent) {
}

void RowBuilder::build(const QByteArray& row, int width) {
    // Return if missing data in row
    if (row.size() != width * 3 + 3) {
        return;
    }

    ImageRow imageRow;

    // Get passed row value
    unsigned char positionValue[2] = {};

    positionValue[0] = row[1];
    positionValue[1] = row[2];

    imageRow.position = *reinterpret_cast<uint16_t*>(positionValue);

    QImage pixels(width, 1, QImage::QImage::Format_RGB32);
    for (int i = 0; i < width; i++) {
        int position = (i + 1) * 3;

        unsigned char r = row[position];
        unsigned char g = row[position + 1];
        unsigned char b = row[position + 2];

        QColor color(r, g, b);
        pixels.setPixelColor(i, 0, color.rgb());
    }

    imageRow.pixmap = QPixmap::fromImage(pixels);

    if (isRowOk(imageRow)) {
        emit rowReadyEvent(imageRow);
    }
}

bool RowBuilder::isRowOk(const ImageRow& row) {
    auto settings = ApplicationSettings::instance();
    int width     = settings->getImageWidth();

    // Return if row number too big
    if (row.position > settings->getImageHeight() - 1) {
        return false;
    }

    // Return if row number too small
    if (row.position < 0) {
        return false;
    }

    return true;
}
