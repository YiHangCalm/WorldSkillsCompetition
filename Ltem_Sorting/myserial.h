#ifndef MYSERIAL_H
#define MYSERIAL_H

#include "mainwindow.h"
#include <QSerialPort>
#include <ui_myserial.h>
#include <QMainWindow>

class MySerial : public QMainWindow
{
    Q_OBJECT

public:
    explicit MySerial(QWidget *parent = nullptr);
    ~MySerial();
    void sendData(const QString &dataToSend);
private slots:
    void on_exButton_Release();
    void recvSLOTS();
    void on_open_clicked();

private:
    Ui::MySerial *ui;
    QSerialPort *serialPort_;
};

#endif // MYSERIAL_H
