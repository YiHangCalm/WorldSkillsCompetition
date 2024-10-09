#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentMode(nullptr)
{
    ui->setupUi(this);
    this->showFullScreen();
    // ����ģʽ��ť
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::on_exitButton_clicked);
     connect(ui->ColourButton, &QPushButton::clicked, this, &MainWindow::on_ColourButton_clicked);
    connect(ui->modeButton,&QPushButton::clicked, this, &MainWindow::on_modeButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (currentMode) {
        currentMode->exitMode();
        delete currentMode;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        if (isFullScreen()) {
            showNormal();  // ������ȫ��״̬���л�Ϊ����״̬
        } else {
            showFullScreen();  // ��������ȫ��״̬���л�Ϊȫ��
        }
    }
}
void MainWindow::on_modeButton_clicked()
{
    if (currentMode) {
            currentMode->exitMode();
            delete currentMode;  // ɾ������ģʽʵ��
            currentMode = nullptr;
        }
       this->hide();
    // ������������ά��ģʽ
    currentMode = new QRCode(this); // ���� `this` ��Ϊ�����󣬱��ڹ�����������
    currentMode->enterMode(this);
    currentMode->show(); // ��ʾ��ά�봰��
}
void MainWindow::on_ColourButton_clicked()
{
    if (currentMode) {
            currentMode->exitMode();
            delete currentMode;  // ɾ������ģʽʵ��
            currentMode = nullptr;
        }
       this->hide();
    // ������������ά��ģʽ
    currentMode = new ScanColor(this); // ���� `this` ��Ϊ�����󣬱��ڹ�����������
    currentMode->enterMode(this);
    currentMode->show(); // ��ʾ��ά�봰��
}
void MainWindow::on_exitButton_clicked() {
    if (currentMode) {
        currentMode->exitMode();
        delete currentMode;
        currentMode = nullptr;
    }
    qApp->quit(); // �ͷ�������Դ���˳�����
}



