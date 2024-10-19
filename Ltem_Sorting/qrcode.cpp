#include "qrcode.h"
#include <QDebug>
#include <QMutex>
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
            if (parts[1] == QStringLiteral("云庭市")) {
                MainWindow::sharedSerial->sendDataPacket("1", MySerial::PacketType::Data);
            } else if (parts[1] == QStringLiteral("碧水市")) {
                MainWindow::sharedSerial->sendDataPacket("2", MySerial::PacketType::Data);
            } else if (parts[1] == QStringLiteral("白云市")) {
                MainWindow::sharedSerial->sendDataPacket("3", MySerial::PacketType::Data);
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
       MainWindow::sharedSerial->sendDataPacket("slow",MySerial::PacketType::Command);
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
       MainWindow::sharedSerial->sendDataPacket("fast",MySerial::PacketType::Command);
}



