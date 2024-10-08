#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentMode(nullptr)
{
    ui->setupUi(this);

    // ����ģʽ��ť

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

void MainWindow::on_modeButton_clicked()
{


    if (currentMode) {
        currentMode->exitMode();
        delete currentMode;
    }
    // ��ť���º������Լ�
      ui-> modeButton->hide();
    // ������ά��ģʽ������
    currentMode = new QRCode_Mode(ui);
    currentMode->enterMode(this);
    currentMode->execute();
}
