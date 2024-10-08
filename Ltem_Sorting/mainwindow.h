#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QTimer>
#include <QPixmap>
#include <QElapsedTimer> // For FPS calculation
#include <QDebug>
#include <opencv2/opencv.hpp>
// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp> // ���� QRCodeDetector

using namespace cv;
QPixmap Mat2QImage(Mat src);

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked(); // ������ť�����¼�
    void readFrame();             // ��ȡÿ֡
    QPixmap Mat2QImage(const cv::Mat &src); // ��cv::Matת��ΪQPixmap

private:
    Ui::MainWindow *ui;          // UIָ��
    QTimer *timer;               // ��ʱ��
    QImage *img;                 // ͼ��ָ��
    VideoCapture *videocapture;  // ��Ƶ��׽ָ��
    Mat matFrame, dst;       // OpenCV Mat����

    // FPS���ر���
    QElapsedTimer *fpsTimer;     // ���ڲ���ʱ�������ļ�ʱ��
    int frameCount;              // ���ڼ���FPS��֡����
    double fps;                  // �洢FPS�ı���

    // QR Code��������
    cv::QRCodeDetector qrDecoder; // QR Code������
    QString qrData;               // ʹ��QString���洢��������
};

#endif // MAINWINDOW_H
