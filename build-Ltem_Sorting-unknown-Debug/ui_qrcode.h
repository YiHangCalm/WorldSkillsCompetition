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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qrcode
{
public:
    QWidget *centralwidget;
    QTableWidget *tableWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *slowButton;
    QSpacerItem *verticalSpacer_3;
    QPushButton *fastButton;
    QSpacerItem *verticalSpacer_2;
    QPushButton *exButton;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *qrcode)
    {
        if (qrcode->objectName().isEmpty())
            qrcode->setObjectName(QString::fromUtf8("qrcode"));
        qrcode->resize(1024, 600);
        qrcode->setStyleSheet(QString::fromUtf8("#qrcode {\n"
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
"QPushButton#slowButton {\n"
"    border-image: url(:/new/btn/Rese/fast.png);\n"
"    \n"
"     width: 203;  \n"
"    height: 80px; \n"
"	font-size: 16px;\n"
"	border: none;\n"
"}\n"
"QPushButton#fastButton {\n"
"    border-image: url(:/new/btn/Rese/slow.png);\n"
"    \n"
"     width: 203;  \n"
"    height: 80px; \n"
"	font-size: 16px;\n"
"	border: none;\n"
"}"));
        centralwidget = new QWidget(qrcode);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(0, 0, 711, 573));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(18);
        tableWidget->setFont(font);
        tableWidget->horizontalHeader()->setMinimumSectionSize(33);
        tableWidget->horizontalHeader()->setDefaultSectionSize(110);
        tableWidget->verticalHeader()->setMinimumSectionSize(50);
        tableWidget->verticalHeader()->setDefaultSectionSize(70);
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(760, 290, 221, 271));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        slowButton = new QPushButton(widget);
        slowButton->setObjectName(QString::fromUtf8("slowButton"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\226\207\346\263\211\351\251\277\347\202\271\351\230\265\346\255\243\351\273\221"));
        slowButton->setFont(font1);

        verticalLayout->addWidget(slowButton);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        fastButton = new QPushButton(widget);
        fastButton->setObjectName(QString::fromUtf8("fastButton"));
        fastButton->setFont(font1);

        verticalLayout->addWidget(fastButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        exButton = new QPushButton(widget);
        exButton->setObjectName(QString::fromUtf8("exButton"));
        exButton->setFont(font1);

        verticalLayout->addWidget(exButton);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

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
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("qrcode", "\347\274\226\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("qrcode", "\345\207\272\345\217\221\345\234\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("qrcode", "\345\210\260\350\276\276\345\234\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("qrcode", "\345\214\205\350\243\271\347\261\273\345\236\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("qrcode", "\346\211\253\346\217\217\346\227\266\351\227\264", nullptr));
        slowButton->setText(QString());
        fastButton->setText(QString());
        exButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class qrcode: public Ui_qrcode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QRCODE_H
