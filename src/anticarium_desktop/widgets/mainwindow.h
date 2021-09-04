#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "custom_elements/clickablewidget.h"
#include "hometab.h"
#include "jttp.h"
#include "modestab.h"
#include "widgets/usertab.h"
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

    // gets called from tabWidget and switches tabs
    void changeTab(ClickableWidget* tabWidget);

    // tabs array
    std::vector<QWidget*> topButtonsArr;

    // hides all widgets in given vector
    void hideTabs(std::vector<QWidget*> wVector);

    // initializes stored settings
    void initSettings();
    // makes HTTP calls to the server and processes received data
    JTTP* jttp;


  private:
    Ui::MainWindow* ui;
    QSettings* _settings;

  private slots:
};
#endif // MAINWINDOW_H
