#include <Jttp.h>
#include <QApplication>
#include <widgets/MainWindow.h>

Q_DECLARE_METATYPE(shared_types::SensorData);


int main(int argc, char* argv[]) {
    qRegisterMetaType<shared_types::SensorData>("shared_types::SensorData");


    QApplication a(argc, argv);
    // for Anticarium.ini
    QCoreApplication::setOrganizationName("Team_7");
    QCoreApplication::setApplicationName("Anticarium");

    JTTP::instance(QCoreApplication::instance());

    MainWindow w;
    w.show();
    return a.exec();
}
