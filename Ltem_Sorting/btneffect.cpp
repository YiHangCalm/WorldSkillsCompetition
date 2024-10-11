#include "btneffect.h"

BtnEffect::BtnEffect(QPushButton *btn) : button(btn), originalGeometry(btn->geometry()) {
    animation = new QPropertyAnimation(button, "geometry", button);



}

void BtnEffect::zoom1() {
    if (!button) return;  // ���鰴ťָ���Ƿ�Ϊ��

    animation->setDuration(100);
    animation->setStartValue(originalGeometry);

    // �����µĳߴ磬���ְ�ť�����Ĳ���
    int newWidth = originalGeometry.width() - 20;
    int newHeight = originalGeometry.height() - 20;
    int dx = (originalGeometry.width() - newWidth) / 2;
    int dy = (originalGeometry.height() - newHeight) / 2;

    animation->setEndValue(QRect(
        originalGeometry.x() + dx,
        originalGeometry.y() + dy,
        newWidth,
        newHeight
    ));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void BtnEffect::zoom2() {
    if (!button) return;  // ���鰴ťָ���Ƿ�Ϊ��

    animation->setDuration(100);

    // ʹ������Сʱ��ͬ��ƫ�������������Ĳ���
    int newWidth = originalGeometry.width() - 20;
    int newHeight = originalGeometry.height() - 20;
    int dx = (originalGeometry.width() - newWidth) / 2;
    int dy = (originalGeometry.height() - newHeight) / 2;

    animation->setStartValue(QRect(
        originalGeometry.x() + dx,
        originalGeometry.y() + dy,
        newWidth,
        newHeight
    ));
    animation->setEndValue(originalGeometry);
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

QPropertyAnimation *BtnEffect::getAnimation() const {
    return animation;
}
