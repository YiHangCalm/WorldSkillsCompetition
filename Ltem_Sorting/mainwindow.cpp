#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp> // ������ά������������
using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    img = new QImage();
    videocapture = new VideoCapture();

    // Initialize FPS timer
    fpsTimer = new QElapsedTimer();
    fpsTimer->start();

    // Set frame count to 0
    frameCount = 0;

    connect(timer, &QTimer::timeout, this, &MainWindow::readFrame);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (videocapture) {
        videocapture->release();
        delete videocapture;
    }
}

void MainWindow::on_pushButton_clicked()
{
    timer->start(33); // Start timer (30 FPS ~ 33ms per frame)
    videocapture->open(0); // Open default camera

    if (videocapture->isOpened()) {
        videocapture->set(cv::CAP_PROP_FRAME_WIDTH, 640);
        videocapture->set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    }
}

void MainWindow::readFrame()
{
    if (!videocapture->isOpened()) {
        return;
    }

    frameCount++;

    if (fpsTimer->elapsed() > 1000) {
        fps = frameCount / (fpsTimer->elapsed() / 1000.0);
        frameCount = 0;
        fpsTimer->restart();
    }

    // ��ȡ֡
    videocapture->read(dst);
    if (dst.empty()) {
        return;
    }

    // ������ά��������
    QRCodeDetector qrDecoder;
    std::vector<Point> points; // ���ڴ洢��ά���Ķ���
    std::string decodedText = qrDecoder.detectAndDecode(dst, points);

    // �������⵽�˶�ά��
    if (!decodedText.empty() && points.size() == 4) {
        // ʹ�� quirc �����ɹ�
        // �ڶ�ά�����ĸ���֮�仭�ߣ�����ά��������
        for (int i = 0; i < 4; i++) {
            line(dst, points[i], points[(i + 1) % 4], Scalar(0, 255, 0), 3);
        }

        // �����������ı���ʾ�ڽ����ϵı�ǩ "erweima" ��
        ui->erweima->setText(QString::fromStdString(decodedText));
    }

    // ���� UI �е� FPS ��ʾ
    ui->fps->setText(QString("FPS: %0.2f").arg(fps, 0, 'f', 2));

    // �� OpenCV Mat ת��Ϊ QPixmap �Ա���ʾ�� Qt ������
    QPixmap qpixmap = Mat2QImage(dst);
    ui->camera->setPixmap(qpixmap);
}

QPixmap MainWindow::Mat2QImage(const cv::Mat &src)
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
