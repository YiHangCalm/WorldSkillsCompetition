#include "camera.h"

ExternalCamera::ExternalCamera(QWidget *parent)
    : QObject(parent), timer(new QTimer(this)), fpsTimer(new QElapsedTimer), frameCount(0), fps(0.0)
{
    // ��ʼ�� QLabel ����ʾ����ͷ�Ļ���
    cameraLabel = new QLabel(parent);
    cameraLabel->setGeometry(711, 0, 320, 240);  // ���� QLabel �Ĵ�СΪ 320x240
    cameraLabel->setStyleSheet("border: 2px solid white;");  // ʹ����ʽ�����ñ߿���ɫ������
    cameraLabel->show();

    // ���Ӷ�ʱ����ʱ�źŵ� display �ۺ���
    connect(timer, &QTimer::timeout, this, &ExternalCamera::display);
}

void ExternalCamera::start()
{
    // ��������ͷ
    videocapture.open(0);
    if (videocapture.isOpened()) {
        // ��������ͷ�ֱ���
        videocapture.set(cv::CAP_PROP_FRAME_WIDTH, 320);
        videocapture.set(cv::CAP_PROP_FRAME_HEIGHT, 240);

        // ��������֡��
        videocapture.set(cv::CAP_PROP_FPS, 90); // ��������֡��Ϊ90

        // ������ʱ��
        fpsTimer->start();
        timer->start(11);  // ÿ11��������һ�Σ��ӽ�90 FPS
    }
}


void ExternalCamera::stop()
{
    if (timer->isActive()) {
        timer->stop();  // ֹͣ��ʱ��
    }

    if (videocapture.isOpened()) {
        videocapture.release();  // �ͷ�����ͷ��Դ
    }

    cameraLabel->clear();  // ���� QLabel ������
    cameraLabel->hide();   // ���� QLabel
}

void ExternalCamera::display()
{
    static bool isProcessing = false;

    if (isProcessing) {
        return;
    }

    isProcessing = true;

    if (!videocapture.isOpened()) {
        isProcessing = false;
        return;
    }

    frameCount++;

    if (fpsTimer->elapsed() > 1000) {
        fps = frameCount / (fpsTimer->elapsed() / 1000.0);
        frameCount = 0;
        fpsTimer->restart();
    }

    videocapture.read(frame);
    if (frame.empty()) {
        isProcessing = false;
        return;
    }

    // ��֡����ʾ FPS ��Ϣ
    std::string fpsText = "FPS: " + std::to_string(static_cast<int>(fps));
    cv::putText(frame, fpsText, cv::Point(10, 20), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 1);

    // ��֡ת��Ϊ QPixmap ����ʾ�� QLabel ��
    QPixmap qpixmap = Mat2QImage(frame);
    cameraLabel->setPixmap(qpixmap);

    emit frameReady(frame);

    isProcessing = false;
}

QPixmap ExternalCamera::Mat2QImage(const cv::Mat &src)
{
    QImage img;
    cv::Mat tmp;

    if (src.channels() == 3) {
        cv::cvtColor(src, tmp, cv::COLOR_BGR2RGB);
        img = QImage((const unsigned char*)(tmp.data), tmp.cols, tmp.rows, tmp.step, QImage::Format_RGB888);
    } else {
        img = QImage((const unsigned char*)(src.data), src.cols, src.rows, src.step, QImage::Format_Grayscale8);
    }

    return QPixmap::fromImage(img);
}

QLabel* ExternalCamera::getCameraLabel()
{
    return cameraLabel;
}


