#include "hometab.h"
#include "ui_hometab.h"

HomeTab::HomeTab(QWidget *parent, JTTP * jttp) :
    QWidget(parent),
    ui(new Ui::HomeTab),
    _jttp(jttp)
{
    ui->setupUi(this);
    aB = ui->autoFlag;


    //connects auto button press event
    connect(ui->autoFlag, &QPushButton::clicked, this, &HomeTab::autoPressed);

    //requests data each time auto button was pressed
//    connect(ui->autoFlag, &QPushButton::clicked, jttp, &JTTP::requestSensorData);

}

HomeTab::~HomeTab()
{
    delete ui;
}

void HomeTab::autoPressed(){
    bool autoState = ui->autoFlag->isChecked();

    //toggles home page buttons
    ui->heatButton->setDisabled(autoState);
    ui->rainButton->setDisabled(autoState);
    ui->windButton->setDisabled(autoState);
    ui->lightButton->setDisabled(autoState);

    //toggles inputs
    ui->lightValue->setReadOnly(autoState);
    ui->heatValue->setReadOnly(autoState);

    //sends new auto button value to server
    //*does it*


    //updates buttons
//    _jttp->requestSensorData();
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

    //reads auto mode value
    try{
        stringValue = jData["Auto_Mode_Type"];
        ui->modeLabel->setText(QString::fromUtf8(stringValue.c_str()));
    } catch (std::exception & e) {
        qDebug() << "No such json key!";
    }

    //reads mode value
    try{
        stringValue = jData["Mode"];
        //controls home buttons depending on Mode value
        if(stringValue == "Auto" && !ui->autoFlag->isChecked()) {
            ui->autoFlag->setChecked(true);
            emit ui->autoFlag->clicked();
        } else if(stringValue != "Auto" && ui->autoFlag->isChecked()){
            ui->autoFlag->setChecked(false);
            emit ui->autoFlag->clicked();
        }

        //reads auto mode value
        try{
            stringValue = jData["Auto_Mode_Type"];
            ui->modeLabel->setText(QString::fromUtf8(stringValue.c_str()));
        } catch (std::exception & e) {
            qDebug() << "No such json key!";
        }

        bool boolValue;
        //reads wind value
        try{
            boolValue = jData["Wind"];
            ui->windButton->setChecked(boolValue);
        } catch (std::exception & e) {
            qDebug() << "No such json key!";
        }

        //reads rain value
        try{
            boolValue = jData["Rain"];
            ui->rainButton->setChecked(boolValue);
        } catch (std::exception & e) {
            qDebug() << "No such json key!";
        }

    } catch (std::exception & e) {
        qDebug() << "No such json key!";
    }


    //    qDebug() << "Display updated!" ;
}

QPushButton * HomeTab::getAutoButton() const {
    return aB;
}
