#ifndef MANAGERSECCRITIQUE_H
#define MANAGERSECCRITIQUE_H

#include <QSemaphore>

#include "locomotive.h"

class ManagerSecCritique
{
public:
    ManagerSecCritique();
    ~ManagerSecCritique();

    void requete(int prio);
    void entree(Locomotive *train, int prio);
    void sortie();

private:
    QSemaphore* mutex;
    QSemaphore* waitAccess;

    int prioActuelle;
    bool occuppe;
    int nbWaiting;
    //QList<int> listePrio;
};

#endif // MANAGERSECCRITIQUE_H
