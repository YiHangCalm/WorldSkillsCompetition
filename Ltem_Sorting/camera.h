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
    QLabel* getCameraLabel();  // ����������������ȡ QLabe
signals:
    void frameReady(const cv::Mat &frame); // �źţ����ڴ��ݲ�����֡
public  slots:
    void display(); // �ۺ�����������ʾ����֡
private:
    QTimer *timer;
    cv::VideoCapture videocapture;
    cv::Mat frame;
    QElapsedTimer *fpsTimer;
    int frameCount;
    double fps;
    QLabel *cameraLabel;

};

#endif // CAMERA_H
