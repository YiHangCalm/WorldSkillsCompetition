#include "qrcode_mode.h"

QRCode_Mode::QRCode_Mode(Ui::MainWindow *ui) : ui(ui), camera(nullptr) {}

void QRCode_Mode::enterMode(QWidget *parentWidget)
{
    // ��������ͷ������
    camera = new ExternalCamera(parentWidget);
    camera->start();

         decodedTextEdit = new QTextEdit(parentWidget);
        decodedTextEdit->setReadOnly(true);  // ����Ϊֻ��ģʽ
        decodedTextEdit->setGeometry(340, 0, 350, 240);
        decodedTextEdit->setStyleSheet("font-size: 24px;");
        decodedTextEdit->show();

}

void QRCode_Mode::execute()
{
    if (!camera) return;
    connect(camera, &ExternalCamera::frameReady, this, [this](const cv::Mat &frame) {
         processFrame(frame);
     });
}

void QRCode_Mode::exitMode()
{
    if (camera) {
        delete camera;
        camera = nullptr;
    }
    if (decodedTextEdit){
        delete decodedTextEdit;
        decodedTextEdit=nullptr;
    }

    ui->modeButton->show();
}

void QRCode_Mode::processFrame(const cv::Mat &frame)
{
    // ����һ�����޸ĵĿ�������������
    cv::Mat frameWithLines = frame.clone();

    // ������ά��
    std::string decodedText = this->qrDecoder.detectAndDecode(frameWithLines, points);

    if (!decodedText.empty() && this->points.size() == 4) {
        // �ڶ�ά�����ı��ϻ���
        for (int i = 0; i < 4; i++) {
            cv::line(frameWithLines, this->points[i], this->points[(i + 1) % 4], cv::Scalar(0,0 , 255), 3);
        }

        // �������ı����ӵ��ı�����
        decodedTextEdit->append(QString::fromStdString(decodedText));
    }

    // ���޸ĺ���ͼ��������ʾ�� QLabel ��
    QPixmap qpixmap = camera->Mat2QImage(frameWithLines);
    camera->getCameraLabel()->setPixmap(qpixmap);
}


