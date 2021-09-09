#include <Jttp.h>
#include <QApplication>
#include <widgets/MainWindow.h>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    JTTP::instance(QCoreApplication::instance());

    MainWindow w;
    w.show();
    return a.exec();
}
