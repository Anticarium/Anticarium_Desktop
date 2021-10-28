#include "DisplayRegimes.h"
#include "ui_DisplayRegimes.h"

DisplayRegimes::DisplayRegimes(QWidget* parent) : QDialog(parent), ui(new Ui::DisplayRegimes) {
    ui->setupUi(this);
    connect(ui->regimesButtonBox, &QDialogButtonBox::accepted, this, &DisplayRegimes::accept);
    connect(ui->regimesButtonBox, &QDialogButtonBox::rejected, this, &DisplayRegimes::reject);

    initializeTableHeader();

    manager = new DisplayRegimesManager(this);
    connect(manager, &DisplayRegimesManager::displayDataEvent, this, &DisplayRegimes::onDisplayData);
    manager->initialize();
}

DisplayRegimes::~DisplayRegimes() {
    delete ui;
}

#include <QDebug>
void DisplayRegimes::onDisplayData(const shared_types::SavedRegimes& savedRegimes) {
    qDebug() << "DisplayRegimes::onDisplayData";
}

void DisplayRegimes::initializeTableHeader() {
    QHeaderView* tableHeader = ui->tableView->horizontalHeader();
}
