/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *modeButton;
    QSpacerItem *verticalSpacer_2;
    QPushButton *ColourButton;
    QSpacerItem *verticalSpacer_5;
    QPushButton *InspectButton;
    QSpacerItem *verticalSpacer_6;
    QPushButton *exitButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setStyleSheet(QString::fromUtf8("#MainWindow {\n"
"    background-image: url(:/new/prefix1/Rese/back.png);\n"
"    background-position: center;\n"
"    background-repeat: no-repeat; \n"
"  \n"
"}\n"
"#centralwidget {\n"
"    background: transparent;\n"
"}\n"
"\n"
"QPushButton#modeButton {\n"
"    background-color: rgb(34, 255, 211);\n"
"    color: black;\n"
"    width: 150px;  \n"
"    height: 50px; \n"
"	font-size: 16px; \n"
"}\n"
"\n"
"QPushButton#ColourButton {\n"
"    background-color: rgb(34, 255, 211);\n"
"    color: black;\n"
"    width: 150px;  \n"
"    height: 50px;   \n"
"	font-size: 16px;\n"
"}\n"
"QPushButton#InspectButton{\n"
"    background-color: rgb(34, 255, 211);\n"
"    color: black;\n"
"    width: 150px;   \n"
"    height: 50px;\n"
"	font-size: 16px;   \n"
"}\n"
"QPushButton#exitButton {\n"
"    background-color: rgb(34, 255, 211);\n"
"    color: black;\n"
"    width: 150px;   \n"
"    height: 50px;   \n"
"	font-size: 16px;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(770, 60, 176, 452));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        modeButton = new QPushButton(widget);
        modeButton->setObjectName(QString::fromUtf8("modeButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(modeButton->sizePolicy().hasHeightForWidth());
        modeButton->setSizePolicy(sizePolicy1);
        modeButton->setMaximumSize(QSize(200, 600));
        QFont font;
        modeButton->setFont(font);
        modeButton->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(modeButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        ColourButton = new QPushButton(widget);
        ColourButton->setObjectName(QString::fromUtf8("ColourButton"));

        verticalLayout->addWidget(ColourButton);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        InspectButton = new QPushButton(widget);
        InspectButton->setObjectName(QString::fromUtf8("InspectButton"));

        verticalLayout->addWidget(InspectButton);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);

        exitButton = new QPushButton(widget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\347\202\271\351\230\265\346\255\243\351\273\221"));
        exitButton->setFont(font1);

        verticalLayout->addWidget(exitButton);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 21));
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
        modeButton->setText(QCoreApplication::translate("MainWindow", "QRCode_Mode", nullptr));
        ColourButton->setText(QCoreApplication::translate("MainWindow", "Colour_Mode", nullptr));
        InspectButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        exitButton->setText(QCoreApplication::translate("MainWindow", "EXIT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
