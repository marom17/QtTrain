#ifndef TRAINTHREAD_H
#define TRAINTHREAD_H

#include <QThread>
#include <QSemaphore>
#include "locomotive.h"

class TrainThread : public QThread {
public:
    TrainThread() :
        QThread() {}

    TrainThread(QList<int> parcour, Locomotive* train, QList<QSemaphore *> sections)
        : QThread(), parcour(parcour),train(train), sections(sections), noTour(0) {}

    QList<QSemaphore *> getSections() const;
    void setSections(const QList<QSemaphore *> &value);

    QList<int> getParcour() const;
    void setParcour(const QList<int> &value);

    Locomotive *getTrain() const;
    void setTrain(Locomotive *value);

    int getNoTour() const;
    void setNoTour(int value);

private:
    virtual void run() Q_DECL_OVERRIDE;

    QList<QSemaphore *> sections;
    QList<int> parcour;
    Locomotive* train;
    int noTour;
};

#endif // TRAINTHREAD_H
