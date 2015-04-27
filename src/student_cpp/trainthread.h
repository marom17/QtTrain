#ifndef TRAINTHREAD_H
#define TRAINTHREAD_H

#include <QThread>
#include <QSemaphore>
#include "locomotive.h"
#include "managerseccritique.h"

class TrainThread : public QThread {
public:
    TrainThread() :
        QThread() {}

    TrainThread(QList<int> parcour, Locomotive* train, QSemaphore* sectionCritique, ManagerSecCritique* manager, int priorite)

        : QThread(), parcour(parcour),train(train), sectionCritique(sectionCritique), manager(manager), priorite(priorite) {
        nbrTour = 0;
    }

private:
    virtual void run() Q_DECL_OVERRIDE;
    void changerAiguillage(int sectionCourrante, int sectionSuivante);

    QSemaphore* sectionCritique;
    QList<int> parcour;
    Locomotive* train;

    int nbrTour;
    int priorite;

    ManagerSecCritique* manager;
};

#endif // TRAINTHREAD_H
