#ifndef MYWORK_H
#define MYWORK_H

#include <QObject>
#include <QThread>
#include <opencv2/opencv.hpp>
#include <QString>
#include "qrcode.h"  // ���� QRCode �Ķ���
class MyWork : public QThread
{
    Q_OBJECT

public:
    MyWork(const cv::Mat &frame, QObject *parent = nullptr);
    void run() override;

signals:
    void decoded(const std::string &decodedText, const std::vector<cv::Point> &points);

private:
    cv::Mat frame;
    cv::QRCodeDetector qrDecoder;  // ��������һ����ά����������ʵ��
};

#endif // MYWORK_H