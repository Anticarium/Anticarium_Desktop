#ifndef REGIMEDIALOG_H
#define REGIMEDIALOG_H

#include <QDialog>

namespace Ui {
class RegimeDialog;
}

class RegimeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegimeDialog(QWidget *parent = nullptr);
    ~RegimeDialog();

private:
    Ui::RegimeDialog *ui;
};

#endif // REGIMEDIALOG_H
