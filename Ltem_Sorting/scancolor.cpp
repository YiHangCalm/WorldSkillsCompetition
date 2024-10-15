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
        // Ensure QObject::connect is successful
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
        camera->stop();  // Stop the camera
        camera.reset();  // Release camera resources
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
    cv::cvtColor(frame, frameHSV, cv::COLOR_BGR2HSV);  // Convert frame to HSV color space
   QPixmap hsvPixmap = camera->Mat2QImage(frameHSV);
    if (ui.HSV) {
            ui.HSV->setPixmap(hsvPixmap);
        }
    cv::Mat grayImage;
   cv::cvtColor(frame, grayImage, cv::COLOR_BGR2GRAY);  // ��ԭͼת��Ϊ�Ҷ�ͼ��
   cv::Mat binaryImage;
   cv::threshold(grayImage, binaryImage, 100, 255, cv::THRESH_BINARY);
   QPixmap binaryPixmap = camera->Mat2QImage(binaryImage);
   if (ui.bin) {
       ui.bin->setPixmap(binaryPixmap);
   }
    // Define color ranges for red, blue, and yellow
    std::vector<std::pair<cv::Scalar, cv::Scalar>> colorRanges = {
     {cv::Scalar(0, 240, 240), cv::Scalar(10, 255, 255)},     // New color (Bright Red)
        {cv::Scalar(35, 100, 100), cv::Scalar(85, 255, 255)},    // Green
        {cv::Scalar(100, 100, 100), cv::Scalar(130, 255, 255)}   // Blue

    };

    std::vector<std::string> colorNames = {"Red", "Blue", "Yellow"};

    cv::Mat result = frame.clone();
    bool colorDetected = false;
    std::string detectedColor;

    static std::string previousDetectedColor = ""; // Store previously detected color

    // Iterate through each color range
    for (size_t i = 0; i < colorRanges.size(); ++i) {
        cv::Mat mask;
        cv::inRange(frameHSV, colorRanges[i].first, colorRanges[i].second, mask);  // Filter color

        // Dilate to strengthen the detected color region
        cv::Mat dilatedMask;
        cv::dilate(mask, dilatedMask, cv::Mat(), cv::Point(-1, -1), 2);

        // Find contours
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(dilatedMask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        for (const auto &contour : contours) {
            double area = cv::contourArea(contour);
            if (area < 1000) {
                continue;  // Ignore small areas
            }

            // Draw bounding box
            cv::Rect boundingRect = cv::boundingRect(contour);
            cv::rectangle(result, boundingRect, cv::Scalar(0, 255, 0), 2);

            detectedColor = colorNames[i];
            if (detectedColor == previousDetectedColor) {
                return;  // Ignore if the detected color is the same as the previous one
            }

            colorDetected = true;
            previousDetectedColor = detectedColor;
        }
    }

    // Display detected color information
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

void ScanColor::on_adjust_pressed()
{
    btn = std::make_unique<BtnEffect>(ui.adjust);
    btn->zoom1();
}


void ScanColor::on_adjust_released()
{
    if (btn) {
                QEventLoop loop;
                connect(btn->getAnimation(), &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
                btn->zoom2();
                loop.exec();
                btn.reset();
            }
}

