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
    QSpacerItem *verticalSpacer_5;
    QPushButton *modeButton;
    QSpacerItem *verticalSpacer_4;
    QPushButton *ColourButton;
    QSpacerItem *verticalSpacer_3;
    QPushButton *usatbtn;
    QSpacerItem *verticalSpacer_2;
    QPushButton *exitButton;
    QSpacerItem *verticalSpacer;
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
"\n"
"    background-image: url(:/new/prefix1/Rese/back.png);\n"
"    background-position: center;\n"
"    background-repeat: no-repeat; \n"
"  \n"
"}\n"
"\n"
"#centralwidget {\n"
"    background: transparent;\n"
"   border: none;\n"
"        background: transparent;\n"
"        padding: 0;\n"
"       margin: 0; \n"
"}\n"
"\n"
"QWidget#widget {\n"
"        border: none;\n"
"        background: transparent;\n"
"        padding: 0;\n"
"       margin: 0; \n"
"    }\n"
"QPushButton#modeButton {\n"
"	\n"
"  	 border: none; \n"
"    background: none;  \n"
"	border-image: url(:/new/btn/Rese/qrbtn.png);\n"
"    color: black;\n"
"    width: 203;  \n"
"    height: 80px; \n"
"	\n"
"}\n"
"\n"
"QPushButton#ColourButton {\n"
"\n"
"    \n"
"	border-image: url(:/new/btn/Rese/clrbtn.png);\n"
"   \n"
"     width: 203;  \n"
"    height: 80px; \n"
"	font-size: 16px;\n"
"	border: none;\n"
"}\n"
"QPushButton#InspectButton{\n"
"    \n"
"	border-image: url(:/new/btn/Rese/jiancebtn.png);\n"
"    \n"
"     width: 203; "
                        " \n"
"    height: 80px; \n"
"	font-size: 16px;   \n"
"	border: none;\n"
"}\n"
"QPushButton#usatbtn {\n"
"	\n"
"  	border-image: url(:/new/btn/Rese/jiancebtn.png);\n"
"    \n"
"     width: 203;  \n"
"    height: 80px; \n"
"	font-size: 16px;   \n"
"	border: none;\n"
"	\n"
"}\n"
"QPushButton#exitButton {\n"
"    border-image: url(:/new/btn/Rese/exbtn.png);\n"
"    \n"
"     width: 203;  \n"
"    height: 80px; \n"
"	font-size: 16px;\n"
"	border: none;\n"
"}\n"
"QPushButton:focus {\n"
"        outline: none;\n"
"    }"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(730, 20, 241, 501));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        modeButton = new QPushButton(widget);
        modeButton->setObjectName(QString::fromUtf8("modeButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(modeButton->sizePolicy().hasHeightForWidth());
        modeButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(modeButton);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        ColourButton = new QPushButton(widget);
        ColourButton->setObjectName(QString::fromUtf8("ColourButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(203);
        sizePolicy2.setHeightForWidth(ColourButton->sizePolicy().hasHeightForWidth());
        ColourButton->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(ColourButton);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        usatbtn = new QPushButton(widget);
        usatbtn->setObjectName(QString::fromUtf8("usatbtn"));
        sizePolicy1.setHeightForWidth(usatbtn->sizePolicy().hasHeightForWidth());
        usatbtn->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(usatbtn);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        exitButton = new QPushButton(widget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        sizePolicy1.setHeightForWidth(exitButton->sizePolicy().hasHeightForWidth());
        exitButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(exitButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

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
        modeButton->setText(QString());
        ColourButton->setText(QString());
        usatbtn->setText(QString());
        exitButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
