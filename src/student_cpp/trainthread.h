#ifndef TRAINTHREAD_H
#define TRAINTHREAD_H

#include <QThread>
#include "locomotive.h"

class TrainThread : QThread{
public:
    TrainThread(QVector<int> parcour, Locomotive* train)
        : QThread(), parcour(parcour),train(train){}

private:
    virtual void run() Q_DECL_OVERRIDE{

    }

    QVector<int> parcour;
    Locomotive* train;
};

#endif // TRAINTHREAD_H
