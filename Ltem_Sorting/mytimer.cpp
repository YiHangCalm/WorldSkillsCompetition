#include "mytimer.h"

mytimer::mytimer(QObject *parent) : QObject(parent)
{
}

QString mytimer::getCurrentTime()
{
    // ��ȡ��ǰʱ�䲢���أ���ʽΪ ʱ:��:��
    return QDateTime::currentDateTime().toString("HH:mm:ss");
}
