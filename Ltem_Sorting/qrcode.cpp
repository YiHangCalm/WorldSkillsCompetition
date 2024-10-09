#include "qrcode.h"
#include <QDebug>
QRCode::QRCode(QWidget *parent)
    : QMainWindow(parent), camera(nullptr)
{
    ui.setupUi(this);  // ��ʼ�� UI���� qrcode.ui �еĿؼ����ӵ���ǰ QMainWindow ʵ����
}

void QRCode::enterMode(QWidget *parentWidget)
{
    // ��ʼ������
    if (!camera) {
        camera = new ExternalCamera(this);
        camera->start();
    }
    this->execute();
}

void QRCode::execute()
{
    if (!camera) return;

    // ȷ��ֻ����һ������
    if (!QObject::connect(camera, &ExternalCamera::frameReady, this, [this](const cv::Mat &frame) {
        processFrame(frame);
    })) {
        qDebug() << "Failed to connect camera signal to processFrame";
    }
}

void QRCode::exitMode()
{
    if (camera) {
        delete camera;
        camera = nullptr;
    }


    if (parentWidget()) {
        parentWidget()->show();
    }
    this->hide();
}

void QRCode::show()
{
    QMainWindow::show();  // ���ø��� QMainWindow �� show ����
}

void QRCode::processFrame(const cv::Mat &frame)
{
    // ��¡��ǰ֡���ڻ��ƶ�ά���߿�
    cv::Mat frameWithLines = frame.clone();

    // ���Ⲣ������ά��
    std::string decodedText = this->qrDecoder.detectAndDecode(frameWithLines, this->points);

    if (!decodedText.empty() && this->points.size() == 4) {
        // �ڶ�ά����Ե����
        for (int i = 0; i < 4; i++) {
            cv::line(frameWithLines, this->points[i], this->points[(i + 1) % 4], cv::Scalar(0, 0, 255), 3);
        }

        // ��ʾ���������ı���Ϣ�� QTextEdit �ؼ�
        if (ui.informationEdit) {
            ui.informationEdit->append(QString::fromStdString(decodedText));
        }
    }

    // �����ƺ���֡��ʾ�� QLabel ��
    QPixmap qpixmap = camera->Mat2QImage(frameWithLines);
    camera->getCameraLabel()->setPixmap(qpixmap);
}
