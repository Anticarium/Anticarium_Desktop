#include "widgets/mainwindow.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    // for Anticarium.ini
    QCoreApplication::setOrganizationName("Team_7");
    QCoreApplication::setApplicationName("Anticarium");

    MainWindow w;
    w.show();
    return a.exec();
}
