/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "custom_elements/clickablewidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *MenuButtons;
    ClickableWidget *HomeButton;
    QLabel *label_2;
    ClickableWidget *UserButton;
    QLabel *label_3;
    ClickableWidget *ModesButton;
    QLabel *label_4;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 801, 21));
        widget->setStyleSheet(QString::fromUtf8("border-bottom: 1px solid black;"));
        horizontalLayoutWidget = new QWidget(widget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 0, 181, 31));
        MenuButtons = new QHBoxLayout(horizontalLayoutWidget);
        MenuButtons->setSpacing(0);
        MenuButtons->setObjectName(QString::fromUtf8("MenuButtons"));
        MenuButtons->setContentsMargins(0, 0, 0, 0);
        HomeButton = new ClickableWidget(horizontalLayoutWidget);
        HomeButton->setObjectName(QString::fromUtf8("HomeButton"));
        HomeButton->setCursor(QCursor(Qt::PointingHandCursor));
        HomeButton->setStyleSheet(QString::fromUtf8("border-right: 1px solid black;"));
        label_2 = new QLabel(HomeButton);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 0, 46, 21));
        label_2->setStyleSheet(QString::fromUtf8("color: black;"));

        MenuButtons->addWidget(HomeButton);

        UserButton = new ClickableWidget(horizontalLayoutWidget);
        UserButton->setObjectName(QString::fromUtf8("UserButton"));
        UserButton->setCursor(QCursor(Qt::PointingHandCursor));
        UserButton->setStyleSheet(QString::fromUtf8("border-right: 1px solid black;"));
        label_3 = new QLabel(UserButton);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 0, 31, 21));
        label_3->setStyleSheet(QString::fromUtf8("color: black;"));

        MenuButtons->addWidget(UserButton);

        ModesButton = new ClickableWidget(horizontalLayoutWidget);
        ModesButton->setObjectName(QString::fromUtf8("ModesButton"));
        ModesButton->setCursor(QCursor(Qt::PointingHandCursor));
        ModesButton->setStyleSheet(QString::fromUtf8("border-right: 1px solid black;"));
        label_4 = new QLabel(ModesButton);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 0, 31, 21));
        label_4->setStyleSheet(QString::fromUtf8("color: black;"));

        MenuButtons->addWidget(ModesButton);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(780, 0, 21, 21));
        label->setPixmap(QPixmap(QString::fromUtf8(":/icons/assets/icons/Exit_To_App_Icon_2.png")));
        label->setScaledContents(true);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Home", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "User", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Modes", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
