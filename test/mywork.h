#ifndef MYWORK_H
#define MYWORK_H

#include <QObject>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <QString>
#include <QSharedPointer>
#include <QVector>
#include <QMutex>
#include <QMutexLocker>
class MyWork : public QObject {
    Q_OBJECT // ȷ�������ǿ���ʹ�� Qt �źźͲۻ��Ƶ�

public:
    MyWork(QObject *parent = nullptr); // ���캯��
    void working(const QImage &image);
    cv::Mat QImageToCvMat(const QImage &image); // ��������
bool isProcessing;
private:
    cv::QRCodeDetector qrDecoder; // QRCodeDetector ʵ��
    QVector<cv::Point> points; // �洢 QR ���ǵ�
    std::string decodedText; // �洢�����ı�
      QMutex mutex;  // ���ӻ�����

};

#endif // MYWORK_H
