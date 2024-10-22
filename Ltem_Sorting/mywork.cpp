#include "mywork.h"

MyWork::MyWork(const cv::Mat &frame, QObject *parent)
    : QThread(parent), frame(frame) {}

void MyWork::run() {
    // ����ɫͼ��ת��Ϊ�Ҷ�ͼ��
    cv::Mat grayFrame;
    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);  // תΪ�Ҷ�ͼ��


    ImageScanner scanner;
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);  // ����������������
    Image zbarImage(grayFrame.cols, grayFrame.rows, "Y800", grayFrame.data, grayFrame.cols * grayFrame.rows);

    // ��ʼɨ��ͼ��
    int result = scanner.scan(zbarImage);

    if (result > 0) {
        // ����ÿ�����ţ���ά��/���룩
        for (Image::SymbolIterator symbol = zbarImage.symbol_begin(); symbol != zbarImage.symbol_end(); ++symbol) {
            std::string decodedText = symbol->get_data();  // ��ȡ�����ı�
            std::vector<cv::Point> points;

            // ��ȡ���ŵ��ĸ�����
            for (int i = 0; i < symbol->get_location_size(); i++) {
                points.emplace_back(symbol->get_location_x(i), symbol->get_location_y(i));
            }

            emit decoded(decodedText, points);  // ���ͽ����ź�
        }
    } else {
        // ����ʧ��ʱ�Ĵ�����������־������
        // qDebug() << "Decode failed";
    }

    // �ڴ˴�����Ҫʹ�� deleteLater()��QThread���Զ���������������
}
