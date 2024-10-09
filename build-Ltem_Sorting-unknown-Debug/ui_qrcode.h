/********************************************************************************
** Form generated from reading UI file 'qrcode.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QRCODE_H
#define UI_QRCODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qrcode
{
public:
    QWidget *centralwidget;
    QTextEdit *informationEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *qrcode)
    {
        if (qrcode->objectName().isEmpty())
            qrcode->setObjectName(QString::fromUtf8("qrcode"));
        qrcode->resize(800, 600);
        centralwidget = new QWidget(qrcode);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        informationEdit = new QTextEdit(centralwidget);
        informationEdit->setObjectName(QString::fromUtf8("informationEdit"));
        informationEdit->setGeometry(QRect(350, 0, 201, 241));
        qrcode->setCentralWidget(centralwidget);
        menubar = new QMenuBar(qrcode);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        qrcode->setMenuBar(menubar);
        statusbar = new QStatusBar(qrcode);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        qrcode->setStatusBar(statusbar);

        retranslateUi(qrcode);

        QMetaObject::connectSlotsByName(qrcode);
    } // setupUi

    void retranslateUi(QMainWindow *qrcode)
    {
        qrcode->setWindowTitle(QCoreApplication::translate("qrcode", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class qrcode: public Ui_qrcode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QRCODE_H
