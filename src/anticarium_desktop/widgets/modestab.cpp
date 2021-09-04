#include "modestab.h"
#include "ui_modestab.h"

ModesTab::ModesTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModesTab)
{
    ui->setupUi(this);
}

ModesTab::~ModesTab()
{
    delete ui;
}
