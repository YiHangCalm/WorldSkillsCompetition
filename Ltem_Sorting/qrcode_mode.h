#ifndef QR_CODE_MODE_H
#define QR_CODE_MODE_H

#include <QObject>  // ȷ������ QObject
#include <opencv2/opencv.hpp>
#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include "mode.h"
#include "camera.h"
#include "ui_mainwindow.h"
class QRCode_Mode : public QObject, public Mode  //
{
    Q_OBJECT

public:
    QRCode_Mode(Ui::MainWindow *ui);
    void enterMode(QWidget *parentWidget) override;  // ������ά��ģʽ
    void execute() override;  // ����ÿһ֡�Լ����ͽ�����ά��
    void exitMode() override;  // �˳���ά��ģʽ


private:
    void processFrame(const cv::Mat &frame);
    Ui::MainWindow *ui;
    ExternalCamera *camera;
    QTextEdit *decodedTextEdit;

    cv::QRCodeDetector qrDecoder;
    std::vector<cv::Point> points;

};

#endif // QR_CODE_MODE_H
