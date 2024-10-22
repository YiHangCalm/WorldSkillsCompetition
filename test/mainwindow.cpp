#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
    frameCount(0) {

    // ��ʼ����ʾͼ���� QLabel
    imageLabel = new QLabel(this);
    imageLabel->setFixedSize(320, 240);  // ���� QLabel �ߴ�
    imageLabel->setScaledContents(true);  // ʹͼ����Ӧ QLabel

    fpsLabel = new QLabel("FPS: 0", this);
    fpsLabel->setStyleSheet("QLabel { color : white; background : black; }"); // ���� FPS ��ǩ��ʽ

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(imageLabel);

    QWidget *widget = new QWidget(this);
    widget->setLayout(layout);
    setCentralWidget(widget);

    // ����Ĭ������ͷ
    cap.open(0);
    if (!cap.isOpened()) {
        qFatal("Could not open camera.");
    }

    // ��������ͷ����
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 320);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 240);
    cap.set(cv::CAP_PROP_FPS, 90);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateFrame);
    timer->start(11); // ÿ 11 ��������һ֡����Լ 90 FPS

    timerFPS.start();

    // ���� FPS ��ǩ��λ��
    fpsLabel->setAttribute(Qt::WA_TransparentForMouseEvents);
    fpsLabel->setGeometry(10, 10, 100, 30); // ����λ�úʹ�С
    fpsLabel->raise(); // ȷ�� FPS ��ǩλ����ǰ��

    // ��ʼ�� MyWork �� QThread
    work = new MyWork;

    // ���� QThread ʵ��
    t1 = new QThread(this);

    // �� MyWork �ƶ������߳�
    work->moveToThread(t1);
    // �����ź�
    connect(this, &MainWindow::work_sig, work, &MyWork::working);    // �������߳�
    t1->start();


      // ȷ���źŲ������߳�����������

}

MainWindow::~MainWindow() {
    cap.release();  // �ͷ�����ͷ
    t1->quit();     // �����߳�
    t1->wait();     // �ȴ��߳��˳�
    delete work;    // ɾ����������
    delete t1;      // ɾ���߳�
}

void MainWindow::updateFrame() {
    cv::Mat frame;
    cap >> frame;  // ������ͷ��ȡһ֡

    if (frame.empty()) {
        return; // ȷ��֡��Ч
    }

    // �� OpenCV Mat ת��Ϊ QImage
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB); // ת����ɫ��ʽ
    QImage img = QImage((const unsigned char*)frame.data, frame.cols, frame.rows, frame.step[0], QImage::Format_RGB888);

    {
           QMutexLocker locker(&mutex); // ����
           if (work->isProcessing) {
                      qDebug() << "Skipping signal emission because processing is ongoing.";
                      return; // �����źŷ���
                  }
           emit work_sig(img); // �����ź�
       }
    // ��ʾͼ��
    imageLabel->setPixmap(QPixmap::fromImage(img));

    // ���� FPS
    frameCount++;
    int elapsed = timerFPS.elapsed();
    if (elapsed >= 1000) {
        fpsLabel->setText(QString("FPS: %1").arg(frameCount));
        frameCount = 0;
        timerFPS.restart();
    }
    this->i++;

       // ʹ��qDebug��ȷ����
    //   qDebug() << "zhuxianc:" << this->i; // ע��������i��������֮ǰ�����ģ�������Ҫ����������ʾ��������ֵ��Ӧ���ڴ��к���


}
