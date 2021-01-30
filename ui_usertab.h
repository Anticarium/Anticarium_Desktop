/********************************************************************************
** Form generated from reading UI file 'usertab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERTAB_H
#define UI_USERTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserTab
{
public:
    QPushButton *pushButton;

    void setupUi(QWidget *UserTab)
    {
        if (UserTab->objectName().isEmpty())
            UserTab->setObjectName(QString::fromUtf8("UserTab"));
        UserTab->resize(400, 300);
        pushButton = new QPushButton(UserTab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(210, 220, 80, 21));

        retranslateUi(UserTab);

        QMetaObject::connectSlotsByName(UserTab);
    } // setupUi

    void retranslateUi(QWidget *UserTab)
    {
        UserTab->setWindowTitle(QCoreApplication::translate("UserTab", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("UserTab", "test", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserTab: public Ui_UserTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERTAB_H
