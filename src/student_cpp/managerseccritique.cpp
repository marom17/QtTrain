#include "managerseccritique.h"
#include <qdebug.h>

/*
 * Cette classe Permet de gerer l'acces concurent
 * a une section critique sur le circuit.
 * Elle est fortement inspiree de la solution
 * BridgeManager2.
 * Une gestion de priorite permet de donner acces
 * a un train choisi.
 *
 *
 * Auteurs : Kobel Nicolas
 *           Maillard Romain
 */

/*
 * Initialisation
 */
ManagerSecCritique::ManagerSecCritique() {
    mutex = new QSemaphore(1);
    waitAccess = new QSemaphore(0);
    occuppe = false;
    prioActuelle = 0;
    nbWaiting = 0;
}

/*
 * Liberation de memoire
 */
ManagerSecCritique::~ManagerSecCritique() {
    delete mutex;
    delete waitAccess;
}


/*
 * Formulation d'une requete. On annonce
 * l'intention d'entrer dans la section critique
 * avec sa priorite.
 */
void ManagerSecCritique::requete(int prio) {
    mutex->acquire();
    if(prio > prioActuelle)
        prioActuelle = prio;
    mutex->release();
 }

/*
 * Point d'entree de la section critique.
 * Permet d'arreter le train si la SC est
 * occupee.
 */
void ManagerSecCritique::entree(Locomotive *train, int prio) {
    mutex->acquire();
    // Il y a deja un train
    bool arrete = false;
    while (occuppe) {
        nbWaiting ++;
        mutex->release();
        if(!arrete) {
            train->arreter();
            arrete = true;
        }
        waitAccess->acquire();
    }
    // Ce train n'est pas prioritaire
    while (prio < prioActuelle) {
        nbWaiting ++;
        mutex->release();
        if(!arrete) {
            train->arreter();
            arrete = true;
        }
        waitAccess->acquire();

    }
    // Le train peut passer
    if(arrete) {
        train->demarrer();
    }
    occuppe = true;
    mutex->release();
}

/*
 * Sortie de la SC
 */
void ManagerSecCritique::sortie() {
    mutex->acquire();
    prioActuelle = 0;
    occuppe = false;
    // On signale aux trains attendant que la voie est libre
    if(nbWaiting > 0) {
        nbWaiting --;
        waitAccess->release();

    } else {
        mutex->release();
    }

}
