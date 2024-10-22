#include "mywork.h"
#include <QDebug>
#include <QImage>


MyWork::MyWork(QObject *parent) : QObject(parent) {
    // ���캯����ʼ��
}

void MyWork::working(const QImage &image) {
    qDebug() << "Start working...";

    // ����ͼ����Ч��
    if (image.isNull()) {
        qDebug() << "Received invalid image.";
        return;
    }

    // ʹ�û����������� isProcessing ״̬
    {
        QMutexLocker locker(&mutex);
        if (isProcessing) {
            qDebug() << "Processing is ongoing, skipping work.";
            return; // �������ڴ�����������
        }
        isProcessing = true; // �������ڴ���
    }

    // ת�� QImage �� cv::Mat
    cv::Mat matImage = QImageToCvMat(image);

    // ���� QR ��
    std::vector<cv::Point> qPoints;
    std::vector<cv::Point> points;

    if (qrDecoder.detect(matImage, qPoints)) {
        points.assign(qPoints.begin(), qPoints.end());
        cv::Mat straightCode;
        decodedText = qrDecoder.decode(matImage, points, straightCode);

        if (!decodedText.empty()) {
            for (size_t i = 0; i < points.size(); i++) {
                cv::line(matImage, points[i], points[(i + 1) % points.size()], cv::Scalar(0, 255, 0), 2);
            }
            qDebug() << "Decoded QR Code:" << QString::fromStdString(decodedText);
        } else {
            qDebug() << "Failed to decode QR Code.";
        }
    } else {
        qDebug() << "QR Code detection failed.";
    }

    // �������ɣ��ͷ���������Ϊ���ٴ���
    {
        QMutexLocker locker(&mutex);
        isProcessing = false; // ���Ǵ�������
    }
}




cv::Mat MyWork::QImageToCvMat(const QImage &image)
{

        // ����ͼ���Ƿ���Ч
        if (image.isNull()) {
            return cv::Mat(); // ���ؿ� Mat ����
        }

        // ȷ�� QImage �ĸ�ʽ��������Ӧת��
        switch (image.format()) {
            case QImage::Format_RGB32: {
                // RGBA to BGR
                cv::Mat matImage(image.height(), image.width(), CV_8UC4, (void*)image.bits(), image.bytesPerLine());
                cv::cvtColor(matImage, matImage, cv::COLOR_RGBA2BGR);
                return matImage;
            }
            case QImage::Format_ARGB32: {
                // ARGB to BGR
                cv::Mat matImage(image.height(), image.width(), CV_8UC4, (void*)image.bits(), image.bytesPerLine());
                cv::cvtColor(matImage, matImage, cv::COLOR_BGRA2BGR);
                return matImage;
            }
            case QImage::Format_RGB888: {
                // RGB888 to BGR
                cv::Mat matImage(image.height(), image.width(), CV_8UC3, (void*)image.bits(), image.bytesPerLine());
                cv::cvtColor(matImage, matImage, cv::COLOR_RGB2BGR);
                return matImage;
            }
            case QImage::Format_Grayscale8: {
                // Grayscale to BGR
                cv::Mat matImage(image.height(), image.width(), CV_8UC1, (void*)image.bits(), image.bytesPerLine());
                cv::cvtColor(matImage, matImage, cv::COLOR_GRAY2BGR);
                return matImage;
            }
            default: {
                // ������֧�ֵ�ͼ����ʽ
                qWarning() << "Unsupported QImage format!";
                return cv::Mat(); // ���ؿ� Mat ����
            }
        }

}
