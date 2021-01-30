/********************************************************************************
** Form generated from reading UI file 'Home.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOME_H
#define UI_HOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HomeWidget
{
public:
    QPushButton *pushButton;

    void setupUi(QWidget *HomeWidget)
    {
        if (HomeWidget->objectName().isEmpty())
            HomeWidget->setObjectName(QString::fromUtf8("HomeWidget"));
        HomeWidget->resize(654, 351);
        pushButton = new QPushButton(HomeWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(200, 190, 80, 21));

        retranslateUi(HomeWidget);

        QMetaObject::connectSlotsByName(HomeWidget);
    } // setupUi

    void retranslateUi(QWidget *HomeWidget)
    {
        HomeWidget->setWindowTitle(QCoreApplication::translate("HomeWidget", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("HomeWidget", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HomeWidget: public Ui_HomeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOME_H
