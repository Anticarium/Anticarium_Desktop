#include <QApplication>
#include <anticarium_desktop/Jttp.h>
#include <anticarium_desktop/config/ApplicationSettings.h>
#include <anticarium_desktop/config/ImageRow.hpp>
#include <anticarium_desktop/widgets/MainWindow.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>

static void exceptionHandler() {
    try {
        std::rethrow_exception(std::current_exception());
    } catch (const std::exception& e) {
        SPDLOG_CRITICAL(e.what());
    } catch (...) {
        SPDLOG_CRITICAL("Unhandled exception occurred!");
    }

    // Exception can occur anywhere, so it is unsafe to try to terminate qt application
    exit(EXIT_FAILURE);
}

static void initializeLogger() {
    auto settings = ApplicationSettings::instance();

    auto loggerPath = QString("%1/%2").arg(QCoreApplication::applicationDirPath(), "logs/AnticariumDesktopLog.log").toStdString();

    auto dailySink    = std::make_shared<spdlog::sinks::daily_file_sink_mt>(loggerPath, 0, 0, false, 10);
    auto rotatingSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(dailySink->filename(), 1048576 * 10, 10);
    auto consoleSink  = std::make_shared<spdlog::sinks::stdout_sink_mt>();

    std::vector<spdlog::sink_ptr> loggerSinks;

    loggerSinks.push_back(dailySink);
    loggerSinks.push_back(rotatingSink);
    loggerSinks.push_back(consoleSink);
    auto combinedLogger = std::make_shared<spdlog::logger>("logger", begin(loggerSinks), end(loggerSinks));

    spdlog::register_logger(combinedLogger);
    spdlog::set_default_logger(combinedLogger);
    spdlog::set_pattern("%5l | %D %T | %-40s %-4# | %v");
    spdlog::flush_on(spdlog::level::trace);
    spdlog::set_level(settings->getLogLevel());
}

// Creates JTTP singleton and puts it in separate thread
static void initializeJttp(QObject* parent) {
    auto jttpThread = new QThread(parent);
    auto jttp       = JTTP::instance();
    jttp->moveToThread(jttpThread);
    jttpThread->start();
    jttpThread->connect(parent, &QObject::destroyed, [=]() {
        jttpThread->quit();
        jttpThread->wait();
    });
}

Q_DECLARE_METATYPE(JTTP::REQUEST_DATA);
Q_DECLARE_METATYPE(JTTP::REQUEST_TYPE);
Q_DECLARE_METATYPE(shared_types::Regime);
Q_DECLARE_METATYPE(shared_types::Control);
Q_DECLARE_METATYPE(shared_types::RegimeId);
Q_DECLARE_METATYPE(shared_types::Regimes);
Q_DECLARE_METATYPE(shared_types::SavedRegimes);
Q_DECLARE_METATYPE(shared_types::SensorData);

int main(int argc, char* argv[]) {
    std::set_terminate(exceptionHandler);

    qRegisterMetaType<JTTP::REQUEST_DATA>();
    qRegisterMetaType<JTTP::REQUEST_TYPE>();
    qRegisterMetaType<shared_types::Regime>();
    qRegisterMetaType<shared_types::Control>();
    qRegisterMetaType<shared_types::RegimeId>();
    qRegisterMetaType<shared_types::Regimes>();
    qRegisterMetaType<shared_types::SavedRegimes>();
    qRegisterMetaType<shared_types::SensorData>();
    qRegisterMetaType<ImageRow>("ImageRow");

    QApplication a(argc, argv);

    ApplicationSettings::instance(QApplication::applicationDirPath() + "/settings.ini", QCoreApplication::instance());

    initializeLogger();
    initializeJttp(QApplication::instance());

    SPDLOG_INFO("Program started");
    MainWindow w;
    w.show();

    int returnCode = a.exec();
    SPDLOG_INFO(QString("Program exited with exit code %1 \n").arg(returnCode).toStdString());
    return returnCode;
}
