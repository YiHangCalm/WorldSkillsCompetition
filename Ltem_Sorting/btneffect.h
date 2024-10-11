#ifndef BTNEFFECT_H
#define BTNEFFECT_H

#include <QPushButton>
#include <QPropertyAnimation>
#include <QRect>

class BtnEffect
{
public:
    explicit BtnEffect(QPushButton *btn);
    void zoom1();  // ��СЧ��
    void zoom2();  // �Ŵ�Ч��
    QPropertyAnimation* getAnimation() const;

private:
    QPushButton *button; // ���水ťָ��
    QRect originalGeometry; // ���水ť��ԭʼ���γߴ�
    QPropertyAnimation *animation; // ���ڴ洢����ָ��
};

#endif // BTNEFFECT_H
