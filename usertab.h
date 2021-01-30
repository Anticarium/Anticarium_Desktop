#ifndef USERTAB_H
#define USERTAB_H

#include <QWidget>

namespace Ui {
class UserTab;
}

class UserTab : public QWidget
{
    Q_OBJECT

public:
    explicit UserTab(QWidget *parent = nullptr);
    ~UserTab();

private:
    Ui::UserTab *ui;
};

#endif // USERTAB_H
