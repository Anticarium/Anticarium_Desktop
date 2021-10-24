#include "RegimeDialog.h"
#include "ui_RegimeDialog.h"

RegimeDialog::RegimeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegimeDialog)
{
    ui->setupUi(this);
}

RegimeDialog::~RegimeDialog()
{
    delete ui;
}
