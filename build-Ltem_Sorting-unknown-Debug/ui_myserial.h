/********************************************************************************
** Form generated from reading UI file 'myserial.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYSERIAL_H
#define UI_MYSERIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MySerial
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QFormLayout *formLayout;
    QLabel *label;
    QComboBox *serial;
    QLabel *label_2;
    QComboBox *baudrate;
    QLabel *label_3;
    QComboBox *stop;
    QLabel *label_4;
    QComboBox *data;
    QLabel *label_5;
    QComboBox *parity;
    QPushButton *open;
    QTextEdit *textEdit;
    QPushButton *exButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MySerial)
    {
        if (MySerial->objectName().isEmpty())
            MySerial->setObjectName(QString::fromUtf8("MySerial"));
        MySerial->resize(1024, 600);
        MySerial->setStyleSheet(QString::fromUtf8("#MySerial {\n"
"\n"
"    background-image: url(:/new/btn/Rese/backgud.png);\n"
"    background-position: center;\n"
"    background-repeat: no-repeat; \n"
"  \n"
"}\n"
"#textEdit {\n"
"    background-color: #1E3A8A;\n"
"    border: 2px solid white;  \n"
"    font-size: 16px;      \n"
"    color: white;            \n"
"}\n"
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
"     width: 200;  \n"
"    height: 80px; \n"
"	font-size: 16px;\n"
"	border: none;\n"
"}\n"
"QPushButton#open {\n"
"    border-image: url(:/new/btn/Rese/exmode.png);\n"
"    \n"
"     width: 200;  \n"
"    height: 80px; \n"
"	font-size: 16px;\n"
"	border: none;\n"
"}"));
        centralwidget = new QWidget(MySerial);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(608, 10, 331, 201));
        formLayout = new QFormLayout(widget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        serial = new QComboBox(widget);
        serial->setObjectName(QString::fromUtf8("serial"));

        formLayout->setWidget(0, QFormLayout::FieldRole, serial);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        baudrate = new QComboBox(widget);
        baudrate->setObjectName(QString::fromUtf8("baudrate"));

        formLayout->setWidget(1, QFormLayout::FieldRole, baudrate);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        stop = new QComboBox(widget);
        stop->setObjectName(QString::fromUtf8("stop"));

        formLayout->setWidget(2, QFormLayout::FieldRole, stop);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        data = new QComboBox(widget);
        data->setObjectName(QString::fromUtf8("data"));

        formLayout->setWidget(3, QFormLayout::FieldRole, data);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        parity = new QComboBox(widget);
        parity->setObjectName(QString::fromUtf8("parity"));

        formLayout->setWidget(4, QFormLayout::FieldRole, parity);

        open = new QPushButton(centralwidget);
        open->setObjectName(QString::fromUtf8("open"));
        open->setGeometry(QRect(720, 210, 181, 61));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(0, 0, 521, 421));
        exButton = new QPushButton(centralwidget);
        exButton->setObjectName(QString::fromUtf8("exButton"));
        exButton->setGeometry(QRect(720, 360, 181, 61));
        MySerial->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MySerial);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 21));
        MySerial->setMenuBar(menubar);
        statusbar = new QStatusBar(MySerial);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MySerial->setStatusBar(statusbar);

        retranslateUi(MySerial);

        QMetaObject::connectSlotsByName(MySerial);
    } // setupUi

    void retranslateUi(QMainWindow *MySerial)
    {
        MySerial->setWindowTitle(QCoreApplication::translate("MySerial", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MySerial", "\344\270\262\345\217\243\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("MySerial", "\346\263\242\347\211\271\347\216\207\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("MySerial", "\345\201\234\346\255\242\344\275\215\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("MySerial", "\346\225\260\346\215\256\344\275\215\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("MySerial", "\345\245\207\345\201\266\346\240\241\351\252\214\344\275\215\357\274\232", nullptr));
        open->setText(QString());
        exButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MySerial: public Ui_MySerial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYSERIAL_H
