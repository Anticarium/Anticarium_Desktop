#include <QMessageBox>
#include <anticarium_desktop/Jttp.h>
#include <anticarium_desktop/widgets/RegimeDialog.h>
#include <ui_RegimeDialog.h>

RegimeDialog::RegimeDialog(RegimeDialog::MODE mode, const shared_types::Regime& regime, QWidget* parent) : QDialog(parent), ui(new Ui::RegimeDialog) {
    ui->setupUi(this);

    setValues(regime);

    if (mode == RegimeDialog::MODE::NEW) {
        modeNew();
    } else if (mode == RegimeDialog::MODE::EDIT) {
        modeEdit();
    }

    connect(ui->buttonBox, &QDialogButtonBox::clicked, this, &RegimeDialog::saveInput);

    adjustSize();
}

void RegimeDialog::modeNew() {
    setWindowTitle("Create new regime");
    ui->temperatureInput->setDisabled(true);
    ui->moistureInput->setDisabled(true);
}

void RegimeDialog::modeEdit() {
    setWindowTitle("Edit regime");
}

void RegimeDialog::setValues(const shared_types::Regime& regime) {
    ui->temperatureInput->setSuffix("°C");
    ui->temperatureInput->setValue(regime.getRegimeValue().getTemperature());
    ui->moistureInput->setSuffix("%");
    ui->moistureInput->setValue(regime.getRegimeValue().getMoisture());
}

void RegimeDialog::saveInput(QAbstractButton* clickedButton) {
    QDialogButtonBox::StandardButton buttonRole = ui->buttonBox->standardButton(clickedButton);

    if (buttonRole == QDialogButtonBox::StandardButton::Save) {
        QString textInput = ui->nameInput->text();
        if (textInput.isEmpty()) {
            QMessageBox* message = new QMessageBox(QMessageBox::Icon::Warning, "No regime name", "Please input regime name", QMessageBox::NoButton, this);
            message->show();
            connect(message, &QMessageBox::finished, this, [=](int result) { message->deleteLater(); });
        } else {
            shared_types::Regime regime;
            shared_types::RegimeName regimeName;
            regimeName.setName(textInput);
            shared_types::RegimeValue regimeValue;
            regimeValue.setTemperature(ui->temperatureInput->value());
            regimeValue.setMoisture(ui->moistureInput->value());

            regime.setRegimeName(regimeName);
            regime.setRegimeValue(regimeValue);

            JTTP* jttp = JTTP::instance();
            connect(this, &RegimeDialog::sendDataEvent, jttp, qOverload<const shared_types::Regime&>(&JTTP::onSendData));
            emit sendDataEvent(regime);
        }
    }
}

RegimeDialog::~RegimeDialog() {
    delete ui;
}
