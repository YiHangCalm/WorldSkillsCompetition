#include <QApplication>
#include "mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // ȫ���쳣��������
    try {
        w.show();
        return a.exec();
    } catch (const std::exception &e) {
        QFile logFile("application.log");
        if (logFile.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&logFile);
            out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")
                << " - Unhandled exception: " << e.what() << "\n";
        }
        logFile.close();
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
        return -1;
    } catch (...) {
        QFile logFile("application.log");
        if (logFile.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&logFile);
            out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")
                << " - Unknown unhandled exception occurred\n";
        }
        logFile.close();
        std::cerr << "Unknown unhandled exception occurred." << std::endl;
        return -1;
    }
}
