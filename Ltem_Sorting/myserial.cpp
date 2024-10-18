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
        // �� QString ת��Ϊ UTF-8 ������ QByteArray
        QByteArray data = dataToSend.toUtf8();

        // �������ݵ�����
        qint64 bytesWritten = serialPort_->write(data);

        // ���鷢���Ƿ��ɹ�
        if (bytesWritten == -1) {
            QMessageBox::warning(this, "Warning", "Failed to send data: " + serialPort_->errorString());
        } else {
            qDebug() << "Successfully sent data, bytes written:" << bytesWritten;
        //    ui->textEdit->append("发送: " + dataToSend);
        }
    }

    void MySerial::openConnection()
    {
            on_open_clicked();  // �ӹ��������е���˽�з���
    }
    void MySerial::sendDataPacket(const QString &dataToSend, PacketType packetType)
    {
        // �������ݰ�
        QByteArray packet;

        // ���Ӱ�ͷ
        packet.append(0x3a);  // �̶���ͷ 0x3a

        // ���Ӱ�ͷ�ڶ����ֽڣ�������������������
        if (packetType == PacketType::Command) {
            packet.append(0x3b);  // ������ͷ 0x3d
        } else {
            packet.append(0x3d);  // ���ݰ�ͷ 0x3b
        }

        // Ϊ�ַ�����������ǰ׺



        packet.append(dataToSend);


        packet.append(0x3c);


        qint64 bytesWritten = serialPort_->write(packet);


        if (bytesWritten == -1) {
            QMessageBox::warning(this, "Warning", "Failed to send data packet: " + serialPort_->errorString());
        } else {
            qDebug() << "Successfully sent data packet, bytes written:" << bytesWritten;
            qDebug() << "Packet sent: " << packet.toHex();
        }
    }
    void MySerial::recvSLOTS()
    {
        qDebug() << "recvSLOTS 被调用 ";
           QByteArray data = serialPort_->readAll();
           if (data.isEmpty()) {
               qDebug() << "没有读到数据";
               return;
           }
           QString formattedData = "收到数据：: " + QString::fromUtf8(data);
           ui->textEdit->append(formattedData);
    }


    void MySerial::on_open_clicked()
    {
        btn = std::make_unique<BtnEffect>(ui->open);
        btn->zoom1();
        if (btn) {
            QEventLoop loop;
            connect(btn->getAnimation(), &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
            btn->zoom2();
            loop.exec();
            btn.reset();
        }
        if (serialPort_->isOpen()) {
            QString formattedData = "关闭端口";
            serialPort_->close();
            ui->textEdit->append(formattedData);
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
            QString formatt = QString("打开 %1 端口").arg(portName);
            ui->textEdit->append(formatt);
        }
    }

    void MySerial::on_exButton_Release()
    {
        this->hide(); // ���ص�ǰ����
        if (auto mainWindow = dynamic_cast<MainWindow*>(parent())) {
            mainWindow->show(); // ��ʾ������
        }
    }

//    void MySerial::on_senddata_Pressed()
//    {
//        btn = std::make_unique<BtnEffect>(ui->senddata);
//        btn->zoom1();
//    }
\
    void MySerial::on_senddata_clicked()
    {
        btn = std::make_unique<BtnEffect>(ui->senddata);
        btn->zoom1();
        if (btn) {
            QEventLoop loop;
            connect(btn->getAnimation(), &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
            btn->zoom2();
            loop.exec();
            btn.reset();
        }

        // ���鴮���Ƿ�����
        if (!serialPort_->isOpen()) {
            qDebug() << "Serial port not open.";
            return;
        }

        // ��ȡ QPlainTextEdit �������ı�
        QPlainTextEdit* plainText = ui->plainTextEdit;
        QString dataToSend = plainText->toPlainText().trimmed();  // ȥ����β�ո�

        // ��ʾ���͵�ʱ��������
        ui->textEdit->append(QString("%1 发送: %2")
                             .arg(mytimer.getCurrentTime())
                             .arg(dataToSend));

        // ͨ�� sendData ������������
        if (!dataToSend.isEmpty()) {  // ֻ�зǿ��ı��ŷ���
            sendData(dataToSend);  // ���� sendData ��������
        } else {
            qDebug() << "No data to send.";
        }
    }

void MySerial::on_senddata_2_clicked()
{
    btn = std::make_unique<BtnEffect>(ui->senddata_2);
    btn->zoom1();
    if (btn) {
        QEventLoop loop;
        connect(btn->getAnimation(), &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
        btn->zoom2();
        loop.exec();
        btn.reset();
    }

    // ���鴮���Ƿ�����
    if (!serialPort_->isOpen()) {
        qDebug() << "Serial port not open.";
        return;
    }

    // ��ȡ QPlainTextEdit �������ı�
    QPlainTextEdit* plainText = ui->plainTextEdit;
    QString dataToSend = plainText->toPlainText().trimmed();  // ȥ����β�ո�

    // ��ʾ���͵�ʱ��������
    ui->textEdit->append(QString("%1 发送数据包: %2")
                         .arg(mytimer.getCurrentTime())
                         .arg(dataToSend));

    // ͨ�� sendData ������������
    if (!dataToSend.isEmpty()) {  // ֻ�зǿ��ı��ŷ���
        sendDataPacket(dataToSend,PacketType::Data);
    } else {
        qDebug() << "No data to send.";
    }
}


