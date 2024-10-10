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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qrcode
{
public:
    QWidget *centralwidget;
    QTextEdit *informationEdit;
    QPushButton *pushButton;
    QTableWidget *tableWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *qrcode)
    {
        if (qrcode->objectName().isEmpty())
            qrcode->setObjectName(QString::fromUtf8("qrcode"));
        qrcode->resize(1024, 600);
        centralwidget = new QWidget(qrcode);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        informationEdit = new QTextEdit(centralwidget);
        informationEdit->setObjectName(QString::fromUtf8("informationEdit"));
        informationEdit->setGeometry(QRect(0, 240, 321, 291));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\345\276\256\347\261\263\351\273\221"));
        font.setPointSize(28);
        informationEdit->setFont(font);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(830, 440, 191, 121));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\347\202\271\351\230\265\346\255\243\351\273\221"));
        font1.setPointSize(16);
        pushButton->setFont(font1);
        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(320, 0, 711, 441));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setPointSize(20);
        tableWidget->setFont(font2);
        tableWidget->horizontalHeader()->setDefaultSectionSize(110);
        tableWidget->verticalHeader()->setMinimumSectionSize(70);
        tableWidget->verticalHeader()->setDefaultSectionSize(70);
        qrcode->setCentralWidget(centralwidget);
        menubar = new QMenuBar(qrcode);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1024, 21));
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
        pushButton->setText(QCoreApplication::translate("qrcode", "\350\277\224\345\233\236", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("qrcode", "\345\207\272\345\217\221\345\234\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("qrcode", "\345\210\260\350\276\276\345\234\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("qrcode", "\345\214\205\350\243\271\347\261\273\345\236\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class qrcode: public Ui_qrcode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QRCODE_H
