#include "qrcode.h"
#include <QDebug>

QRCode::QRCode(QWidget *parent)
    : QMainWindow(parent), camera(nullptr), lastDecodedText("")
{
    ui.setupUi(this);
    this->showFullScreen();

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
    ui.tableWidget->setColumnWidth(3, 130);
    ui.tableWidget->setColumnWidth(4, 200);
    connect(ui.exButton, &QPushButton::pressed, this, &QRCode::on_exButton_Release);
    connect(ui.exButton, &QPushButton::released, this, &QRCode::on_exButton_Pressed);
    connect(ui.exButton, &QPushButton::released, this, &QRCode::on_exButton_Pressed);
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
    this->raise(); // ȷ��������ǰ̨��ʾ
    this->activateWindow(); // �����
}

void QRCode::processFrame(const cv::Mat &frame)
{
    try {
        cv::Mat frameWithLines = frame.clone();

        std::string decodedText = this->qrDecoder.detectAndDecode(frameWithLines, this->points);

        if (!decodedText.empty() && decodedText != lastDecodedText) {
            lastDecodedText = decodedText;

            QStringList parts = QString::fromStdString(decodedText).split("-");
            if (parts.size() == 3) {
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
    btn = std::make_unique<BtnEffect>(ui.exButton);
    btn->zoom1();

}
void QRCode::on_exButton_Release()
{

    exitMode();
}
