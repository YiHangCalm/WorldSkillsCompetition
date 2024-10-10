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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScanColor
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QTextEdit *informationEdit;
    QPushButton *exitButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ScanColor)
    {
        if (ScanColor->objectName().isEmpty())
            ScanColor->setObjectName(QString::fromUtf8("ScanColor"));
        ScanColor->resize(800, 600);
        centralwidget = new QWidget(ScanColor);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(254, 20, QSizePolicy::Ignored, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        informationEdit = new QTextEdit(centralwidget);
        informationEdit->setObjectName(QString::fromUtf8("informationEdit"));

        gridLayout->addWidget(informationEdit, 0, 1, 2, 2);

        exitButton = new QPushButton(centralwidget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        QFont font;
        font.setPointSize(20);
        exitButton->setFont(font);

        gridLayout->addWidget(exitButton, 2, 2, 1, 1);

        ScanColor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ScanColor);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
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
        exitButton->setText(QCoreApplication::translate("ScanColor", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScanColor: public Ui_ScanColor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCANCOLOR_H
