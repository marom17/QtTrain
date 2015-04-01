#ifndef TRAINTHREAD_H
#define TRAINTHREAD_H

#include <QThread>
#include <QSemaphore>
#include "locomotive.h"

class TrainThread : public QThread {
public:
    TrainThread() :
        QThread() {}

    TrainThread(QList<int> parcour, Locomotive* train, QSemaphore* sectionCritique)

        : QThread(), parcour(parcour),train(train), sectionCritique(sectionCritique) {
        nbrTour = 0;
    }

private:
    virtual void run() Q_DECL_OVERRIDE;
    void changerAiguillage(int sectionCourrante, int sectionSuivante);

    QSemaphore* sectionCritique;
    QList<int> parcour;
    Locomotive* train;

    int nbrTour;
};

#endif // TRAINTHREAD_H
