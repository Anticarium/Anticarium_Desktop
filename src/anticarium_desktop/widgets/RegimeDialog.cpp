#include <QMessageBox>
#include <anticarium_desktop/widgets/RegimeDialog.h>
#include <ui_RegimeDialog.h>

enum REGIME_DIALOG_RESULT { PROCESSING = 2 };

RegimeDialog::RegimeDialog(RegimeDialog::MODE mode, const shared_types::Regime& regime, QWidget* parent) : QDialog(parent), ui(new Ui::RegimeDialog) {
    ui->setupUi(this);

    currentRegimeId = regime.getRegimeId().getId();
    currentMode     = mode;
    if (currentMode == RegimeDialog::MODE::NEW) {
        modeNew();
    } else if (currentMode == RegimeDialog::MODE::EDIT) {
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

    if (currentMode == RegimeDialog::MODE::EDIT) {
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
    if (currentMode == RegimeDialog::MODE::NEW) {
        regimeId.setId(RegimeDialog::NEW_REGIME_ID);
    } else {
        regimeId.setId(currentRegimeId);
    }
    regime.setRegimeId(regimeId);
    return regime;
}

void RegimeDialog::sendAndRequest(const shared_types::Regime& regime) {
    JTTP* jttp = JTTP::instance();
    connect(this, &RegimeDialog::sendDataEvent, jttp, qOverload<const shared_types::Regime&>(&JTTP::onSendData));
    connect(this, &RegimeDialog::requestDataEvent, jttp, &JTTP::onRequestData);
    emit sendDataEvent(regime);

    // Update regime list
    emit requestDataEvent(JTTP::REQUEST_DATA::REGIMES);

    // If used this dialog to edit regime, update saved regimes table
    if (currentMode == RegimeDialog::MODE::EDIT) {
        emit requestDataEvent(JTTP::REQUEST_DATA::SAVED_REGIMES);
    }

    // If edited regime that is turned on now, will make changes appear
    emit requestDataEvent(JTTP::REQUEST_DATA::REGIME);

    // For save button in MainWindow
    emit requestDataEvent(JTTP::REQUEST_DATA::REGIME_ID);
}

void RegimeDialog::saveInput(QAbstractButton* clickedButton) {
    QDialogButtonBox::StandardButton buttonRole = ui->buttonBox->standardButton(clickedButton);

    if (buttonRole == QDialogButtonBox::StandardButton::Save) {
        QString textInput = ui->nameInput->text();
        if (textInput.isEmpty()) {
            QMessageBox* message = new QMessageBox(QMessageBox::Icon::Warning, "No regime name", "Please input regime name", QMessageBox::NoButton, this);
            message->show();
            message->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
            connect(message, &QMessageBox::finished, this, [&](int result) { setResult(QDialog::DialogCode::Rejected); });
            setResult(REGIME_DIALOG_RESULT::PROCESSING);
        } else {
            // Create Regime from input fields
            shared_types::Regime regime = prepareRegime(textInput);
            // Send Regime and request new data to apply changes
            sendAndRequest(regime);
            // Can close dialog
            setResult(QDialog::DialogCode::Accepted);
        }
    } else {
        setResult(QDialog::DialogCode::Rejected);
    }
}

void RegimeDialog::done(int r) {
    if (result() != REGIME_DIALOG_RESULT::PROCESSING) {
        QDialog::done(r);
    }
}

RegimeDialog::~RegimeDialog() {
    delete ui;
}
