#include "scancolor.h"
#include <QDebug>
#include <QPainter>

ScanColor::ScanColor(QWidget *parent)
    : QMainWindow(parent), camera(nullptr)
{
    ui.setupUi(this);
    this->showFullScreen();
    connect(ui.exButton, &QPushButton::clicked, this, &ScanColor::on_exitBtn_clicked);
     ui.bin->setStyleSheet("border: 2px solid white;");  // ʹ����ʽ�����ñ߿���ɫ������
     ui.HSV->setStyleSheet("border: 2px solid white;");  // ʹ����ʽ�����ñ߿���ɫ������
     ui.informationEdit->setReadOnly(true) ;
     ui.widget->hide();

     lastColorDetectedTime = QDateTime::currentDateTime();  // �ڹ��캯���г�ʼ��
}

ScanColor::~ScanColor()
{

}

void ScanColor::enterMode(QWidget *parentWidget)
{
    if (!camera) {
        camera = std::make_unique<ExternalCamera>(this);
        camera->start();
    }

    this->execute();
}

void ScanColor::execute()
{
    if (!camera) return;

    if (!signalConnected) {
        // Ensure QObject::connect is successful
        if (QObject::connect(camera.get(), &ExternalCamera::frameReady, this, &ScanColor::processFrame)) {
            signalConnected = true;
        } else {
            qDebug() << "Failed to connect camera signal to processFrame";
        }
    }
}

void ScanColor::exitMode()
{
    if (camera) {
        camera->stop();  // Stop the camera
        camera.reset();  // Release camera resources
    }

    if (parentWidget()) {
        parentWidget()->show();
    }

    this->hide();
}

void ScanColor::show()
{
    QMainWindow::show();
}

void ScanColor::processFrame(const cv::Mat &frame) {
    if (frame.empty()) {
        qDebug() << "Input frame is empty!";
        return; // ���ڷ���
    }
    cv::Mat frameHSV;
       cv::cvtColor(frame, frameHSV, cv::COLOR_BGR2HSV);

       // Display the HSV image
       QPixmap hsvPixmap = camera->Mat2QImage(frameHSV);
       if (ui.HSV) {
           ui.HSV->setPixmap(hsvPixmap);
       }
       cv::Mat binaryImage;
          cv::inRange(frameHSV, cv::Scalar(iLowH, iLowS, iLowV), cv::Scalar(iHighH, iHighS, iHighV), binaryImage);

          // Display the binary image
          QPixmap binaryPixmap = camera->Mat2QImage(binaryImage);
          if (ui.bin) {
              ui.bin->setPixmap(binaryPixmap);
          }

          // Define color ranges for detection
          std::vector<std::pair<cv::Scalar, cv::Scalar>> colorRanges = {
              {cv::Scalar(125, 114, 71), cv::Scalar(180, 255, 255)}, // Upper Red
              {cv::Scalar(90, 170, 132), cv::Scalar(112, 255, 255)}, // Blue
              {cv::Scalar(35, 100, 100), cv::Scalar(85, 255, 255)},  // Green
          };

          std::vector<std::string> colorNames = {"Red", "Blue", "Green"};

             cv::Mat result = frame.clone();
             bool colorDetected = false;
             std::string detectedColor;

             // Get the current time
             QDateTime currentTime = QDateTime::currentDateTime();

             // Iterate through each color range to detect colors
             for (size_t i = 0; i < colorRanges.size(); ++i) {
                 cv::Mat mask;
                 cv::inRange(frameHSV, colorRanges[i].first, colorRanges[i].second, mask); // Filter color

                 // Dilate to strengthen the detected color region
                 cv::Mat dilatedMask;
                 cv::dilate(mask, dilatedMask, cv::Mat(), cv::Point(-1, -1), 2);

                 // Find contours
                 std::vector<std::vector<cv::Point>> contours;
                 cv::findContours(dilatedMask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

                 for (const auto &contour : contours) {
                     double area = cv::contourArea(contour);
                     if (area < 13000) {
                         continue;  // Ignore small areas
                     }
                     // Draw bounding box
                             cv::Rect boundingRect = cv::boundingRect(contour);
                             cv::rectangle(result, boundingRect, cv::Scalar(0, 255, 0), 2);

                             detectedColor = colorNames[i];
                             cv::putText(result, detectedColor,
                                         cv::Point(boundingRect.x, boundingRect.y - 10), // Text position
                                         cv::FONT_HERSHEY_SIMPLEX, // Font type
                                         0.7, // Font scale
                                         cv::Scalar(255, 255, 255), 1); // Text color

                             // Check if the detected color's time interval is more than 1 second
                             if (lastColorDetectedTime.msecsTo(currentTime) < 2000) {
                                 continue; // Ignore if less than 1 second has passed
                             }

                             // Log detected color with time
                             QString color = QString::fromStdString(detectedColor);
                             if (color == "Red") {
                                 ui.informationEdit->append(QString("%1  检测到红色包裹")
                                                            .arg(mytimer.getCurrentTime()));
                             } else if (color == "Blue") {
                                 ui.informationEdit->append(QString("%1  检测到蓝色包裹")
                                                            .arg(mytimer.getCurrentTime()));
                             } else if (color == "Green") {
                                 ui.informationEdit->append(QString("%1  检测到绿色包裹")
                                                            .arg(mytimer.getCurrentTime()));
                             }

                             // Send data based on mode and color
                             if (currentMode == classification) {
                                 if (color == "Red") {
                                     MainWindow::sharedSerial->sendDataPacket("1", MySerial::PacketType::Data);
                                 } else if (color == "Blue") {
                                     MainWindow::sharedSerial->sendDataPacket("2", MySerial::PacketType::Data);
                                 } else if (color == "Green") {
                                     MainWindow::sharedSerial->sendDataPacket("3", MySerial::PacketType::Data);
                                 }
                             } else {
                                 if (variable == R) {
                                     if (color == "Red")
                                         MainWindow::sharedSerial->sendDataPacket("1", MySerial::PacketType::Data);
                                     else
                                         MainWindow::sharedSerial->sendDataPacket("0", MySerial::PacketType::Data);
                                 } else if (variable == B) {
                                     if (color == "Blue")
                                         MainWindow::sharedSerial->sendDataPacket("2", MySerial::PacketType::Data);
                                     else
                                         MainWindow::sharedSerial->sendDataPacket("0", MySerial::PacketType::Data);
                                 } else if (variable == G) {
                                     if (color == "Green")
                                         MainWindow::sharedSerial->sendDataPacket("3", MySerial::PacketType::Data);
                                     else
                                         MainWindow::sharedSerial->sendDataPacket("0", MySerial::PacketType::Data);
                                 }
                             }

                             // Update the last detected color time
                             lastColorDetectedTime = currentTime;
                         }
                     }

                     // Display the result image
                     QPixmap qpixmap = camera->Mat2QImage(result);
                     camera->getCameraLabel()->setPixmap(qpixmap);
  }
void ScanColor::on_adjust_released()
{
    if (btn) {
        // ʹ���¼�ѭ����ȷ���������ɺ��ټ���
        QEventLoop loop;
        connect(btn->getAnimation(), &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
        btn->zoom2(); // ִ����������
        loop.exec();  // �ȴ���������
        btn.reset();  // ���ð�ťЧ������
    }

    // ���������Ի�����δ���������д���
    if (!adjustDialog) {
        adjustDialog = std::make_unique<HSVAdjustDialog>(iLowH, iHighH, iLowS, iHighS, iLowV, iHighV, this);
        // �����ź��Դ����Ի����Ľ����¼�

    }

    adjustDialog->show(); // ��ʾ�����Ի���
}
void ScanColor::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {

        if (isFullScreen()) {
            showNormal();
        } else {
            showFullScreen();
        }
    }
}

void ScanColor::on_exitBtn_clicked()
{
     MainWindow::sharedSerial->sendDataPacket("exit",MySerial::PacketType::Command);
     previousDetectedColor="";
    exitMode();
}

void ScanColor::on_adjust_pressed()
{
    btn = std::make_unique<BtnEffect>(ui.adjust);
    btn->zoom1();
}


void ScanColor::adjustButtonHeight(QPushButton *selectedButton) {
    // ���尴ť�ĸ߶�
    const int selectedHeight = 90;
    const int defaultHeight = 60;

    // ���谴ť��ָ���ֱ��� ui.yuntingButton, ui.baiyunButton, ui.bishuiButton
    QPushButton *buttons[] = {ui.red, ui.blue, ui.green};

    // ������ť���飬���ø߶�
    for (QPushButton *button : buttons) {
        if (button == selectedButton) {
            button->setFixedHeight(selectedHeight); // ���ô��밴ť�ĸ߶�
        } else {
            button->setFixedHeight(defaultHeight);  // ������ť�ĸ߶�
        }
    }
}

void ScanColor::on_red_clicked()
{
    btn = std::make_unique<BtnEffect>(ui.red);
    btn->zoom1();
    if(btn){
        QEventLoop loop;
        connect(btn->getAnimation(),&QPropertyAnimation::finished,&loop,&QEventLoop::quit);
        btn->zoom2();
        loop.exec();
        btn.reset();
    }
    this->variable=R;
      MainWindow::sharedSerial->sendDataPacket("red",MySerial::PacketType::Command);
      previousDetectedColor="";
    adjustButtonHeight(ui.red);
}


void ScanColor::on_green_clicked()
{
    btn = std::make_unique<BtnEffect>(ui.green);
    btn->zoom1();
    if(btn){
        QEventLoop loop;
        connect(btn->getAnimation(),&QPropertyAnimation::finished,&loop,&QEventLoop::quit);
        btn->zoom2();
        loop.exec();
        btn.reset();
    }
    this->variable=G;
     MainWindow::sharedSerial->sendDataPacket("green",MySerial::PacketType::Command);
     previousDetectedColor="";
    adjustButtonHeight(ui.green);
}


void ScanColor::on_blue_clicked()
{
    btn = std::make_unique<BtnEffect>(ui.blue);
    btn->zoom1();
    if(btn){
        QEventLoop loop;
        connect(btn->getAnimation(),&QPropertyAnimation::finished,&loop,&QEventLoop::quit);
        btn->zoom2();
        loop.exec();
        btn.reset();
    }
    this->variable=B;
     MainWindow::sharedSerial->sendDataPacket("blue",MySerial::PacketType::Command);
     previousDetectedColor="";

     adjustButtonHeight(ui.blue);
}


void ScanColor::on_appoint_clicked()
{
    btn = std::make_unique<BtnEffect>(ui.appoint);
    btn->zoom1();
    if(btn){
        QEventLoop loop;
        connect(btn->getAnimation(),&QPropertyAnimation::finished,&loop,&QEventLoop::quit);
        btn->zoom2();
        loop.exec();
        btn.reset();
    }
     MainWindow::sharedSerial->sendDataPacket("sorte",MySerial::PacketType::Command);
    previousDetectedColor="";
     this->variable=R;
      this->currentMode=classification;
    animateWidget2Hide();
}


void ScanColor::on_sorte_clicked()
{
    btn = std::make_unique<BtnEffect>(ui.sorte);
    btn->zoom1();
    if(btn){
        QEventLoop loop;
        connect(btn->getAnimation(),&QPropertyAnimation::finished,&loop,&QEventLoop::quit);
        btn->zoom2();
        loop.exec();
        btn.reset();
    }
     MainWindow::sharedSerial->sendDataPacket("appoint",MySerial::PacketType::Command);
     this->currentMode=appoint;
     animateWidget2Show();
}
void ScanColor::animateWidget2Show() {
    // ���� widget2 ��͸��Ч��
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(ui.widget);
    ui.widget->setGraphicsEffect(opacityEffect);

    // �������붯��
    QPropertyAnimation *fadeIn = new QPropertyAnimation(opacityEffect, "opacity");
    fadeIn->setDuration(500);  // 500 ����
    fadeIn->setStartValue(0);  // ��͸����ʼ
    fadeIn->setEndValue(1);    // ��Ϊ��ȫ�ɼ�

    // ��ʾ widget2
    ui.widget->show();

    // �������붯��
    fadeIn->start();
}
void ScanColor::animateWidget2Hide() {
    // ���� widget2 ��͸��Ч��
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(ui.widget);
    ui.widget->setGraphicsEffect(opacityEffect);

    // ������������
    QPropertyAnimation *fadeOut = new QPropertyAnimation(opacityEffect, "opacity");
    fadeOut->setDuration(500);  // 500 ����
    fadeOut->setStartValue(1);
    fadeOut->setEndValue(0);

    // ���Ӷ��������ź������� widget2
    connect(fadeOut, &QPropertyAnimation::finished, this, [this]() {
        ui.widget->hide();
    });

    // ������������
    fadeOut->start();
}
void ScanColor::resetAllButtons() {
    // ��ȡ������ť��ָ��
    QPushButton *buttons[3] = {ui.red, ui.blue, ui.green};

    // ����ÿ����ť�������߶ȸ�ԭΪĬ�ϵ� 60
    for (int i = 0; i < 3; i++) {
        buttons[i]->setFixedHeight(60);
    }
}
