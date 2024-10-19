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
    private slots:
        void on_exButton_Release();
        void on_exButton_Pressed();

         void on_slowButton_pressed();
        void on_slowButton_released();

        void on_fastButton_pressed();
       void on_fastButton_released();




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
    };

    #endif // QR_CODE_MODE_H
