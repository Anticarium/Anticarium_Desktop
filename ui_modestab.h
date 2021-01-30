/********************************************************************************
** Form generated from reading UI file 'modestab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODESTAB_H
#define UI_MODESTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModesTab
{
public:
    QPushButton *pushButton;

    void setupUi(QWidget *ModesTab)
    {
        if (ModesTab->objectName().isEmpty())
            ModesTab->setObjectName(QString::fromUtf8("ModesTab"));
        ModesTab->resize(400, 300);
        pushButton = new QPushButton(ModesTab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(180, 190, 80, 21));

        retranslateUi(ModesTab);

        QMetaObject::connectSlotsByName(ModesTab);
    } // setupUi

    void retranslateUi(QWidget *ModesTab)
    {
        ModesTab->setWindowTitle(QCoreApplication::translate("ModesTab", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("ModesTab", "modes", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ModesTab: public Ui_ModesTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODESTAB_H
