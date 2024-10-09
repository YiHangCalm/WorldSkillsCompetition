#ifndef SCAN_COLOR_H
#define SCAN_COLOR_H

#include <QWidget>
#include "mode.h"
#include "camera.h"
#include "ui_scancolor.h"  // ���� UI �ļ� scancolor.ui ��ͷ�ļ�

class ScanColor : public QMainWindow , public Mode  // ��Ϊֻ�̳� QMainWindow
{
    Q_OBJECT

public:
    explicit ScanColor(QWidget *parent = nullptr);
    void enterMode(QWidget *parentWidget);  // ������ɫʶ��ģʽ
    void execute();  // ����ÿһ֡����
    void exitMode();  // �˳���ɫʶ��ģʽ
    void show();  // ʵ����ʾ����

private slots:


    void on_exitButton_clicked();

private:
    void processFrame(const cv::Mat &frame);  // ��������ͷ������֡

    Ui::ScanColor ui;  // UI ��������
    std::unique_ptr<ExternalCamera> camera;  // ����ͷ����
    bool signalConnected = false;  // �Ƿ��������ź�
};

#endif // SCAN_COLOR_H
