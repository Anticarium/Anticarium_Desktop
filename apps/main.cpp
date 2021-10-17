#include <QApplication>
#include <anticarium_desktop/Jttp.h>
#include <anticarium_desktop/widgets/MainWindow.h>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    JTTP::instance(QCoreApplication::instance());

    MainWindow w;
    w.initialize();
    w.show();
    return a.exec();
}
