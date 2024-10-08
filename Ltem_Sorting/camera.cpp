#include "camera.h"

ExternalCamera::ExternalCamera(QWidget *parent) : QObject(parent), timer(new QTimer(this)), fpsTimer(new QElapsedTimer), frameCount(0), fps(0.0)
{
    // ����һ�� QLabel��λ��Ϊ (0, 0)����СΪ 640x480
    cameraLabel = new QLabel(parent);
    cameraLabel->setGeometry(0, 0, 320, 240);
    cameraLabel->show();

    // ���Ӷ�ʱ���ĳ�ʱ�źŵ� display �ۺ���
    connect(timer, &QTimer::timeout, this, &ExternalCamera::display);
}
void ExternalCamera::start()
{
    videocapture.open(0);
    if (videocapture.isOpened()) {
        videocapture.set(cv::CAP_PROP_FRAME_WIDTH, 320);
        videocapture.set(cv::CAP_PROP_FRAME_HEIGHT, 240);
        fpsTimer->start();
        timer->start(33);  // Capture approximately 30 FPS
    }
}

void ExternalCamera::display()
{
    // ��������ͷ�Ƿ��Ѵ���
    if (!videocapture.isOpened()) {
        return;
    }

    // ����֡����
    frameCount++;

    // ���� FPS ÿ������һ��
    if (fpsTimer->elapsed() > 1000) {
        fps = frameCount / (fpsTimer->elapsed() / 1000.0);
        frameCount = 0;
        fpsTimer->restart();
    }

    // ������ͷ��ȡһ֡
    videocapture.read(frame);
    if (frame.empty()) {
        return;
    }

    // ��֡����Ϣ���Ƶ�֡�����Ͻ�
    std::string fpsText = "FPS: " + std::to_string(static_cast<int>(fps));
    cv::putText(frame, fpsText, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 0.5);

    // ��֡ת��Ϊ QPixmap ��ʾ�� QLabel ��
    QPixmap qpixmap = Mat2QImage(frame);
    cameraLabel->setPixmap(qpixmap);

    // �����ź�֪ͨ֡��׼����
    emit frameReady(frame);
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

QLabel* ExternalCamera::getCameraLabel() {
    return cameraLabel;
}
