#include "usertab.h"
#include "ui_usertab.h"

UserTab::UserTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserTab)
{
    ui->setupUi(this);
}

UserTab::~UserTab()
{
    delete ui;
}
