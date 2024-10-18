#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QTimer>
#include <QWidget>
#include <QLabel>
#include <QElapsedTimer>
#include <opencv2/opencv.hpp>
#include <QTextEdit>

class ExternalCamera : public QObject
{
    Q_OBJECT

public:
    ExternalCamera(QWidget *parent = nullptr);
    void start();
    void stop();
    QPixmap Mat2QImage(const cv::Mat &src);
    QLabel* getCameraLabel();

signals:
    void frameReady(const cv::Mat &frame);

public slots:
    void display();

private:
    QTimer *timer;
    cv::VideoCapture videocapture;
    cv::Mat frame;
    QElapsedTimer *fpsTimer;
    int frameCount;
    double fps;
    QLabel *cameraLabel;
    bool isProcessing;  // ���� isProcessing ����
};

#endif // CAMERA_H
