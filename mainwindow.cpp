#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //for Anticarium.ini
    QCoreApplication::setOrganizationName("Team_7");
    QCoreApplication::setApplicationName("Anticarium");
    initSettings();

    ui->setupUi(this);

    homeTab = new HomeTab(this);
    userTab = new UserTab(this);
    modesTab = new ModesTab(this);

    topButtonsArr.push_back(homeTab);
    topButtonsArr.push_back(userTab);
    topButtonsArr.push_back(modesTab);

    //moves all tabs by 21 so it does not interfere with top buttons
    for(QWidget * i : topButtonsArr){
        i->move(0, 21); //21 is the header height
    }
    hideTabs(topButtonsArr);
    //show the home tab at the start of the app
    homeTab->show();


    //connects top buttons with tab changing method
    connect(ui->HomeButton, &ClickableWidget::clicked, this, &MainWindow::changeTab);
    connect(ui->ModesButton, &ClickableWidget::clicked, this, &MainWindow::changeTab);
    connect(ui->UserButton, &ClickableWidget::clicked, this, &MainWindow::changeTab);
}

void MainWindow::initSettings(){
    //every time you want to use settings file you must create settings object like this, so same .ini file gets used each time
    QSettings settings(QSettings::Format::IniFormat, QSettings::Scope::SystemScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
}

void MainWindow::changeTab(ClickableWidget * tabWidget){
    hideTabs(topButtonsArr);
    QString inStr = tabWidget->objectName();
    //opens the required tab
    if(inStr == "HomeButton"){
        homeTab->show();
    } else if (inStr == "UserButton"){
        userTab->show();
    } else if (inStr == "ModesButton"){
        modesTab->show();
    }
}

void MainWindow::hideTabs(std::vector<QWidget *> wVector){
    for(QWidget * i : wVector){
        i->hide();
    }
}

MainWindow::~MainWindow()
{
    delete modesTab;
    delete userTab;
    delete homeTab;
    delete ui;
}

