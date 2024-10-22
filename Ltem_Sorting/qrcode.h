    #ifndef QR_CODE_MODE_H
    #define QR_CODE_MODE_H

    #include <QWidget>
    #include "mode.h"
    #include "camera.h"
    #include "ui_qrcode.h"
    #include "mytimer.h"
    #include <QFile>
    #include <QTextStream>
    #include "btneffect.h"
    #include <QKeyEvent>
    #include "mainwindow.h"  // ��Ҫ���� MainWindow ͷ�ļ�
    #include "mywork.h"
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QSequentialAnimationGroup>
    class QRCode : public QMainWindow, public Mode
    {
        Q_OBJECT

    public:
        explicit QRCode(QWidget *parent = nullptr);
        void enterMode(QWidget *parentWidget) override;
        void execute() override;
        void exitMode() override;
        void show() override;
        void  keyPressEvent(QKeyEvent *event);
        void handleDecoded(const std::string &decodedText, const std::vector<cv::Point> &points);
        void checkDamagedQRCode();
        enum ModeType {
               classification,
               appoint
               // �������ڴ˴���������ģʽ
           };
        enum ModeType_variable {
              yunting,
              bishui,
               baiyun,
               // �������ڴ˴���������ģʽ
        };

        void adjustButtonHeight(QPushButton *selectedButton) ;
        void animateWidget2Show();
        void animateWidget2Hide();

        void resetAllButtons();
        private slots:
        void on_exButton_Release();
        void on_exButton_Pressed();

         void on_slowButton_pressed();
        void on_slowButton_released();

        void on_fastButton_pressed();
       void on_fastButton_released();




       void on_yunting_clicked();

       void on_bishui_clicked();

       void on_baiyun_clicked(); // ȷ������������();

    private:
        void processFrame(const cv::Mat &frame);
        mytimer mytimer;
        Ui::qrcode ui;
        std::unique_ptr<BtnEffect> btn;  // ʹ������ָ������ BtnEffect
        std::unique_ptr<ExternalCamera> camera;
        cv::QRCodeDetector qrDecoder;
        std::string lastDecodedText;
        std::vector<cv::Point> lastPoints; // �洢����һ�ν����ĵ�
        bool isProcessing = false; // ��־����ʾ��ǰ�Ƿ��ڴ������߳�
        std::vector<cv::Point> points;
        bool signalConnected = false;
        int currentIndex = 1;
         ModeType currentMode;
         ModeType_variable variable;
    };

    #endif // QR_CODE_MODE_H
