#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "mode.h"
#include "qrcode_mode.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_modeButton_clicked();  // ����ģʽ��ť�����¼�

private:
    Ui::MainWindow *ui;
    QPushButton *modeButton;  // ����������ά��ģʽ�İ�ť
    Mode *currentMode;  // ��ǰ��ģʽ����ָ��
};

#endif // MAINWINDOW_H
