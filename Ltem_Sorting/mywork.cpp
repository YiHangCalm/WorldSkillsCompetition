#include "mywork.h"

MyWork::MyWork(const cv::Mat &frame, QObject *parent)
    : QThread(parent), frame(frame) {}

void MyWork::run() {
    std::vector<cv::Point> points;
    std::string decodedText = qrDecoder.detectAndDecode(frame, points);

    if (!decodedText.empty()) {
        emit decoded(decodedText, points);
        // �������źź󣬸���ʵ�����������Ƿ�ɾ��
    } else {
        // ��¼����ʧ����Ϣ����ѡ��
        // qDebug() << "Decode failed";
        this->deleteLater();
    }

    // ȷ�����ڴ˴����� deleteLater()
    // this->deleteLater();
}
