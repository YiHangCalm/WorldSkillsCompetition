#ifndef HSV_ADJUST_DIALOG_H
#define HSV_ADJUST_DIALOG_H

#include <QDialog>
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>
#include<QMap>
class HSVAdjustDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HSVAdjustDialog(int& lowH, int& highH, int& lowS, int& highS, int& lowV, int& highV, QWidget *parent = nullptr);

private slots:
    void onSliderValueChanged(int value);


private:
    int& iLowH;
    int& iHighH;
    int& iLowS;
    int& iHighS;
    int& iLowV;
    int& iHighV;

    QMap<QSlider*, int*> sliderToVariable;
    QLabel* valueLabel ;

    QMap<QSlider*, QLabel*> sliderToValueLabel;  // ������һ��
    void addSlider(QVBoxLayout* layout, const QString& label, int& variable, int min, int max);
};

#endif // HSV_ADJUST_DIALOG_H
