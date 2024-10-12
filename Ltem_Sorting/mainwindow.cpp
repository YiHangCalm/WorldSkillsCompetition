#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myserial.h"
#include <QEventLoop>
#include <memory>

std::shared_ptr<MySerial> MainWindow::sharedSerial = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentMode(nullptr)
{
    ui->setupUi(this);
    this->showFullScreen();
    if (!sharedSerial) {
           qDebug() << "Initializing sharedSerial...";
           sharedSerial = std::make_shared<MySerial>(this);
       }
    connect(ui->modeButton, &QPushButton::pressed, this, &MainWindow::on_modeButton_Pressed);
    connect(ui->modeButton, &QPushButton::released, this, &MainWindow::on_modeButton_Released);
    connect(ui->ColourButton, &QPushButton::pressed, this, &MainWindow::on_ColourButton_Pressed);
    connect(ui->ColourButton, &QPushButton::released, this, &MainWindow::on_ColourButton_Released);
    connect(ui->exitButton, &QPushButton::pressed, this, &MainWindow::on_exitButton_Pressed);
    connect(ui->exitButton, &QPushButton::released, this, &MainWindow::on_exitButton_Released);
    connect(ui->usatbtn, &QPushButton::pressed, this, &MainWindow::on_usatbtn_Pressed);
    connect(ui->usatbtn, &QPushButton::released, this, &MainWindow::on_usatbtn_Released);
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
            showNormal();
        } else {
            showFullScreen();
        }
    }
}

void MainWindow::on_modeButton_Pressed()
{
    btn = std::make_unique<BtnEffect>(ui->modeButton);
    btn->zoom1();
}

void MainWindow::on_modeButton_Released() {
    if (btn) {
        QEventLoop loop;
        connect(btn->getAnimation(), &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
        btn->zoom2();
        loop.exec();
        btn.reset();
    }

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
    btn = std::make_unique<BtnEffect>(ui->ColourButton);
    btn->zoom1();
}

void MainWindow::on_ColourButton_Released()
{
    if (btn) {
        QEventLoop loop;
        connect(btn->getAnimation(), &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
        btn->zoom2();
        loop.exec();
        btn.reset();
    }
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
    btn = std::make_unique<BtnEffect>(ui->exitButton);
    btn->zoom1();
}

void MainWindow::on_exitButton_Released()
{
    if (btn) {
        QEventLoop loop;
        connect(btn->getAnimation(), &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
        btn->zoom2();
        loop.exec();
        btn.reset();
    }
    if (currentMode) {
        currentMode->exitMode();
        delete currentMode;
        currentMode = nullptr;
    }
    qApp->quit();
}

void MainWindow::on_usatbtn_Pressed()
{
    btn = std::make_unique<BtnEffect>(ui->usatbtn);
    btn->zoom1();
}

void MainWindow::on_usatbtn_Released()
{
    if (btn) {
        QEventLoop loop;
        connect(btn->getAnimation(), &QPropertyAnimation::finished, &loop, &QEventLoop::quit);
        btn->zoom2();
        loop.exec();
        btn.reset();
    }

    this->hide();
    sharedSerial->show();
}
