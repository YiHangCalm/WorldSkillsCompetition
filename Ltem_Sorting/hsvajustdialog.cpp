#include"hsvajustdialog.h"

HSVAdjustDialog::HSVAdjustDialog(int& lowH, int& highH, int& lowS, int& highS, int& lowV, int& highV, QWidget *parent)
    : QDialog(parent), iLowH(lowH), iHighH(highH), iLowS(lowS), iHighS(highS), iLowV(lowV), iHighV(highV)
{
    QVBoxLayout *layout = new QVBoxLayout;

    addSlider(layout, "低 H", iLowH, 0, 179);
    addSlider(layout, "高 H", iHighH, 0, 179);
    addSlider(layout, "低 S", iLowS, 0, 255);
    addSlider(layout, "高 S", iHighS, 0, 255);
    addSlider(layout, "低 V", iLowV, 0, 255);
    addSlider(layout, "高 V", iHighV, 0, 255);

    setLayout(layout);
    setWindowTitle("调节 HSV 阈值");
    resize(400,300);
}

void HSVAdjustDialog::addSlider(QVBoxLayout *layout, const QString &label, int &variable, int min, int max)
{
    // Create a new QWidget to hold the slider and value label
    QWidget *sliderWidget = new QWidget;
    QHBoxLayout *sliderLayout = new QHBoxLayout(sliderWidget); // Use this line

    // Create label for the slider
    QLabel* sliderLabel = new QLabel(label);
    sliderLayout->addWidget(sliderLabel);

    // Create the slider
    QSlider* slider = new QSlider(Qt::Horizontal);
    slider->setRange(min, max);
    slider->setValue(variable);
    sliderLayout->addWidget(slider);

    // Create label to show the current value
    QLabel* valueLabel = new QLabel(QString::number(variable));
    sliderLayout->addWidget(valueLabel);  // Use addWidget instead of setWideget

    // Set the layout to the slider widget
    sliderWidget->setLayout(sliderLayout); // Set the layout for the widget

    // Add the slider widget to the main layout
    layout->addWidget(sliderWidget); // Add the widget that holds the layout

    sliderToVariable[slider] = &variable;
    sliderToValueLabel[slider] = valueLabel;

    // Connect slider value changes to update the corresponding variable and label
    connect(slider, &QSlider::valueChanged, this, &HSVAdjustDialog::onSliderValueChanged);
}

void HSVAdjustDialog::onSliderValueChanged(int value)
{
    QSlider* senderSlider = qobject_cast<QSlider*>(sender());
    if (!senderSlider) return;

    // Update the corresponding variable and label
    if (sliderToVariable.contains(senderSlider))
    {
        *(sliderToVariable[senderSlider]) = value;
    }

    if (sliderToValueLabel.contains(senderSlider))
    {
        sliderToValueLabel[senderSlider]->setText(QString::number(value));
    }

}
