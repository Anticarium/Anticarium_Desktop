#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connects top buttons
    connect(ui->HomeButton, &ClickableWidget::clicked, this, &MainWindow::changeTab);
    connect(ui->ModesButton, &ClickableWidget::clicked, this, &MainWindow::changeTab);
    connect(ui->UserButton, &ClickableWidget::clicked, this, &MainWindow::changeTab);
}

void MainWindow::changeTab(ClickableWidget * tabWidget){
    qDebug() << tabWidget->objectName();

}

MainWindow::~MainWindow()
{
    delete ui;
}

