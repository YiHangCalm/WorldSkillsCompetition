#ifndef MYTIMER_H
#define MYTIMER_H

#include <QObject>
#include <QDateTime>

class mytimer : public QObject
{
    Q_OBJECT

public:
    explicit mytimer(QObject *parent = nullptr);

    QString getCurrentTime();  // ��ȡ��ǰʱ�䣬��ʽΪ ʱ:��:��
};

#endif // MYTIMER_H
