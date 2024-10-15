#ifndef SCAN_COLOR_H
#define SCAN_COLOR_H

#include <QWidget>
#include "mode.h"
#include "camera.h"
#include "ui_scancolor.h"
#include <QKeyEvent>
#include "mainwindow.h"
class ScanColor : public QMainWindow , public Mode
{
    Q_OBJECT

public:
    explicit ScanColor(QWidget *parent = nullptr);
    void enterMode(QWidget *parentWidget);
    void execute();
    void exitMode();
    void show();
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_exitBtn_clicked();

    void on_adjust_pressed();

    void on_adjust_released();

private:
    void processFrame(const cv::Mat &frame);
    std::unique_ptr<BtnEffect> btn;
    Ui::ScanColor ui;
    std::unique_ptr<ExternalCamera> camera;  // Camera instance
    bool signalConnected = false;  // Flag for signal connection
};

#endif // SCAN_COLOR_H
