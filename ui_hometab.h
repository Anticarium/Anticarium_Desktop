/********************************************************************************
** Form generated from reading UI file 'hometab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMETAB_H
#define UI_HOMETAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HomeTab
{
public:
    QPushButton *pushButton;
    QWidget *widget;

    void setupUi(QWidget *HomeTab)
    {
        if (HomeTab->objectName().isEmpty())
            HomeTab->setObjectName(QString::fromUtf8("HomeTab"));
        HomeTab->setEnabled(true);
        HomeTab->resize(559, 315);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(HomeTab->sizePolicy().hasHeightForWidth());
        HomeTab->setSizePolicy(sizePolicy);
        HomeTab->setMinimumSize(QSize(559, 21));
        HomeTab->setStyleSheet(QString::fromUtf8(""));
        pushButton = new QPushButton(HomeTab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(150, 260, 80, 21));
        widget = new QWidget(HomeTab);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 191, 111));
        widget->setStyleSheet(QString::fromUtf8("background: red;"));

        retranslateUi(HomeTab);

        QMetaObject::connectSlotsByName(HomeTab);
    } // setupUi

    void retranslateUi(QWidget *HomeTab)
    {
        HomeTab->setWindowTitle(QCoreApplication::translate("HomeTab", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("HomeTab", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HomeTab: public Ui_HomeTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMETAB_H
