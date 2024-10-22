#include "qrcode.h"
#include <QDebug>
#include <QMutex>
QRCode::QRCode(QWidget *parent)
    : QMainWindow(parent), camera(nullptr), lastDecodedText(""),currentMode(classification),variable(yunting)
{
    ui.setupUi(this);
    this->showFullScreen();
    ui.tableWidget->verticalHeader()->setVisible(false); // ������ͷ�����ţ�
    ui.tableWidget->setFixedHeight(560);
     ui.widget2->hide();
    ui.tableWidget->setStyleSheet(
        "QTableWidget {"
        "   background-color: #1E3A8A;"
        "   alternate-background-color: #004080;"
        "   gridline-color: #ffffff;"
        "   border: 2px solid #ffffff;"  // ���ð�ɫ�߿�
        "   color: #ffffff;"
        "}"
        "QHeaderView::section {"
        "   background-color: #002244;"
        "   color: #ffffff;"
        "   font-weight: bold;"
        "   padding: 6px;"
        "   border: 1px solid #ffffff;"
        "}"
        "QTableWidget::item {"
        "   border: 1px solid #004080;"
        "   padding: 6px;"
        "}"
        "QTableWidget::item:selected {"
        "   background-color: #0066cc;"
        "   color: #ffffff;"
        "}"
    );
    QFont headerFont = ui.tableWidget->horizontalHeader()->font();
       headerFont.setPointSize(20);  // ����������С
      headerFont.setBold(true);     // ���������Ӵ֣���ѡ��

      QFont tableFont = ui.tableWidget->font();
     tableFont.setPointSize(18); // ����������С
    ui.tableWidget->setFont(tableFont);

    ui.tableWidget->setColumnWidth(0, 110);
    ui.tableWidget->setColumnWidth(1, 140);
    ui.tableWidget->setColumnWidth(2, 140);
    ui.tableWidget->setColumnWidth(3, 170);
    ui.tableWidget->setColumnWidth(4, 160);
    connect(ui.exButton, &QPushButton::pressed, this, &QRCode::on_exButton_Release);
    //connect(ui.slowButton, &QPushButton::released, this, &QRCode::on_slowButton_Pressed);
    //connect(ui.fastButton, &QPushButton::released, this, &QRCode::on_fastButton_Pressed);
}

void QRCode::enterMode(QWidget *parentWidget)
{
    if (!camera) {
        camera = std::make_unique<ExternalCamera>(this);
        camera->start();
    }

    this->execute();
    this->show(); // ȷ��������ʾ��ǰ̨
}

void QRCode::execute()
{
    if (!camera) return;

    if (!signalConnected) {
        if (QObject::connect(camera.get(), &ExternalCamera::frameReady, this, [this](const cv::Mat &frame) {
            processFrame(frame);
        })) {
            signalConnected = true;
        } else {
            qDebug() << "Failed to connect camera signal to processFrame";
        }
    }
}

void QRCode::exitMode()
{
    if (camera) {
        camera->stop();
        camera.reset();
    }

    if (isProcessing) {
        // �ȴ���ǰ�߳�����
        QThread::currentThread()->wait();

        isProcessing = false;
    }

    signalConnected = false;

    if (parentWidget()) {
        parentWidget()->show();
    }

    this->hide();
}

void QRCode::show()
{
    QMainWindow::show();
    this->raise();
    this->activateWindow();
}

void QRCode::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        if (isFullScreen()) {
            showNormal();
        } else {
            showFullScreen();
        }
    }
}


void QRCode::checkDamagedQRCode()
{
    int row = ui.tableWidget->rowCount();
    ui.tableWidget->insertRow(row);

    std::unique_ptr<QTableWidgetItem> item0(new QTableWidgetItem(QString::number(currentIndex++)));
    item0->setTextAlignment(Qt::AlignCenter);
    ui.tableWidget->setItem(row, 0, item0.release());

    std::unique_ptr<QTableWidgetItem> item1(new QTableWidgetItem("Damaged"));
    item1->setTextAlignment(Qt::AlignCenter);
    ui.tableWidget->setItem(row, 1, item1.release());

    std::unique_ptr<QTableWidgetItem> item2(new QTableWidgetItem("Damaged"));
    item2->setTextAlignment(Qt::AlignCenter);
    ui.tableWidget->setItem(row, 2, item2.release());

    std::unique_ptr<QTableWidgetItem> item3(new QTableWidgetItem("Damaged"));
    item3->setTextAlignment(Qt::AlignCenter);
    ui.tableWidget->setItem(row, 3, item3.release());

    std::unique_ptr<QTableWidgetItem> item4(new QTableWidgetItem(mytimer.getCurrentTime()));
    item4->setTextAlignment(Qt::AlignCenter);
    ui.tableWidget->setItem(row, 4, item4.release());

    qDebug() << "Damaged QR code detected.";
}
void QRCode::resetAllButtons() {
    // ��ȡ������ť��ָ��
    QPushButton *buttons[3] = {ui.yunting, ui.baiyun, ui.bishui};

    // ����ÿ����ť�������߶ȸ�ԭΪĬ�ϵ� 60
    for (int i = 0; i < 3; i++) {
        buttons[i]->setFixedHeight(60);
    }
}

void QRCode::adjustButtonHeight(QPushButton *selectedButton) {
    // ���尴ť�ĸ߶�
    const int selectedHeight = 90;
    const int defaultHeight = 60;

    // ���谴ť��ָ���ֱ��� ui.yuntingButton, ui.baiyunButton, ui.bishuiButton
    QPushButton *buttons[] = {ui.yunting, ui.baiyun, ui.bishui};

    // ������ť���飬���ø߶�
    for (QPushButton *button : buttons) {
        if (button == selectedButton) {
            button->setFixedHeight(selectedHeight); // ���ô��밴ť�ĸ߶�
        } else {
            button->setFixedHeight(defaultHeight);  // ������ť�ĸ߶�
        }
    }
}
void QRCode::processFrame(const cv::Mat &frame)
{
    // ֱ�ӻ�ȡ֡�Ŀ�¡
    cv::Mat frameWithLines = frame.clone();

    if (!isProcessing) { // �����Ƿ����ڴ���
            isProcessing = true; // ���ñ�־Ϊ true

            MyWork *decoderThread = new MyWork(frameWithLines);
            // �� decoderThread ����Ϊ QRCode ���Ӷ������Ա��Զ������ڴ�
            decoderThread->setParent(this);

            // �����ź�����
            connect(decoderThread, &MyWork::decoded, this, &QRCode::handleDecoded);
            connect(decoderThread, &QThread::finished, this, [this]() {
                isProcessing = false; // ���ô���״̬Ϊ false
            });

            // �����߳�
            decoderThread->start();
    }
    // ���� points ���������������� 4 ���㣬�����ƶ�ά���߿�
    QMutex mutex;
    mutex.lock();
    if (lastPoints.size() >= 4) {
        for (size_t i = 0; i < lastPoints.size(); i++) {
            cv::line(frameWithLines, lastPoints[i], lastPoints[(i + 1) % lastPoints.size()], cv::Scalar(0, 255, 0), 3);
        }
        lastPoints.clear();  // ����lastPoints
    }
    mutex.unlock();

    // ��ʾ��������֡
    QPixmap qpixmap = camera->Mat2QImage(frameWithLines);
    camera->getCameraLabel()->setPixmap(qpixmap);
}


void QRCode::handleDecoded(const std::string &decodedText, const std::vector<cv::Point> &points)
{

    static int i;
    i++;
    qDebug()<<i;
  this->lastPoints = points;
    if (decodedText == lastDecodedText) {

        return;
    }



    this->lastDecodedText = decodedText;

    // ���к�������
    if (!decodedText.empty()) {
        // �ָ��ַ���
        QStringList parts = QString::fromStdString(lastDecodedText).split("-");
        if (parts.size() == 3 || parts.size() == 4) {
            if (parts.size() == 4) {
                MainWindow::sharedSerial->sendData("delicate");
            }

            // ���� UI
            int row = ui.tableWidget->rowCount();
            ui.tableWidget->insertRow(row);
            ui.tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(currentIndex++)));
            ui.tableWidget->setItem(row, 1, new QTableWidgetItem(parts[0]));
            ui.tableWidget->setItem(row, 2, new QTableWidgetItem(parts[1]));
            ui.tableWidget->setItem(row, 3, new QTableWidgetItem(parts[2]));
            ui.tableWidget->setItem(row, 4, new QTableWidgetItem(mytimer.getCurrentTime()));
        }

        // ���ݲ�ͬ��������������
        if (MainWindow::sharedSerial) {
            if(currentMode==classification){
                if (parts[1] == QStringLiteral("云庭市")) {
                    MainWindow::sharedSerial->sendDataPacket("1", MySerial::PacketType::Data);
                } else if (parts[1] == QStringLiteral("碧水市")) {
                    MainWindow::sharedSerial->sendDataPacket("2", MySerial::PacketType::Data);
                } else if (parts[1] == QStringLiteral("青山市")) {
                    MainWindow::sharedSerial->sendDataPacket("3", MySerial::PacketType::Data);
                }
            }else{
                if (variable == yunting) {
                           // ֻ���� "��ͥ��" �ŷ������ݰ�
                           if (parts[1] == QStringLiteral("云庭市")) {
                               MainWindow::sharedSerial->sendDataPacket("1", MySerial::PacketType::Data);
                           }else{
                                MainWindow::sharedSerial->sendDataPacket("0", MySerial::PacketType::Data);
                           }
                } else if (variable == bishui) {
                           // ֻ���� "��ˮ��" �ŷ������ݰ�
                           if (parts[1] == QStringLiteral("碧水市")) {
                               MainWindow::sharedSerial->sendDataPacket("2", MySerial::PacketType::Data);
                           }else{
                               MainWindow::sharedSerial->sendDataPacket("0", MySerial::PacketType::Data);
                          }
                 } else if (variable == baiyun) {
                           // ֻ���� "������" �ŷ������ݰ�
                           if (parts[1] == QStringLiteral("青山市")) {//青山市
                               MainWindow::sharedSerial->sendDataPacket("3", MySerial::PacketType::Data);
                            }else{
                               MainWindow::sharedSerial->sendDataPacket("0", MySerial::PacketType::Data);
                          }
                }
            }
        }
    }

    // ����������һ��
    ui.tableWidget->scrollToBottom();
}

void QRCode::on_exButton_Pressed()
{
    btn = std::make_unique<BtnEffect>(ui.exButton);
    btn->zoom1();

}
void QRCode::on_exButton_Release()
{
    MainWindow::sharedSerial->sendDataPacket("exit",MySerial::PacketType::Command);
    exitMode();
}

void QRCode::on_slowButton_pressed()
{
    btn = std::make_unique<BtnEffect>(ui.slowButton);
    btn->zoom1();
}

void QRCode::on_slowButton_released()
{
    if (btn) {
                QEventLoop loop;
                connect(btn->getAnimation(), &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
                btn->zoom2();
                loop.exec();
                btn.reset();
            }
       MainWindow::sharedSerial->sendDataPacket("sorte",MySerial::PacketType::Command);
       this->currentMode=classification;
       for(int i=0;i<130;i++)
        ui.tableWidget->setFixedHeight(430+i);
       animateWidget2Hide();

}
void QRCode::on_fastButton_pressed()
{
    btn = std::make_unique<BtnEffect>(ui.fastButton);
    btn->zoom1();
}

void QRCode::on_fastButton_released()
{
    if (btn) {
                QEventLoop loop;
                connect(btn->getAnimation(), &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
                btn->zoom2();
                loop.exec();
                btn.reset();
            }
       MainWindow::sharedSerial->sendDataPacket("appoint",MySerial::PacketType::Command);
       this->currentMode=appoint;
       this->variable=yunting;
       for(int i=0;i<130;i++)
        ui.tableWidget->setFixedHeight(560-i);
       animateWidget2Show();
       resetAllButtons();

}




void QRCode::on_yunting_clicked()
{
    btn = std::make_unique<BtnEffect>(ui.yunting);
    btn->zoom1();
    if (btn) {
                QEventLoop loop;
                connect(btn->getAnimation(), &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
                btn->zoom2();
                loop.exec();
                btn.reset();
            }
   this->variable=yunting;
    MainWindow::sharedSerial->sendDataPacket("yunting",MySerial::PacketType::Command);
    adjustButtonHeight(ui.yunting);
}


void QRCode::on_bishui_clicked()
{
    btn = std::make_unique<BtnEffect>(ui.bishui);
    btn->zoom1();
    if(btn){
        QEventLoop loop;
        connect(btn->getAnimation(),&QPropertyAnimation::finished,&loop,&QEventLoop::quit);
        btn->zoom2();
        loop.exec();
        btn.reset();
    }
    this->variable=bishui;
     MainWindow::sharedSerial->sendDataPacket("bishui",MySerial::PacketType::Command);
    adjustButtonHeight(ui.bishui);
}
void  QRCode::on_baiyun_clicked(){

    btn = std::make_unique<BtnEffect>(ui.baiyun);
    btn->zoom1();
    if(btn){
        QEventLoop loop;
        connect(btn->getAnimation(),&QPropertyAnimation::finished,&loop,&QEventLoop::quit);
        btn->zoom2();
        loop.exec();
        btn.reset();
    }
    this->variable=baiyun;
     MainWindow::sharedSerial->sendDataPacket("baiyun",MySerial::PacketType::Command);//青山市
    adjustButtonHeight(ui.baiyun);

}

void QRCode::animateWidget2Show() {
    // ���� widget2 ��͸��Ч��
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(ui.widget2);
    ui.widget2->setGraphicsEffect(opacityEffect);

    // �������붯��
    QPropertyAnimation *fadeIn = new QPropertyAnimation(opacityEffect, "opacity");
    fadeIn->setDuration(500);  // 500 ����
    fadeIn->setStartValue(0);  // ��͸����ʼ
    fadeIn->setEndValue(1);    // ��Ϊ��ȫ�ɼ�

    // ��ʾ widget2
    ui.widget2->show();

    // �������붯��
    fadeIn->start();
}
void QRCode::animateWidget2Hide() {
    // ���� widget2 ��͸��Ч��
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(ui.widget2);
    ui.widget2->setGraphicsEffect(opacityEffect);

    // ������������
    QPropertyAnimation *fadeOut = new QPropertyAnimation(opacityEffect, "opacity");
    fadeOut->setDuration(500);  // 500 ����
    fadeOut->setStartValue(1);
    fadeOut->setEndValue(0);

    // ���Ӷ��������ź������� widget2
    connect(fadeOut, &QPropertyAnimation::finished, this, [this]() {
        ui.widget2->hide();
    });

    // ������������
    fadeOut->start();
}
