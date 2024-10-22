#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <QImage>
#include <QPixmap>
#include <QTableWidget> // ȷ������ QTableWidget
#include <QHeaderView>  // ȷ������ QHeaderView
#include <QTime>
#include <opencv2/opencv.hpp>
#include "mywork.h"
#include  <QThread>
#include <QMutex>
#include <QMutexLocker>
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateFrame();
signals:
   void work_sig(const QImage &image);

private:
    cv::VideoCapture cap;  // OpenCV ����ͷ����
    QTimer *timer;
    QLabel *fpsLabel;
    QLabel *imageLabel; // ������ʾ��Ƶ֡�� QLabel
    int frameCount;
    QTime timerFPS;
    QMutex mutex;
     MyWork *work;
    QThread *t1;
    cv::QRCodeDetector qrDecoder;  // ���� QRCodeDetector ����
    // ���� QTableWidget ��Ϊ��Ա
        QTableWidget *tableWidget;
        int i;
};

#endif // MAINWINDOW_H
