#include "managerseccritique.h"
#include <qdebug.h>


ManagerSecCritique::ManagerSecCritique()
{
    mutex = new QSemaphore(1);
    waitAccess = new QSemaphore(0);
    occuppe = false;
    prioActuelle = 0;
}

ManagerSecCritique::~ManagerSecCritique()
{
    delete mutex;
    delete waitAccess;
}

void ManagerSecCritique::requete(int prio) {
    qDebug() << "New request" << prio << endl;
    mutex->acquire();
    if(prio > prioActuelle)
        prioActuelle = prio;
    //listePrio.append(prio);
    mutex->release();
}

void ManagerSecCritique::entree(Locomotive *train, int prio) {
    qDebug() << "Entree " << train->numero() << " " << prio << endl;
    bool arrete = false;
    mutex->acquire();
    while (occuppe) {
        qDebug() << "Occuppe " << train->numero() << endl;
        nbWaiting ++;
        mutex->release();
        if(!arrete) {
            train->arreter();
            arrete = true;
        }
        waitAccess->acquire();
    }
    while (prio < prioActuelle) {
        qDebug() << "Petite Prio " << prio << prioActuelle << endl;
        nbWaiting ++;
        mutex->release();
        if(!arrete) {
            train->arreter();
            arrete = true;
        }
        waitAccess->acquire();

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
