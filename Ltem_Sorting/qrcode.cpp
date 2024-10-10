#include "qrcode.h"
#include <QDebug>

QRCode::QRCode(QWidget *parent)
    : QMainWindow(parent), camera(nullptr), lastDecodedText("")
{

    ui.setupUi(this);
    this->showFullScreen();
}

void QRCode::enterMode(QWidget *parentWidget)
{
    if (!camera) {
        camera = std::make_unique<ExternalCamera>(this);
        camera->start();
    }

    this->execute();
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
        camera->stop(); // ֹͣ����ͷ
        camera.reset(); // �ͷ�����ͷ��Դ
    }

    if (parentWidget()) {
        parentWidget()->show();
    }

    this->hide();
}

void QRCode::show()
{
    QMainWindow::show();
}

void QRCode::processFrame(const cv::Mat &frame)
{
    cv::Mat frameWithLines = frame.clone();

    std::string decodedText = this->qrDecoder.detectAndDecode(frameWithLines, this->points);

    // �����ɹ������ݲ�ͬ���ϴν���������
    if (!decodedText.empty() && decodedText != lastDecodedText) {
        lastDecodedText = decodedText;

        // �ָ��������ı�����
        QStringList parts = QString::fromStdString(decodedText).split("-");
        if (parts.size() == 3) {
            int row = ui.tableWidget->rowCount();
            ui.tableWidget->insertRow(row);

            ui.tableWidget->setItem(row, 0, new QTableWidgetItem(parts[0]));
            ui.tableWidget->setItem(row, 1, new QTableWidgetItem(parts[1]));
            ui.tableWidget->setItem(row, 2, new QTableWidgetItem(parts[2]));
        }
    }

    QPixmap qpixmap = camera->Mat2QImage(frameWithLines);
    camera->getCameraLabel()->setPixmap(qpixmap);
}

void QRCode::on_pushButton_clicked()
{
    exitMode();
}
