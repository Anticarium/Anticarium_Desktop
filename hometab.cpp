#include "hometab.h"
#include "ui_hometab.h"

HomeTab::HomeTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeTab)
{
    ui->setupUi(this);
}

HomeTab::~HomeTab()
{
    delete ui;
}


void HomeTab::updateSensorDisplay(const json& jData){
    //reads temperature value
    float displayValue = 0.0f;
    try{
        displayValue = jData["Temperature"];
        ui->tempValue->display(displayValue);
    } catch (std::exception & e) {
        qDebug() << "No such json key!";
    }

    //reads air humidity value
    try{
        displayValue = jData["Air_humidity"];
        ui->humiValue->display(displayValue);
    } catch (std::exception & e) {
        qDebug() << "No such json key!";
    }

    //reads soil moisture value
    try{
        displayValue = jData["Soil_Moisture"];
        ui->moistValue->display(displayValue);
    } catch (std::exception & e) {
        qDebug() << "No such json key!";
    }

    //reads light value
    try{
        displayValue = jData["Light"];
        ui->lightValue->setValue(displayValue);
    } catch (std::exception & e) {
        qDebug() << "No such json key!";
    }

    //reads heat value
    try{
        displayValue = jData["Heat"];
        ui->heatValue->setValue(displayValue);
    } catch (std::exception & e) {
        qDebug() << "No such json key!";
    }

    //reads weather value
    std::string stringValue;
    try{
        stringValue = jData["Weather"];
        ui->weatherLabel->setText(QString::fromUtf8(stringValue.c_str()));
    } catch (std::exception & e) {
        qDebug() << "No such json key!";
    }

    //reads mode value
    try{
        stringValue = jData["Auto_Mode_Type"];
        ui->modeLabel->setText(QString::fromUtf8(stringValue.c_str()));
    } catch (std::exception & e) {
        qDebug() << "No such json key!";
    }


    qDebug() << "Display updated!" ;
}
