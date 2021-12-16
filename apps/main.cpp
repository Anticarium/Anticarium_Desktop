#include <QApplication>
#include <anticarium_desktop/Jttp.h>
#include <anticarium_desktop/config/ApplicationSettings.h>
#include <anticarium_desktop/config/ImageRow.hpp>
#include <anticarium_desktop/widgets/MainWindow.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>

static void initializeLogger() {
    QString qStringPath    = QString("%1/%2").arg(QCoreApplication::applicationDirPath(), "logs/AnticariumDesktopLog.log");
    std::string loggerPath = qStringPath.toStdString();

    std::shared_ptr<spdlog::sinks::daily_file_sink_mt> dailyLogger = std::make_shared<spdlog::sinks::daily_file_sink_mt>(loggerPath, 0, 0, false, 10);
    std::shared_ptr<spdlog::sinks::stdout_sink_mt> consoleLogger   = std::make_shared<spdlog::sinks::stdout_sink_mt>();

    std::vector<spdlog::sink_ptr> loggerSinks;

    loggerSinks.push_back(dailyLogger);
    loggerSinks.push_back(consoleLogger);
    std::shared_ptr<spdlog::logger> combined_logger = std::make_shared<spdlog::logger>("logger", begin(loggerSinks), end(loggerSinks));

    spdlog::register_logger(combined_logger);
    spdlog::set_default_logger(combined_logger);
    spdlog::set_pattern("%l | %D %T | %s %# | %v");
    spdlog::flush_on(spdlog::level::trace);
}

int main(int argc, char* argv[]) {
    qRegisterMetaType<ImageRow>("ImageRow");

    QApplication a(argc, argv);

    initializeLogger();

    SPDLOG_INFO("Program started");

    JTTP::instance(QApplication::instance());
    ApplicationSettings::instance(QApplication::applicationDirPath() + "/settings.ini", QCoreApplication::instance());

    MainWindow w;
    w.show();

    int returnCode = a.exec();
    SPDLOG_INFO(QString("Program exited with exit code %1 \n").arg(returnCode).toStdString());
    return returnCode;
}
