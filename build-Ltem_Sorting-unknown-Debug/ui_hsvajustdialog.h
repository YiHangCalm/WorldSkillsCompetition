/********************************************************************************
** Form generated from reading UI file 'hsvajustdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HSVAJUSTDIALOG_H
#define UI_HSVAJUSTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HSVAjustDialog
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *HSVAjustDialog)
    {
        if (HSVAjustDialog->objectName().isEmpty())
            HSVAjustDialog->setObjectName(QString::fromUtf8("HSVAjustDialog"));
        HSVAjustDialog->resize(800, 600);
        menubar = new QMenuBar(HSVAjustDialog);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        HSVAjustDialog->setMenuBar(menubar);
        centralwidget = new QWidget(HSVAjustDialog);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        HSVAjustDialog->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(HSVAjustDialog);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        HSVAjustDialog->setStatusBar(statusbar);

        retranslateUi(HSVAjustDialog);

        QMetaObject::connectSlotsByName(HSVAjustDialog);
    } // setupUi

    void retranslateUi(QMainWindow *HSVAjustDialog)
    {
        HSVAjustDialog->setWindowTitle(QCoreApplication::translate("HSVAjustDialog", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HSVAjustDialog: public Ui_HSVAjustDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HSVAJUSTDIALOG_H
