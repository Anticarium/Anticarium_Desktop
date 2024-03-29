#include <anticarium_desktop/widgets/DisplayRegimes.h>
#include <anticarium_desktop/widgets/RegimeDialog.h>
#include <ui_DisplayRegimes.h>

DisplayRegimes::DisplayRegimes(QWidget* parent) : QDialog(parent), ui(new Ui::DisplayRegimes) {
    ui->setupUi(this);

    setWindowTitle("Saved Regimes");

    connect(ui->regimesButtonBox, &QDialogButtonBox::accepted, this, &DisplayRegimes::accept);
    connect(ui->regimesButtonBox, &QDialogButtonBox::rejected, this, &DisplayRegimes::reject);
    connect(ui->editItemButton, &QPushButton::clicked, this, &DisplayRegimes::onEditItemButtonClicked);
    connect(ui->deleteItemButton, &QPushButton::clicked, this, &DisplayRegimes::onDeleteItemButtonClicked);

    initializeTableHeader();

    manager = new DisplayRegimesManager(this);
    connect(manager, &DisplayRegimesManager::displayDataEvent, this, &DisplayRegimes::onDisplayData);
    manager->initialize();

    adjustSize();
}

DisplayRegimes::~DisplayRegimes() {
    delete ui;
}

void DisplayRegimes::onDisplayData(const shared_types::SavedRegimes& savedRegimes) {
    // Delete previous rows
    ui->table->setRowCount(0);

    const auto regimesList = savedRegimes.getSavedRegimes();

    const int regimesListSize = regimesList.size();

    // Create new rows
    ui->table->setRowCount(regimesListSize);
    for (int i = 0; i < regimesListSize; ++i) {
        QTableWidgetItem* item = nullptr;

        item = new QTableWidgetItem(regimesList[i].getName(), Qt::DisplayRole);
        ui->table->setItem(i, 0, item);

        item = new QTableWidgetItem(QString::number(regimesList[i].getRegimeValue().getTemperature()), Qt::DisplayRole);
        ui->table->setItem(i, 1, item);

        item = new QTableWidgetItem(QString::number(regimesList[i].getRegimeValue().getMoisture()), Qt::DisplayRole);
        ui->table->setItem(i, 2, item);
    }

    checkTable();
}

void DisplayRegimes::onEditItemButtonClicked() {
    const int selectedRow = ui->table->currentRow();

    const auto regime = manager->getRegimeAt(selectedRow);

    auto regimeDialog = new RegimeDialog(RegimeDialog::MODE::EDIT, regime, this);
    regimeDialog->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
    regimeDialog->setModal(true);
    regimeDialog->show();
}

void DisplayRegimes::onDeleteItemButtonClicked() {
    int selectedRow = ui->table->currentRow();
    manager->deleteRegime(selectedRow);
    checkTable();
}

void DisplayRegimes::initializeTableHeader() {
    ui->table->setColumnCount(3);

    QTableWidgetItem* columnName = nullptr;

    columnName = new QTableWidgetItem("Name", Qt::DisplayRole);
    ui->table->setHorizontalHeaderItem(ITEM_POSITION::NAME, columnName);

    columnName = new QTableWidgetItem("Temperature", Qt::DisplayRole);
    ui->table->setHorizontalHeaderItem(ITEM_POSITION::TEMPERATURE, columnName);

    columnName = new QTableWidgetItem("Moisture", Qt::DisplayRole);
    ui->table->setHorizontalHeaderItem(ITEM_POSITION::MOISTURE, columnName);

    // Stretch rows
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Hide vertical header
    ui->table->verticalHeader()->hide();

    // Select whole row on click
    ui->table->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Disable edit on double click
    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void DisplayRegimes::checkTable() {
    const int rowCount = ui->table->rowCount();

    ui->deleteItemButton->setEnabled(rowCount);
    ui->editItemButton->setEnabled(rowCount);
}
