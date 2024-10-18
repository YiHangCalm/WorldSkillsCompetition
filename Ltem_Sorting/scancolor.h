#ifndef SCAN_COLOR_H
#define SCAN_COLOR_H

#include <QWidget>
#include "mode.h"
#include "camera.h"
#include "ui_scancolor.h"
#include <QKeyEvent>
#include "mainwindow.h"
#include"hsvajustdialog.h"
#include "workthread.h"
#include "mytimer.h"
class ScanColor : public QMainWindow , public Mode
{
    Q_OBJECT

public:
    explicit ScanColor(QWidget *parent = nullptr);
     ~ ScanColor();
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
    int iLowH =10;
    int iHighH=40;

    int iLowS =90;
    int iHighS=255;

    int iLowV =1;
    int iHighV=255;
    void processFrame(const cv::Mat &frame);
    std::unique_ptr<BtnEffect> btn;
    Ui::ScanColor ui;
    std::unique_ptr<ExternalCamera> camera;  // Camera instance
    std::unique_ptr<HSVAdjustDialog>adjustDialog;
    bool signalConnected = false;  // Flag for signal connection
    mytimer mytimer;
};

#endif // SCAN_COLOR_H
