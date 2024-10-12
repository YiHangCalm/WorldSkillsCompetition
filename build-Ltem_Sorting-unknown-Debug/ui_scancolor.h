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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScanColor
{
public:
    QWidget *centralwidget;
    QTextEdit *informationEdit;
    QPushButton *exButton;
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
"}"));
        centralwidget = new QWidget(ScanColor);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        informationEdit = new QTextEdit(centralwidget);
        informationEdit->setObjectName(QString::fromUtf8("informationEdit"));
        informationEdit->setGeometry(QRect(0, 0, 581, 491));
        exButton = new QPushButton(centralwidget);
        exButton->setObjectName(QString::fromUtf8("exButton"));
        exButton->setGeometry(QRect(790, 480, 181, 71));
        QFont font;
        exButton->setFont(font);
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
        exButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ScanColor: public Ui_ScanColor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCANCOLOR_H
