#ifndef MODE_H
#define MODE_H

#include <QWidget>  // ��������ͷ�ļ��Խ��� QWidget δ֪������

class Mode
{
public:
    Mode() noexcept;  // ������������ noexcept ˵����
    virtual void enterMode(QWidget *parentWidget) = 0;  // �����ຯ������Ϊ�麯��
    virtual void execute() = 0;
    virtual void exitMode() = 0;
    //virtual void prepareUI(QWidget *parentWidget) = 0;
    virtual ~Mode() {}
};

#endif // MODE_H
