#include "mytimer.h"

mytimer::mytimer(QObject *parent) : QObject(parent)
{
}

QString mytimer::getCurrentTime()
{

    return QDateTime::currentDateTime().toString("HH:mm:ss");
}
