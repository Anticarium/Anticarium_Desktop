#include <QMessageBox>
#include <anticarium_desktop/widgets/RegimeDialog.h>
#include <ui_RegimeDialog.h>

enum REGIME_DIALOG_RESULT
{
    PROCESSING = 2 // Prevent dialog closing if there was an error
};

RegimeDialog::RegimeDialog(MODE mode, const shared_types::Regime& regime, QWidget* parent) : QDialog(parent), ui(new Ui::RegimeDialog) {
    ui->setupUi(this);

    currentRegimeId = regime.getRegimeId().getId();
    currentMode     = mode;
    if (currentMode == MODE::NEW) {
        modeNew();
    } else if (currentMode == MODE::EDIT) {
        modeEdit();
    }

    setValues(regime);

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

    if (currentMode == MODE::EDIT) {
        ui->nameInput->setText(regime.getName());
    }
}

shared_types::Regime RegimeDialog::prepareRegime(const QString& regimeName) {
    shared_types::Regime regime;
    shared_types::RegimeValue regimeValue;
    regimeValue.setTemperature(ui->temperatureInput->value());
    regimeValue.setMoisture(ui->moistureInput->value());

    regime.setName(regimeName);
    regime.setRegimeValue(regimeValue);

    shared_types::RegimeId regimeId;
    if (currentMode == MODE::NEW) {
        regimeId.setId(RegimeDialog::NEW_REGIME_ID);
    } else {
        regimeId.setId(currentRegimeId);
    }
    regime.setRegimeId(regimeId);
    return regime;
}

void RegimeDialog::sendRegime(const shared_types::Regime& regime) {
    const auto jttp = JTTP::instance();
    connect(this, &RegimeDialog::sendDataEvent, jttp, qOverload<const shared_types::Regime&>(&JTTP::onSendData));

    emit sendDataEvent(regime);
}

void RegimeDialog::saveInput(QAbstractButton* clickedButton) {
    const auto buttonRole = ui->buttonBox->standardButton(clickedButton);

    if (buttonRole == QDialogButtonBox::Save) {
        const auto textInput = ui->nameInput->text();
        if (textInput.isEmpty()) {
            auto message = new QMessageBox(QMessageBox::Warning, "No regime name", "Please input regime name", QMessageBox::NoButton, this);
            message->show();
            message->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
            connect(message, &QMessageBox::finished, this, [&](int) { setResult(Rejected); });
            setResult(PROCESSING);
        } else {
            // Create Regime from input fields
            const auto regime = prepareRegime(textInput);
            // Send Regime and request new data to apply changes
            sendRegime(regime);
            // Can close dialog
            setResult(Accepted);
        }
    } else {
        setResult(Rejected);
    }
}

void RegimeDialog::done(int r) {
    if (result() != PROCESSING) {
        QDialog::done(r);
    }
}

RegimeDialog::~RegimeDialog() {
    delete ui;
}
