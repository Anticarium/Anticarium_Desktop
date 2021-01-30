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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HomeTab
{
public:
    QWidget *widget_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_4;
    QLabel *label;
    QLCDNumber *lcdNumber_3;
    QLabel *label_8;
    QWidget *widget;
    QLabel *label_2;
    QLCDNumber *lcdNumber_2;
    QLabel *label_7;
    QWidget *widget_3;
    QLabel *label_3;
    QLCDNumber *lcdNumber;
    QLabel *label_6;
    QWidget *widget_5;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QOpenGLWidget *openGLWidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *RainButtonWidget;
    QPushButton *pushButton;
    QLabel *label_12;
    QWidget *WindButtonWidget;
    QLabel *label_13;
    QPushButton *pushButton_3;
    QWidget *LightButtonWidget;
    QSpinBox *spinBox;
    QPushButton *pushButton_5;
    QWidget *HeatButtonWidget;
    QSpinBox *spinBox_2;
    QPushButton *pushButton_6;

    void setupUi(QWidget *HomeTab)
    {
        if (HomeTab->objectName().isEmpty())
            HomeTab->setObjectName(QString::fromUtf8("HomeTab"));
        HomeTab->setEnabled(true);
        HomeTab->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(HomeTab->sizePolicy().hasHeightForWidth());
        HomeTab->setSizePolicy(sizePolicy);
        HomeTab->setMinimumSize(QSize(800, 600));
        HomeTab->setStyleSheet(QString::fromUtf8(""));
        widget_2 = new QWidget(HomeTab);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(0, 0, 161, 601));
        widget_2->setStyleSheet(QString::fromUtf8("border-right: 1px solid black;\n"
"color: black;\n"
"font-size: 16px;"));
        verticalLayoutWidget = new QWidget(widget_2);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 161, 331));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_4 = new QWidget(verticalLayoutWidget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setStyleSheet(QString::fromUtf8("border-bottom: 1px solid black;"));
        label = new QLabel(widget_4);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 0, 111, 21));
        lcdNumber_3 = new QLCDNumber(widget_4);
        lcdNumber_3->setObjectName(QString::fromUtf8("lcdNumber_3"));
        lcdNumber_3->setGeometry(QRect(10, 30, 64, 23));
        lcdNumber_3->setSegmentStyle(QLCDNumber::Flat);
        label_8 = new QLabel(widget_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(80, 30, 21, 21));
        label_8->setStyleSheet(QString::fromUtf8("font-size: 14px;"));

        verticalLayout->addWidget(widget_4);

        widget = new QWidget(verticalLayoutWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("border-bottom: 1px solid black;"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 0, 81, 21));
        lcdNumber_2 = new QLCDNumber(widget);
        lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));
        lcdNumber_2->setGeometry(QRect(10, 30, 64, 23));
        lcdNumber_2->setSegmentStyle(QLCDNumber::Flat);
        label_7 = new QLabel(widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(80, 30, 21, 20));
        label_7->setStyleSheet(QString::fromUtf8("font-size: 14px;"));

        verticalLayout->addWidget(widget);

        widget_3 = new QWidget(verticalLayoutWidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setStyleSheet(QString::fromUtf8("border-bottom: 1px solid black;"));
        label_3 = new QLabel(widget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 0, 81, 21));
        lcdNumber = new QLCDNumber(widget_3);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(10, 30, 64, 23));
        lcdNumber->setSegmentStyle(QLCDNumber::Flat);
        lcdNumber->setProperty("value", QVariant(3.000000000000000));
        label_6 = new QLabel(widget_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(80, 30, 21, 20));
        label_6->setStyleSheet(QString::fromUtf8("font-size: 14px;"));

        verticalLayout->addWidget(widget_3);

        widget_5 = new QWidget(verticalLayoutWidget);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setStyleSheet(QString::fromUtf8("border-bottom: 1px solid black;"));
        label_4 = new QLabel(widget_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 0, 81, 21));
        label_5 = new QLabel(widget_5);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 20, 71, 16));
        label_5->setStyleSheet(QString::fromUtf8("font-size: 12px;"));

        verticalLayout->addWidget(widget_5);

        label_9 = new QLabel(HomeTab);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(200, 10, 81, 21));
        label_9->setStyleSheet(QString::fromUtf8("font-weight: bold; color: black; font-size: 16px;"));
        label_10 = new QLabel(HomeTab);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(280, 10, 51, 21));
        label_10->setStyleSheet(QString::fromUtf8("font-weight: normal; color: black; font-size: 16px;"));
        label_11 = new QLabel(HomeTab);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(320, 10, 41, 21));
        label_11->setStyleSheet(QString::fromUtf8("font-weight: normal; color: black; font-size: 16px;"));
        label_11->setScaledContents(true);
        openGLWidget = new QOpenGLWidget(HomeTab);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(190, 40, 581, 331));
        horizontalLayoutWidget = new QWidget(HomeTab);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(190, 380, 581, 61));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        RainButtonWidget = new QWidget(horizontalLayoutWidget);
        RainButtonWidget->setObjectName(QString::fromUtf8("RainButtonWidget"));
        RainButtonWidget->setStyleSheet(QString::fromUtf8("QWidget#RainButtonWidget{border: 1px solid black;}"));
        pushButton = new QPushButton(RainButtonWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 10, 51, 41));
        pushButton->setStyleSheet(QString::fromUtf8("color: black;"));
        label_12 = new QLabel(RainButtonWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(70, 10, 41, 41));
        label_12->setStyleSheet(QString::fromUtf8("border: none;"));
        label_12->setPixmap(QPixmap(QString::fromUtf8(":/icons/assets/icons/Invert_Colors_Icon_1.png")));
        label_12->setScaledContents(true);

        horizontalLayout->addWidget(RainButtonWidget);

        WindButtonWidget = new QWidget(horizontalLayoutWidget);
        WindButtonWidget->setObjectName(QString::fromUtf8("WindButtonWidget"));
        WindButtonWidget->setStyleSheet(QString::fromUtf8("QWidget#WindButtonWidget{border: 1px solid black;}\n"
""));
        label_13 = new QLabel(WindButtonWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(70, 10, 41, 41));
        label_13->setStyleSheet(QString::fromUtf8("border: none;"));
        label_13->setPixmap(QPixmap(QString::fromUtf8(":/icons/assets/icons/Waves_Icon_1.png")));
        label_13->setScaledContents(true);
        pushButton_3 = new QPushButton(WindButtonWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(10, 10, 51, 41));
        pushButton_3->setStyleSheet(QString::fromUtf8("color: black;"));
        pushButton_3->setCheckable(false);
        pushButton_3->setAutoDefault(false);
        pushButton_3->setFlat(false);

        horizontalLayout->addWidget(WindButtonWidget);

        LightButtonWidget = new QWidget(horizontalLayoutWidget);
        LightButtonWidget->setObjectName(QString::fromUtf8("LightButtonWidget"));
        LightButtonWidget->setStyleSheet(QString::fromUtf8("QWidget#LightButtonWidget{border: 1px solid black;}\n"
""));
        spinBox = new QSpinBox(LightButtonWidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(70, 10, 51, 41));
        spinBox->setStyleSheet(QString::fromUtf8("font-size: 14px;"));
        spinBox->setMaximum(100);
        pushButton_5 = new QPushButton(LightButtonWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(10, 10, 51, 41));
        pushButton_5->setStyleSheet(QString::fromUtf8("color: black;"));
        pushButton_5->setCheckable(false);
        pushButton_5->setAutoDefault(false);
        pushButton_5->setFlat(false);

        horizontalLayout->addWidget(LightButtonWidget);

        HeatButtonWidget = new QWidget(horizontalLayoutWidget);
        HeatButtonWidget->setObjectName(QString::fromUtf8("HeatButtonWidget"));
        HeatButtonWidget->setStyleSheet(QString::fromUtf8("QWidget#HeatButtonWidget{border: 1px solid black;}\n"
""));
        spinBox_2 = new QSpinBox(HeatButtonWidget);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setGeometry(QRect(70, 10, 51, 41));
        spinBox_2->setStyleSheet(QString::fromUtf8("font-size: 14px;"));
        spinBox_2->setMaximum(100);
        pushButton_6 = new QPushButton(HeatButtonWidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(10, 10, 51, 41));
        pushButton_6->setStyleSheet(QString::fromUtf8("color: black;"));
        pushButton_6->setCheckable(false);
        pushButton_6->setAutoDefault(false);
        pushButton_6->setFlat(false);

        horizontalLayout->addWidget(HeatButtonWidget);


        retranslateUi(HomeTab);

        pushButton_3->setDefault(false);
        pushButton_5->setDefault(false);
        pushButton_6->setDefault(false);


        QMetaObject::connectSlotsByName(HomeTab);
    } // setupUi

    void retranslateUi(QWidget *HomeTab)
    {
        HomeTab->setWindowTitle(QCoreApplication::translate("HomeTab", "Form", nullptr));
        label->setText(QCoreApplication::translate("HomeTab", "Temperature:", nullptr));
        label_8->setText(QCoreApplication::translate("HomeTab", "\302\260C", nullptr));
        label_2->setText(QCoreApplication::translate("HomeTab", "Humidity:", nullptr));
        label_7->setText(QCoreApplication::translate("HomeTab", "%", nullptr));
        label_3->setText(QCoreApplication::translate("HomeTab", "Moisture:", nullptr));
        label_6->setText(QCoreApplication::translate("HomeTab", "%", nullptr));
        label_4->setText(QCoreApplication::translate("HomeTab", "Mode:", nullptr));
        label_5->setText(QCoreApplication::translate("HomeTab", "NULL", nullptr));
        label_9->setText(QCoreApplication::translate("HomeTab", "Weather: ", nullptr));
        label_10->setText(QCoreApplication::translate("HomeTab", "NULL", nullptr));
        label_11->setText(QCoreApplication::translate("HomeTab", "ICON", nullptr));
        pushButton->setText(QCoreApplication::translate("HomeTab", "Rain", nullptr));
        label_12->setText(QString());
        label_13->setText(QString());
        pushButton_3->setText(QCoreApplication::translate("HomeTab", "Wind", nullptr));
        pushButton_5->setText(QCoreApplication::translate("HomeTab", "Light", nullptr));
        pushButton_6->setText(QCoreApplication::translate("HomeTab", "Heat", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HomeTab: public Ui_HomeTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMETAB_H
