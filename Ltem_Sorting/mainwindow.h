#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "mode.h"
#include "qrcode.h"
#include "scancolor.h"
#include <QKeyEvent>
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
    void on_modeButton_clicked();  // ����ģʽ��ť�����¼�
    void on_exitButton_clicked();
    void on_ColourButton_clicked();

private:
    Ui::MainWindow *ui;
    QPushButton *modeButton;  // ����������ά��ģʽ�İ�ť
    Mode *currentMode;  // ��ǰ��ģʽ����ָ��
};

#endif // MAINWINDOW_H
