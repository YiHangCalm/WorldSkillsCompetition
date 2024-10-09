#include "scancolor.h"
#include <QDebug>
#include <QPainter>

ScanColor::ScanColor(QWidget *parent)
    : QMainWindow(parent), camera(nullptr)
{
    ui.setupUi(this);
    this->showFullScreen();
}

void ScanColor::enterMode(QWidget *parentWidget)
{
    if (!camera) {
        camera = std::make_unique<ExternalCamera>(this);
        camera->start();

        // ���� QLabel �ĳߴ���ƥ������ͷ�ķֱ���
        camera->getCameraLabel()->setGeometry(0, 0, 640, 480);
        camera->getCameraLabel()->show();
    }

    this->execute();
}

void ScanColor::execute()
{
    if (!camera) return;

    if (!signalConnected) {
        // ʹ�� QObject::connect ȷ���ź�������ȷ
        if (QObject::connect(camera.get(), &ExternalCamera::frameReady, this, &ScanColor::processFrame)) {
            signalConnected = true;
        } else {
            qDebug() << "Failed to connect camera signal to processFrame";
        }
    }
}

void ScanColor::exitMode()
{
    if (camera) {
        camera->stop();  // ֹͣ����ͷ
        camera.reset();  // �ͷ�����ͷ��Դ
    }

    if (parentWidget()) {
        parentWidget()->show();
    }

    this->hide();
}

void ScanColor::show()
{
    QMainWindow::show();
}

void ScanColor::processFrame(const cv::Mat &frame)
{
    cv::Mat frameHSV;
    cv::cvtColor(frame, frameHSV, cv::COLOR_BGR2HSV);  // ��ͼ��ת��Ϊ HSV ��ɫ�ռ�

    // ������ɫ�ķ�Χ�����ڼ�����ɫ
    cv::Scalar lowerRed(0, 100, 100);
    cv::Scalar upperRed(10, 200, 200);

    // ������ɫ����
    cv::Mat mask;
    cv::inRange(frameHSV, lowerRed, upperRed, mask);

    // ���Ͳ���
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::dilate(mask, mask, kernel, cv::Point(-1, -1), 1);

    // Ѱ������
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    bool colorDetected = false;
    cv::Mat result = frame.clone();

    for (const auto &contour : contours) {
        double area = cv::contourArea(contour);
        if (area < 200) {
            continue;  // ����С�� 200 ���ص�����
        }

        // ���ƾ��ο�
        cv::Rect boundingRect = cv::boundingRect(contour);
        cv::rectangle(result, boundingRect, cv::Scalar(0, 0, 255), 2);

        colorDetected = true;
    }

    // ��ʾ���⵽����ɫ��Ϣ
    if (colorDetected && ui.informationEdit) {
        ui.informationEdit->append("Color detected: Red");
    }

    QPixmap qpixmap = camera->Mat2QImage(result);
    camera->getCameraLabel()->setPixmap(qpixmap);
}

void ScanColor::on_exitButton_clicked()
{
    exitMode();
}
