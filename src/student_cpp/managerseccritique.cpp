#include "managerseccritique.h"
#include <qdebug.h>


ManagerSecCritique::ManagerSecCritique() {
    mutex = new QSemaphore(1);
    waitAccess = new QSemaphore(0);
    occuppe = false;
    prioActuelle = 0;
    nbWaiting = 0;
}

ManagerSecCritique::~ManagerSecCritique() {
    delete mutex;
    delete waitAccess;
}

void ManagerSecCritique::requete(int prio) {
    qDebug() << "New request" << prio << endl;
    mutex->acquire();
    qDebug() << "Mutex Acquired request" << endl;
    if(prio > prioActuelle)
        prioActuelle = prio;
    //listePrio.append(prio);
    mutex->release();
    qDebug() << "Mutex Released request" << endl;
}

void ManagerSecCritique::entree(Locomotive *train, int prio) {
    //qDebug() << "Entree train : " << train->numero() << " prio : " << prio << endl;
    bool arrete = false;
    mutex->acquire();
    qDebug() << "Mutex Acquired entry 1" << endl;
    while (occuppe) {
      //  qDebug() << "Occuppe " << train->numero() << endl;
        nbWaiting ++;
        mutex->release();
        qDebug() << "Mutex Released entry 1" << endl;
        if(!arrete) {
            train->arreter();
            arrete = true;
        }
        waitAccess->acquire();
    }
    while (prio < prioActuelle) {
        //qDebug() << "Petite Prio train : " << train->numero() << " prio : " << prio << prioActuelle << endl;
        nbWaiting ++;
        mutex->release();
        qDebug() << "Mutex Released entry 2" << endl;
        if(!arrete) {
            train->arreter();
          //  qDebug() << "Stop train : " << train->numero() << endl;
            arrete = true;
        }
        waitAccess->acquire();

    }

    if(arrete) {
        train->demarrer();
    }
    occuppe = true;
    mutex->release();
    qDebug() << "Mutex Released entry 3" << endl;
}

void ManagerSecCritique::sortie() {
    mutex->acquire();
    qDebug() << "Mutex Acquired exit" << endl;
    prioActuelle = 0;
    occuppe = false;
    if(nbWaiting > 0) {
        nbWaiting --;
        waitAccess->release();

    } else {
        mutex->release();
        qDebug() << "Mutex Released exit" << endl;
    }

}
