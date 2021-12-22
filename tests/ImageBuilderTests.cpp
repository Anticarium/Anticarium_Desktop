#include <QApplication>
#include <QByteArray>
#include <QImage>
#include <TestDataDirectory.h>
#include <anticarium_desktop/RowBuilder.h>
#include <gtest/gtest.h>

TEST(TestImageBuilder, TestBuild) {
    int argc      = 0;
    char* argv[1] = {};
    QApplication a(argc, argv);

    unsigned char rawRow[] = { 0, 61, 2, 255, 0, 0, 0, 255, 0, 0, 0, 255 };

    const char* unsignedRawRow = reinterpret_cast<char*>(rawRow);

    QByteArray byteArray(unsignedRawRow, sizeof(rawRow));

    auto imageRow = RowBuilder::build(byteArray, sizeof(rawRow) / 3);

    auto qImageRow = imageRow.pixmap.toImage();

    EXPECT_EQ(imageRow.position, 573);

    // Red
    EXPECT_EQ(qImageRow.pixelColor(0, 0).red(), 255);
    EXPECT_EQ(qImageRow.pixelColor(0, 0).green(), 0);
    EXPECT_EQ(qImageRow.pixelColor(0, 0).blue(), 0);

    // Green
    EXPECT_EQ(qImageRow.pixelColor(1, 0).red(), 0);
    EXPECT_EQ(qImageRow.pixelColor(1, 0).green(), 255);
    EXPECT_EQ(qImageRow.pixelColor(1, 0).blue(), 0);

    // Blue
    EXPECT_EQ(qImageRow.pixelColor(2, 0).red(), 0);
    EXPECT_EQ(qImageRow.pixelColor(2, 0).green(), 0);
    EXPECT_EQ(qImageRow.pixelColor(2, 0).blue(), 255);
}
