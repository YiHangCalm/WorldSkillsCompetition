#ifndef QR_CODE_MODE_H
#define QR_CODE_MODE_H

#include <QWidget>
#include "mode.h"
#include "camera.h"
#include "ui_qrcode.h"  // ������ qrcode.ui �Զ����ɵ�ͷ�ļ�

class QRCode : public QMainWindow, public Mode  // �̳��� QWidget �� Mode ����
{
    Q_OBJECT

public:
    explicit QRCode(QWidget *parent = nullptr);
    void enterMode(QWidget *parentWidget) override;  // ������ά��ģʽ
    void execute() override;  // ִ��ÿһ֡�Ĵ����߼�
    void exitMode() override;  // �˳���ά��ģʽ
    void show() override;  // ʵ�ֻ����� show ����

private:
    void processFrame(const cv::Mat &frame);

    Ui::qrcode ui;  // ʹ�� qrcode.ui ���ɵ� Ui �� ui;  // Ui �����ռ��е� QRCodeUI �࣬���ڹ��������ؼ�
    ExternalCamera *camera;  // ��������
    cv::QRCodeDetector qrDecoder;  // OpenCV �Ķ�ά��������
    std::vector<cv::Point> points;
};

#endif // QR_CODE_MODE_H
