#include "qrcode.h"
#include <QDebug>

QRCode::QRCode(QWidget *parent)
    : QMainWindow(parent), camera(nullptr), lastDecodedText("")
{
    ui.setupUi(this);
    this->showFullScreen();
    ui.tableWidget->verticalHeader()->setVisible(false); // ������ͷ�����ţ�

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

    ui.tableWidget->setColumnWidth(0, 120);
    ui.tableWidget->setColumnWidth(1, 130);
    ui.tableWidget->setColumnWidth(2, 130);
    ui.tableWidget->setColumnWidth(3, 160);
    ui.tableWidget->setColumnWidth(4, 170);
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
void QRCode::processFrame(const cv::Mat &frame)
{
    try {
        cv::Mat frameWithLines = frame.clone();

        std::string decodedText = this->qrDecoder.detectAndDecode(frameWithLines, this->points);
        if (points.size() < 4 && !decodedText.empty()) {
                   checkDamagedQRCode();
                   return;
               }

        if (!decodedText.empty() && decodedText != lastDecodedText) {
            lastDecodedText = decodedText;

            QStringList parts = QString::fromStdString(decodedText).split("-");
            if (parts.size() == 3||parts.size() == 4) {
                if(parts.size() == 4){
                     MainWindow::sharedSerial->sendData("2");
                }
                int row = ui.tableWidget->rowCount();
                ui.tableWidget->insertRow(row);

                std::unique_ptr<QTableWidgetItem> item0(new QTableWidgetItem(QString::number(currentIndex++)));
                item0->setTextAlignment(Qt::AlignCenter);
                ui.tableWidget->setItem(row, 0, item0.release());

                std::unique_ptr<QTableWidgetItem> item1(new QTableWidgetItem(parts[0]));
                item1->setTextAlignment(Qt::AlignCenter);
                ui.tableWidget->setItem(row, 1, item1.release());

                std::unique_ptr<QTableWidgetItem> item2(new QTableWidgetItem(parts[1]));
                item2->setTextAlignment(Qt::AlignCenter);
                ui.tableWidget->setItem(row, 2, item2.release());

                std::unique_ptr<QTableWidgetItem> item3(new QTableWidgetItem(parts[2]));
                item3->setTextAlignment(Qt::AlignCenter);
                ui.tableWidget->setItem(row, 3, item3.release());

                std::unique_ptr<QTableWidgetItem> item4(new QTableWidgetItem(mytimer.getCurrentTime()));
                item4->setTextAlignment(Qt::AlignCenter);
                ui.tableWidget->setItem(row, 4, item4.release());
            }
            if (MainWindow::sharedSerial) {
                // ȷ���ַ�������ȷ�Ƚ�
                if (parts[2] == QStringLiteral("云庭市")) {
                    MainWindow::sharedSerial->sendDataPacket("1");
                    qDebug() << "Data sent to serial port: 1";
                }else if(parts[2] == QStringLiteral("碧水市")) {
                    MainWindow::sharedSerial->sendDataPacket("2");
                    qDebug() << "Data sent to serial port: 2";
                }else  {
                    MainWindow::sharedSerial->sendDataPacket("3");
                    qDebug() << "Data sent to serial port: 3";

                }
            }

        }

        ui.tableWidget->scrollToBottom();
        QPixmap qpixmap = camera->Mat2QImage(frameWithLines);
        camera->getCameraLabel()->setPixmap(qpixmap);
    } catch (const std::exception &e) {
        QFile logFile("application.log");
        if (logFile.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&logFile);
            out << mytimer.getCurrentTime() << " - Exception caught in processFrame: " << e.what() << "\n";
        }
        logFile.close();
        qDebug() << "Exception caught in processFrame: " << e.what();
    } catch (...) {
        QFile logFile("application.log");
        if (logFile.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&logFile);
            out << mytimer.getCurrentTime() << " - Unknown exception caught in processFrame\n";
        }
        logFile.close();
        qDebug() << "Unknown exception caught in processFrame";
    }
}
void QRCode::on_exButton_Pressed()
{
//    btn = std::make_unique<BtnEffect>(ui.exButton);
//    btn->zoom1();

}
void QRCode::on_exButton_Release()
{

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
       MainWindow::sharedSerial->sendDataPacket("flow");
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
       MainWindow::sharedSerial->sendDataPacket("fast");
}



