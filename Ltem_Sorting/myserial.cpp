#include "myserial.h"
#include "ui_myserial.h"
#include <QMessageBox>
#include <QSerialPortInfo>

MySerial::MySerial(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MySerial),
    serialPort_(new QSerialPort(this))
{
    ui->setupUi(this);

    auto portsinfo = QSerialPortInfo::availablePorts();
        for(auto&info: portsinfo){
            //���������� �˿����� ��ϵͳλ�� ,
            qInfo()<<info.description()<<info.portName()<<info.systemLocation();
            ui->serial->addItem(info.portName()+":"+info.description(),info.portName());//�ڰ�ť��ʾ����
        }
    connect(ui->exButton, &QPushButton::  released, this, &MySerial::on_exButton_Release);
    connect(serialPort_, &QSerialPort::readyRead, this, &MySerial::recvSLOTS);
    auto baudRates = QSerialPortInfo::standardBaudRates();
        for(auto br :baudRates){
            ui->baudrate->addItem(QString::number(br),br);

        }
        ui->baudrate->setCurrentText("9600");

        ui->stop->addItem("1",QSerialPort::OneStop);
        ui->stop->addItem("1.5",QSerialPort::OneAndHalfStop);
        ui->stop->addItem("2",QSerialPort::TwoStop);

        ui->data->addItem("5",QSerialPort::Data5);
        ui->data->addItem("6",QSerialPort::Data6);
        ui->data->addItem("7",QSerialPort::Data7);
        ui->data->addItem("8",QSerialPort::Data8);
        ui->data->setCurrentText("8");

        ui->parity->addItem("Noparity",   QSerialPort::NoParity);
        ui->parity->addItem("EvenParity", QSerialPort::EvenParity);
        ui->parity->addItem("OddParity",  QSerialPort::OddParity);
        ui->parity->addItem("SpaceParity",QSerialPort::SpaceParity);
        ui->parity->addItem("MarkParity", QSerialPort::MarkParity);
}

MySerial::~MySerial()
{
    delete ui;
}

void MySerial::sendData(const QString &dataToSend)
{
    QByteArray data = dataToSend.toUtf8();
    serialPort_->write(data);

    QString formattedData = "发送数据：" + dataToSend;  // "���ͣ�" + dataToSend
    ui->textEdit->append(formattedData);
}

void MySerial::recvSLOTS()
{
    QByteArray data = serialPort_->readAll();
    QString formattedData = "收到数据：" + QString::fromUtf8(data);  // "���գ�" + received data
    ui->textEdit->append(formattedData);
}

void MySerial::on_open_clicked()
{
    if (serialPort_->isOpen()) {
        QString formattedData = "串口已关闭";
        serialPort_->close();

        return;
    }

   auto portName = ui->serial->currentData().toString();
    QSerialPort::BaudRate baudRate = static_cast<QSerialPort::BaudRate>(ui->baudrate->currentData().toInt());
    QSerialPort::DataBits dataBits = static_cast<QSerialPort::DataBits>(ui->data->currentData().toInt());
    QSerialPort::StopBits stopBits = static_cast<QSerialPort::StopBits>(ui->stop->currentData().toInt());
    QSerialPort::Parity parity = static_cast<QSerialPort::Parity>(ui->parity->currentData().toInt());

    serialPort_->setPortName(portName);
    serialPort_->setBaudRate(baudRate);
    serialPort_->setDataBits(dataBits);
    serialPort_->setStopBits(stopBits);
    serialPort_->setParity(parity);

    if (!serialPort_->open(QIODevice::ReadWrite)) {
        QMessageBox::warning(this, "Warning", portName + " open failed: " + serialPort_->errorString());
    } else {
        QString formatt = QString("串口: %1 已打开").arg(portName);
        ui->textEdit->append(formatt);
    }

}
void MySerial::on_exButton_Release()
{
    this->hide(); // ���ش��ڽ���
    if (auto mainWindow = dynamic_cast<MainWindow*>(parent())) {
            mainWindow->show(); // ��ʾ������
        }
}
