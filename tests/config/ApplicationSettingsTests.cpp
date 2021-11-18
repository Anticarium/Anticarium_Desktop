#include <TestDataDirectory.h>
#include <anticarium_desktop/config/ApplicationSettings.h>
#include <gtest/gtest.h>

TEST(TestApplicationSettings, TestRead) {
    QObject parent;

    QString testSettingsPath(TEST_DATA_DIR);
    testSettingsPath.append("/config/TestSettings.ini");
    ApplicationSettings* applicationSettings = ApplicationSettings::instance(testSettingsPath, &parent);

    EXPECT_EQ(applicationSettings->getAnticariumUrl(), "http://127.0.0.1:5000");
    EXPECT_EQ(applicationSettings->getSensorDataFetchTimeout(), 1000);
}
