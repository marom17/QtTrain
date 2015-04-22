#include "managerseccritique.h"
#include "locomotive.h"

ManagerSecCritique::ManagerSecCritique()
{
    mutex = new QSemaphore(1);
    waitAccess = new QSemaphore(0);
}

ManagerSecCritique::~ManagerSecCritique()
{
    delete mutex;
}

void ManagerSecCritique::requete(int prio) {
    mutex->acquire();
    if(prio>prioActuelle)
        prioActuelle = prio;
    mutex->release();
}

void ManagerSecCritique::entree(Locomotive *train, int prio) {
    bool arrete = false;
    mutex->acquire();
    if (occuppe) {
        nbWaiting ++;
        mutex->release();
        if(!arrete) {
            train->arreter();
            arrete = true;
        }
        waitAccess->acquire();
    } else if (prio < prioActuelle) {
        nbWaiting ++;
        mutex->release();
        if(!arrete) {
            train->arreter();
            arrete = true;
        }
        waitAccess->release();

    }

    if(arrete)
    {
        train->demarrer();
    }

    mutex->release();
}

void ManagerSecCritique::sortie() {
    mutex->acquire();
    prioActuelle = 0;
    if(nbWaiting > 0) {
        nbWaiting --;
        waitAccess->release();
    } else {
        mutex->release();
    }

}
