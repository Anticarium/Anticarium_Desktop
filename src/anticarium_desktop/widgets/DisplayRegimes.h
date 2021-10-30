#pragma once

#include <QDialog>
#include <anticarium_desktop/DisplayRegimesManager.h>

namespace Ui {
class DisplayRegimes;
}

class DisplayRegimes : public QDialog {
    Q_OBJECT

  public:
    enum ITEM_POSITION { NAME, TEMPERATURE, MOISTURE };
    DisplayRegimes(QWidget* parent = nullptr);
    ~DisplayRegimes();

  public slots:
    // Display all saved regimes in table
    void onDisplayData(const shared_types::SavedRegimes& savedRegimes);

  private slots:
    // Open RegimeDialog in edit mode
    void onEditItemButtonClicked();

    // Delete selected element
    void onDeleteItemButtonClicked();

  private:
    Ui::DisplayRegimes* ui;
    DisplayRegimesManager* manager = nullptr;

    // Sets table header
    void initializeTableHeader();

    // Check if there are elements in list, block edit buttons if there are not
    void checkTable();
};
