#pragma once

#include <QDialog>
#include <anticarium_desktop/DisplayRegimesManager.h>

namespace Ui {
class DisplayRegimes;
}

class DisplayRegimes : public QDialog {
    Q_OBJECT

  public:
    explicit DisplayRegimes(QWidget* parent = nullptr);
    ~DisplayRegimes();

  public slots:
    void onDisplayData(const shared_types::SavedRegimes& savedRegimes);

  private:
    Ui::DisplayRegimes* ui;
    DisplayRegimesManager* manager = nullptr;

    // Sets table header
    void initializeTableHeader();
};
