#include <QMessageBox>
#include <anticarium_desktop/config/ApplicationSettings.h>
#include <anticarium_desktop/widgets/DisplayRegimes.h>
#include <anticarium_desktop/widgets/MainWindow.h>
#include <anticarium_desktop/widgets/RegimeDialog.h>
#include <anticarium_desktop/widgets/RequestWaiter.h>
#include <ui_MainWindow.h>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    setWindowIcon(QIcon(":/resources/assets/icons/AnticariumIcon.ico"));
    setWindowTitle("Anticarium Desktop");

    manager = new MainWindowManager(this);

    connect(manager, qOverload<const shared_types::SensorData&>(&MainWindowManager::displayDataEvent), this,
            qOverload<const shared_types::SensorData&>(&MainWindow::displayData));
    connect(manager, qOverload<const shared_types::Control&>(&MainWindowManager::displayDataEvent), this,
            qOverload<const shared_types::Control&>(&MainWindow::displayData));
    connect(manager, qOverload<const shared_types::RegimeId&>(&MainWindowManager::displayDataEvent), this,
            qOverload<const shared_types::RegimeId&>(&MainWindow::displayData));
    connect(manager, qOverload<const shared_types::Regimes&>(&MainWindowManager::displayDataEvent), this,
            qOverload<const shared_types::Regimes&>(&MainWindow::displayData));
    connect(manager, qOverload<const shared_types::Regime&>(&MainWindowManager::displayDataEvent), this,
            qOverload<const shared_types::Regime&>(&MainWindow::displayData));

    connectUi();
    connectUiInputs();
    initializeVideoView();

    // Set slider values to minimum
    onWindSliderMoved(ui->windSlider->minimum());
    onHeatSliderMoved(ui->heatSlider->minimum());
    onLightSliderMoved(ui->lightSlider->minimum());
    onMoistureSliderMoved(ui->moistureSlider->minimum());

    manager->initialize();

    auto requestWaiter = new RequestWaiter(this);
    requestWaiter->setMaximumWidth(100);

    connect(manager, &MainWindowManager::dataRequestedEvent, requestWaiter, &RequestWaiter::onDataRequested);
    connect(manager, &MainWindowManager::answerReceivedEvent, requestWaiter, &RequestWaiter::onAnswerReceived);
    ui->statusBar->addPermanentWidget(requestWaiter);
    ui->statusBar->setStyleSheet("margin-right: 2px;");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::displayData(const shared_types::RegimeId& regimeId) {
    disconnectUiInputs();
    const int id = regimeId.getId();

    // Is custom regime id?
    if (id == -1) {
        // Yes: Set up everything to display custom regime
        onEnableSaveButton();
    } else if (ui->regimeList->count() >= regimeId.getId() + 1) {
        // No: Set current regime name if possible
        ui->regimeList->setCurrentIndex(id);
        ui->modeLabel->setText(ui->regimeList->currentText());
    }

    connectUiInputs();
}

void MainWindow::displayData(const shared_types::RegimeValue& regimeValue) {
    disconnectUiInputs();
    ui->heatSlider->setValue(regimeValue.getTemperature() * SLIDER_MULTIPLIER);
    ui->moistureSlider->setValue(regimeValue.getMoisture());
    connectUiInputs();

    ui->saveButton->setEnabled(false);
}


void MainWindow::onEnableSaveButton(int value) {
    disconnectUiInputs();
    ui->saveButton->setEnabled(true);
    ui->modeLabel->setText("Custom");
    ui->regimeList->setCurrentIndex(-1);
    connectUiInputs();
}

void MainWindow::onMoistureSliderMoved(int value) {
    ui->moistureLabel->setText(QString("%1%").arg(QString::number(value)));
}

void MainWindow::onHeatSliderMoved(int value) {
    QString stringValue;
    float displayFloat = value / static_cast<float>(SLIDER_MULTIPLIER);
    stringValue.sprintf("%.1f°C", displayFloat);
    ui->heatLabel->setText(stringValue);
}

void MainWindow::onWindSliderMoved(int value) {
    ui->windLabel->setText(QString("%1%").arg(QString::number(value)));
}

void MainWindow::onLightSliderMoved(int value) {
    ui->lightLabel->setText(QString("%1%").arg(QString::number(value)));
}

void MainWindow::onMoistureSliderReleased() {
    int value = ui->moistureSlider->value();
    manager->sendMoistureValue(value);
}

void MainWindow::onHeatSliderReleased() {
    int value = ui->heatSlider->value();
    manager->sendHeatValue(value);
}

void MainWindow::onWindSliderReleased() {
    int value = ui->windSlider->value();
    manager->sendWindValue(value);
}

void MainWindow::onLightSliderReleased() {
    int value = ui->lightSlider->value();
    manager->sendLightValue(value);
}

void MainWindow::onOpenRegimeDialog() {
    shared_types::RegimeValue regimeValue;
    float temperature = ui->heatSlider->value() / static_cast<float>(SLIDER_MULTIPLIER);
    regimeValue.setTemperature(temperature);

    int moisture = ui->moistureSlider->value();
    regimeValue.setMoisture(moisture);

    shared_types::Regime regime;
    regime.setRegimeValue(regimeValue);

    RegimeDialog* regimeDialog = new RegimeDialog(RegimeDialog::MODE::NEW, regime, this);
    regimeDialog->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
    regimeDialog->setModal(true);
    regimeDialog->show();
}

void MainWindow::onOpenDisplayRegimes() {
    DisplayRegimes* displayRegimes = new DisplayRegimes(this);
    displayRegimes->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
    displayRegimes->setModal(true);
    displayRegimes->show();
}

void MainWindow::onOpenAboutDialog() {
    auto aboutDialog = new QMessageBox(this);
    aboutDialog->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
    aboutDialog->setWindowTitle("About");
    aboutDialog->setText(QString("Version %1").arg(manager->getAppVersion()));
    aboutDialog->adjustSize();
    aboutDialog->show();
}

void MainWindow::displayData(const shared_types::Regime& regime) {
    displayData(regime.getRegimeId());
    displayData(regime.getRegimeValue());
}

void MainWindow::displayData(const shared_types::Control& control) {
    disconnectUiInputs();
    ui->windSlider->setValue(control.getWindPercentage());
    ui->lightSlider->setValue(control.getLightPercentage());
    connectUiInputs();
    displayData(control.getRegimeValue());
}

void MainWindow::displayData(const shared_types::SensorData& sensorData) {
    ui->temperatureValue->display(sensorData.getTemperature());
    ui->humidityValue->display(sensorData.getHumidity());
    ui->moistureValue->display(sensorData.getMoisture());
}

void MainWindow::displayData(const shared_types::Regimes& regimes) {
    disconnectUiInputs();
    ui->regimeList->clear();
    const auto regimesVector = regimes.getRegimes();
    for (const auto& regimeName : regimesVector) {
        ui->regimeList->addItem(regimeName);
    }

    displayData(manager->getRegimeId());

    connectUiInputs();
}

void MainWindow::connectUi() {
    // Display slider value
    connect(ui->moistureSlider, &QSlider::valueChanged, this, &MainWindow::onMoistureSliderMoved);
    connect(ui->heatSlider, &QSlider::valueChanged, this, &MainWindow::onHeatSliderMoved);
    connect(ui->lightSlider, &QSlider::valueChanged, this, &MainWindow::onLightSliderMoved);
    connect(ui->windSlider, &QSlider::valueChanged, this, &MainWindow::onWindSliderMoved);

    // Read released slider value
    connect(ui->heatSlider, &QSlider::sliderReleased, this, &MainWindow::onHeatSliderReleased);
    connect(ui->moistureSlider, &QSlider::sliderReleased, this, &MainWindow::onMoistureSliderReleased);
    connect(ui->windSlider, &QSlider::sliderReleased, this, &MainWindow::onWindSliderReleased);
    connect(ui->lightSlider, &QSlider::sliderReleased, this, &MainWindow::onLightSliderReleased);

    connect(ui->openDisplayRegimes, &QAction::triggered, this, &MainWindow::onOpenDisplayRegimes);
    connect(ui->openAboutDialog, &QAction::triggered, this, &MainWindow::onOpenAboutDialog);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::onOpenRegimeDialog);
}

void MainWindow::connectUiInputs() {
    connect(ui->moistureSlider, &QSlider::valueChanged, this, &MainWindow::onEnableSaveButton);
    connect(ui->heatSlider, &QSlider::valueChanged, this, &MainWindow::onEnableSaveButton);
    connect(ui->regimeList, qOverload<int>(&QComboBox::activated), manager, &MainWindowManager::onRegimeListActivated);
}

void MainWindow::disconnectUiInputs() {
    disconnect(ui->moistureSlider, &QSlider::valueChanged, this, &MainWindow::onEnableSaveButton);
    disconnect(ui->heatSlider, &QSlider::valueChanged, this, &MainWindow::onEnableSaveButton);
    disconnect(ui->regimeList, qOverload<int>(&QComboBox::activated), manager, &MainWindowManager::onRegimeListActivated);
}

void MainWindow::initializeVideoView() {
    auto settings = ApplicationSettings::instance();

    ui->videoStreamView->setScene(manager->getVideoScene());

    int width  = settings->getImageWidth();
    int height = settings->getImageHeight();

    ui->videoStreamView->setMaximumSize(width + 20, height);
}
