#ifndef MYSERIAL_H
#define MYSERIAL_H

#include "mainwindow.h"
#include <QSerialPort>
#include <ui_myserial.h>
#include <QMainWindow>
#include "btneffect.h"
#include "mytimer.h"
class MySerial : public QMainWindow
{
    Q_OBJECT

public:
    explicit MySerial(QWidget *parent = nullptr);
    ~MySerial();
    void sendData(const QString &dataToSend);
    void openConnection();

   void sendDataPacket(const QString &dataToSend);
private slots:
    void on_exButton_Release();
    void recvSLOTS();
    void on_open_clicked();
   // void   on_senddata_Pressed();
    void on_senddata_clicked();

private:
    Ui::MySerial *ui;
   std::unique_ptr<BtnEffect> btn;
    QSerialPort *serialPort_;
    mytimer mytimer;
};

#endif // MYSERIAL_H
