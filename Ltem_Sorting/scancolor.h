#ifndef SCAN_COLOR_H
#define SCAN_COLOR_H

#include <QWidget>
#include "mode.h"
#include "camera.h"
#include "ui_scancolor.h"

class ScanColor : public QMainWindow , public Mode
{
    Q_OBJECT

public:
    explicit ScanColor(QWidget *parent = nullptr);
    void enterMode(QWidget *parentWidget);
    void execute();
    void exitMode();
    void show();

private slots:


    void on_exitBtn_clicked();

private:
    void processFrame(const cv::Mat &frame);

    Ui::ScanColor ui;
    std::unique_ptr<ExternalCamera> camera;  // ����ͷ����
    bool signalConnected = false;  // �Ƿ��������ź�
};

#endif // SCAN_COLOR_H
