/********************************************************************************
** Form generated from reading UI file 'scancolor.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCANCOLOR_H
#define UI_SCANCOLOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScanColor
{
public:
    QWidget *centralwidget;
    QTextEdit *informationEdit;
    QLabel *HSV;
    QLabel *bin;
    QWidget *widget_2;
    QGridLayout *gridLayout;
    QPushButton *appoint;
    QPushButton *sorte;
    QPushButton *adjust;
    QPushButton *exButton;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *blue;
    QPushButton *red;
    QPushButton *green;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ScanColor)
    {
        if (ScanColor->objectName().isEmpty())
            ScanColor->setObjectName(QString::fromUtf8("ScanColor"));
        ScanColor->resize(1024, 600);
        ScanColor->setStyleSheet(QString::fromUtf8("#ScanColor {\n"
"\n"
"    background-image: url(:/new/btn/Rese/backgud.png);\n"
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
"QPushButton#exButton {\n"
"    border-image: url(:/new/btn/Rese/exmode.png);\n"
"    \n"
"     width: 203;  \n"
"    height: 80px; \n"
"	font-size: 16px;\n"
"	border: none;\n"
"}\n"
"QPushButton#adjust {\n"
"    border-image: url(:/new/btn/Rese/HSV.png);\n"
"    \n"
"     width: 203;  \n"
"    height: 80px; \n"
"	font-size: 16px;\n"
"	border: none;\n"
"}\n"
"QPushButton#sorte {\n"
"    border-image: url(:/new/btn/Rese/fast.png);\n"
"    \n"
"     width: 203;  \n"
"    height: 80px; \n"
"	font-size: 16px;\n"
"	border: none;\n"
"}\n"
"\n"
"QPushButton#appoint {\n"
"    border-image: url(:/new/btn/Rese/slow.png);\n"
"    \n"
"     width: 203;  \n"
"    height: 80px; \n"
"	font-si"
                        "ze: 16px;\n"
"	border: none;\n"
"}\n"
"QPushButton#red {\n"
"    border-image: url(:/new/btn/Rese/red.png);\n"
"    \n"
"     width: 203;  \n"
"    height: 80px; \n"
"	font-size: 16px;\n"
"	border: none;\n"
"}\n"
"QPushButton#blue {\n"
"    border-image: url(:/new/btn/Rese/blue.png);\n"
"    \n"
"     width: 203;  \n"
"    height: 80px; \n"
"	font-size: 16px;\n"
"	border: none;\n"
"}\n"
"QPushButton#green {\n"
"    border-image: url(:/new/btn/Rese/green.png);\n"
"    \n"
"     width: 203;  \n"
"    height: 80px; \n"
"	font-size: 16px;\n"
"	border: none;\n"
"}"));
        centralwidget = new QWidget(ScanColor);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        informationEdit = new QTextEdit(centralwidget);
        informationEdit->setObjectName(QString::fromUtf8("informationEdit"));
        informationEdit->setGeometry(QRect(0, 270, 341, 301));
        HSV = new QLabel(centralwidget);
        HSV->setObjectName(QString::fromUtf8("HSV"));
        HSV->setGeometry(QRect(350, 0, 320, 240));
        bin = new QLabel(centralwidget);
        bin->setObjectName(QString::fromUtf8("bin"));
        bin->setGeometry(QRect(0, 0, 320, 240));
        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(820, 260, 201, 301));
        gridLayout = new QGridLayout(widget_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        appoint = new QPushButton(widget_2);
        appoint->setObjectName(QString::fromUtf8("appoint"));
        QFont font;
        appoint->setFont(font);

        gridLayout->addWidget(appoint, 0, 0, 1, 1);

        sorte = new QPushButton(widget_2);
        sorte->setObjectName(QString::fromUtf8("sorte"));
        sorte->setFont(font);

        gridLayout->addWidget(sorte, 1, 0, 1, 1);

        adjust = new QPushButton(widget_2);
        adjust->setObjectName(QString::fromUtf8("adjust"));
        adjust->setFont(font);

        gridLayout->addWidget(adjust, 2, 0, 1, 1);

        exButton = new QPushButton(widget_2);
        exButton->setObjectName(QString::fromUtf8("exButton"));
        exButton->setFont(font);

        gridLayout->addWidget(exButton, 3, 0, 1, 1);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(570, 270, 221, 270));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        blue = new QPushButton(widget);
        blue->setObjectName(QString::fromUtf8("blue"));
        blue->setFont(font);

        verticalLayout->addWidget(blue);

        red = new QPushButton(widget);
        red->setObjectName(QString::fromUtf8("red"));
        red->setFont(font);

        verticalLayout->addWidget(red);

        green = new QPushButton(widget);
        green->setObjectName(QString::fromUtf8("green"));
        green->setFont(font);

        verticalLayout->addWidget(green);

        ScanColor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ScanColor);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 21));
        ScanColor->setMenuBar(menubar);
        statusbar = new QStatusBar(ScanColor);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ScanColor->setStatusBar(statusbar);

        retranslateUi(ScanColor);

        QMetaObject::connectSlotsByName(ScanColor);
    } // setupUi

    void retranslateUi(QMainWindow *ScanColor)
    {
        ScanColor->setWindowTitle(QCoreApplication::translate("ScanColor", "MainWindow", nullptr));
        HSV->setText(QString());
        bin->setText(QString());
        appoint->setText(QString());
        sorte->setText(QString());
        adjust->setText(QString());
        exButton->setText(QString());
        blue->setText(QString());
        red->setText(QString());
        green->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ScanColor: public Ui_ScanColor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCANCOLOR_H
