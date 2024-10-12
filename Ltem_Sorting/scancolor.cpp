#include "scancolor.h"
#include <QDebug>
#include <QPainter>

ScanColor::ScanColor(QWidget *parent)
    : QMainWindow(parent), camera(nullptr)
{
    ui.setupUi(this);
    this->showFullScreen();
    connect(ui.exButton, &QPushButton::clicked, this, &ScanColor::on_exitBtn_clicked);
}

void ScanColor::enterMode(QWidget *parentWidget)
{
    if (!camera) {
        camera = std::make_unique<ExternalCamera>(this);
        camera->start();

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

    // ������ɫ��Χ�����ڼ�����ɫ����ɫ����ɫ
    std::vector<std::pair<cv::Scalar, cv::Scalar>> colorRanges = {
        {cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255)},     // ��ɫ
        {cv::Scalar(100, 150, 0), cv::Scalar(140, 255, 255)},    // ��ɫ
        {cv::Scalar(20, 100, 100), cv::Scalar(30, 255, 255)}     // ��ɫ
    };

    std::vector<std::string> colorNames = {"Red", "Blue", "Yellow"};

    cv::Mat result = frame.clone();
    bool colorDetected = false;
    std::string detectedColor;

    // ѭ������ÿ����ɫ��Χ
    for (size_t i = 0; i < colorRanges.size(); ++i) {
        cv::Mat mask;
        cv::inRange(frameHSV, colorRanges[i].first, colorRanges[i].second, mask);  // ������ɫ����

        // ���Ͳ�������ǿɫ������
        cv::Mat dilatedMask;
        cv::dilate(mask, dilatedMask, cv::Mat(), cv::Point(-1, -1), 2);

        // Ѱ������
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(dilatedMask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        for (const auto &contour : contours) {
            double area = cv::contourArea(contour);
            if (area < 1000) {
                continue;  // ����С�� 200 ���ص�����
            }

            // ���ƾ��ο�
            cv::Rect boundingRect = cv::boundingRect(contour);
            cv::rectangle(result, boundingRect, cv::Scalar(0, 255, 0), 2);

            colorDetected = true;
            detectedColor = colorNames[i];
        }
    }

    // ��ʾ���⵽����ɫ��Ϣ
    if (colorDetected && ui.informationEdit) {
        ui.informationEdit->append(QString("Color detected: %1").arg(QString::fromStdString(detectedColor)));
    }

    QPixmap qpixmap = camera->Mat2QImage(result);
    camera->getCameraLabel()->setPixmap(qpixmap);
}
void ScanColor::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        if (isFullScreen()) {
            showNormal();
        } else {
            showFullScreen();
        }
    }
}

void ScanColor::on_exitBtn_clicked()
{
    exitMode();
}
