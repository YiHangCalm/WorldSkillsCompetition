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
        camera.reset(); // �ͷ�������Դ
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

    // �����½������ı�Ϊ�ջ��ߺ��ϴν�����һ��������������
//        if (decodedText.empty() || decodedText == lastDecodedText) {
//            return;
//        }

//        // �����ϴν������ı�
//        lastDecodedText = decodedText;



    if (!decodedText.empty() && this->points.size() == 4) {
        for (int i = 0; i < 4; i++) {
            cv::line(frameWithLines, this->points[i], this->points[(i + 1) % 4], cv::Scalar(0, 0, 255), 3);
        }

        if (ui.informationEdit) {
            ui.informationEdit->append(QString::fromStdString(decodedText));
        }
    }

    QPixmap qpixmap = camera->Mat2QImage(frameWithLines);
    camera->getCameraLabel()->setPixmap(qpixmap);
}

void QRCode::on_pushButton_clicked()
{
    exitMode();
}
