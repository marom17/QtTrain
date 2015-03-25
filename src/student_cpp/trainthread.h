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

        : QThread(), parcour(parcour),train(train), sections(sections) {
        nbrTour = 0;
    }

private:
    virtual void run() Q_DECL_OVERRIDE;
    void changerAiguillage(int sectionCourrante, int sectionSuivante);

    QList<QSemaphore *> sections;
    QList<int> parcour;
    Locomotive* train;

    int nbrTour;
};

#endif // TRAINTHREAD_H
