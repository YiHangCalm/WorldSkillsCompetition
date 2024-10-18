#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QObject>
#include <QThread>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

class WorkThread : public QObject
{
    Q_OBJECT

public:
    explicit WorkThread(QObject *parent = nullptr);
    ~WorkThread();



signals:


public slots:


private:

};

#endif // WORKTHREAD_H
