#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "mode.h"
#include "qrcode.h"
#include "scancolor.h"
#include <QKeyEvent>
#include <QPropertyAnimation>
#include "btneffect.h"
#include <memory>
#include "myserial.h"
#include <memory>
#include <QDebug>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event) override;

    static std::shared_ptr<class MySerial> sharedSerial;

private slots:
    void on_modeButton_Pressed();
    void on_modeButton_Released();

    void on_ColourButton_Released();
    void on_ColourButton_Pressed();

    void on_exitButton_Released();
    void on_exitButton_Pressed();

    void on_usatbtn_Pressed();
    void on_usatbtn_Released();

private:
    std::unique_ptr<BtnEffect> btn;
    Ui::MainWindow *ui;
    QPushButton *modeButton;
    Mode *currentMode;
};
#endif
