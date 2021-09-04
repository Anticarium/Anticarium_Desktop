#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "jttp.h"
#include <MainWindowManager.h>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  public slots:
    void onUpdate(const shared_types::Control& control);

  private:
    Ui::MainWindow* ui;
    QSettings* _settings = nullptr;
    // makes HTTP calls to the server and processes received data
    JTTP* jttp                 = nullptr;
    MainWindowManager* manager = nullptr;
};
#endif // MAINWINDOW_H
