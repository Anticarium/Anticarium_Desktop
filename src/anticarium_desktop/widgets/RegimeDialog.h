#pragma once

#include <QAbstractButton>
#include <QDialog>
#include <anticarium_desktop/Jttp.h>
#include <shared_types/Regime.h>

namespace Ui {
class RegimeDialog;
}

class RegimeDialog : public QDialog {
    Q_OBJECT

  public:
    static const int NEW_REGIME_ID = -1;
    enum class MODE { NEW, EDIT };
    RegimeDialog(RegimeDialog::MODE mode, const shared_types::Regime& regime, QWidget* parent = nullptr);
    ~RegimeDialog();

  signals:
    void sendDataEvent(const shared_types::Regime& regime);
    void requestDataEvent(JTTP::REQUEST_DATA requestData);

  private slots:
    void saveInput(QAbstractButton* clickedButton);

  private:
    RegimeDialog::MODE currentMode;
    int currentRegimeId = 0;

    // Closes dialog only if result code is accepted or rejected
    void done(int r) override;

    // Setups widget for "New" mode
    void modeNew();

    // Setups widget for "Edit" mode
    void modeEdit();

    // Setup initial values in input fields
    void setValues(const shared_types::Regime& regime);

    Ui::RegimeDialog* ui;
};
