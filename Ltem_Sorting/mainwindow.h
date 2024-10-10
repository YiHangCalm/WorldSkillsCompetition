#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "mode.h"
#include "qrcode.h"
#include "scancolor.h"
#include <QKeyEvent>
#include <QPropertyAnimation>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);
private slots:

    void on_modeButton_Pressed();
    void on_modeButton_Released();   // ���°�ťʱ�����Ĳۺ���

    void on_ColourButton_Released();
    void on_ColourButton_Pressed();

    void on_exitButton_Released();
    void on_exitButton_Pressed();

//     void   enterQRCodeMode();
//     void  enterScanColorMode();
private:
    Ui::MainWindow *ui;
    QPushButton *modeButton;  // ����������ά��ģʽ�İ�ť
    Mode *currentMode;  // ��ǰ��ģʽ�

};

#endif // MAINWINDOW_H
