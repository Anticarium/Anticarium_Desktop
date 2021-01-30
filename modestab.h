#ifndef MODESTAB_H
#define MODESTAB_H

#include <QWidget>

namespace Ui {
class ModesTab;
}

class ModesTab : public QWidget
{
    Q_OBJECT

public:
    explicit ModesTab(QWidget *parent = nullptr);
    ~ModesTab();

private:
    Ui::ModesTab *ui;
};

#endif // MODESTAB_H
