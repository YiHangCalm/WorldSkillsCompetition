#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QEventLoop>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentMode(nullptr)
{
    ui->setupUi(this);
    this->showFullScreen();


    connect(ui->modeButton, &QPushButton::pressed, this, &MainWindow::on_modeButton_Pressed);
    connect(ui->modeButton, &QPushButton::released, this, &MainWindow::on_modeButton_Released);
    connect(ui->ColourButton, &QPushButton::pressed, this, &MainWindow::on_ColourButton_Pressed);
    connect(ui->ColourButton, &QPushButton::released, this, &MainWindow::on_ColourButton_Released);
    connect(ui->exitButton, &QPushButton::pressed, this, &MainWindow::on_exitButton_Pressed);
    connect(ui->exitButton, &QPushButton::released, this, &MainWindow::on_exitButton_Released);
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
            showNormal();  // �˳�ȫ��״̬
        } else {
            showFullScreen();  // ����ȫ��״̬
        }
    }
}

void MainWindow::on_modeButton_Pressed()
{

}

void MainWindow::on_modeButton_Released()
{




    // ������ά��ģʽ
    if (currentMode) {
        currentMode->exitMode();
        delete currentMode;
        currentMode = nullptr;
    }

    this->hide();

    currentMode = new QRCode(this);
    currentMode->enterMode(this);
    currentMode->show();
}

void MainWindow::on_ColourButton_Pressed()
{

}

void MainWindow::on_ColourButton_Released()
{


    // ������ɫģʽ
    if (currentMode) {
        currentMode->exitMode();
        delete currentMode;
        currentMode = nullptr;
    }

    this->hide();

    currentMode = new ScanColor(this);
    currentMode->enterMode(this);
    currentMode->show();
}

void MainWindow::on_exitButton_Pressed()
{


}

void MainWindow::on_exitButton_Released()
{

      if (currentMode) {
          currentMode->exitMode();
          delete currentMode;
          currentMode = nullptr;
      }
    qApp->quit();
}
