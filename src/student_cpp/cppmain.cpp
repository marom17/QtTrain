#include "ctrain_handler.h"
#include "locomotive.h"
#include "trainthread.h"
#include <QList>

/*
 * Programme principal pour le parcours de trains
 * Les parcours et les sections critiques sont codes
 * en dur.
 *
 * Le fonctionnement du programme a ete teste en simulation
 * uniquement.
 * Grace aux boutons pause/start des locomotives
 * plusieurs situations critiques ont etes testees.
 *
 * Ce code correspond au deuxieme ennonce.
 *
 * Auteurs : Kobel Nicolas
 *           Maillard Romain
 */

//Creation d'une locomotive
static Locomotive locomotive;
static Locomotive loco2;


TrainThread* tthread1;
TrainThread* tthread2;



//Arret d'urgence
void emergency_stop() {
    afficher_message("\nSTOP!");
    tthread1->requestInterruption();
    tthread2->requestInterruption();
}

//Fonction principale
int cmain() {
    afficher_message("Hit play to start the simulation...");

    //Choix de la maquette
    selection_maquette(MAQUETTE_A);

    //Initialisation des parcours
    QList<int> parcours;
    parcours  << 19 << 13 << 15 << 14 << 7 << 6 << 1 << 31 << 30 << 29 << 28 << 22 << 21 << 20;
    QList<int> parcours2;
    parcours2 << 23 << 16 << 15 << 14 << 7 << 6 << 5 << 34 << 33 << 32 << 25 << 24;
    QSemaphore* sectionCritique = new QSemaphore(1);
    ManagerSecCritique* manager = new ManagerSecCritique();

    //Initialisation des aiguillages
    diriger_aiguillage(8,  DEVIE,       0);
    diriger_aiguillage(2,  DEVIE,       0);
    diriger_aiguillage(20, DEVIE,       0);
    diriger_aiguillage(14, DEVIE,       0);
    diriger_aiguillage(11, TOUT_DROIT,  0);
    diriger_aiguillage(17, TOUT_DROIT,  0);
    diriger_aiguillage(23, TOUT_DROIT,  0);
    diriger_aiguillage(5 , TOUT_DROIT,  0);

    diriger_aiguillage(4,  TOUT_DROIT,  0);
    diriger_aiguillage(10, DEVIE,  0);
    diriger_aiguillage(13, TOUT_DROIT,  0);
    diriger_aiguillage(7,  TOUT_DROIT,  0);
    diriger_aiguillage(1,  TOUT_DROIT,  0);
    diriger_aiguillage(22, TOUT_DROIT,  0);
    diriger_aiguillage(19, TOUT_DROIT,  0);
    diriger_aiguillage(16, TOUT_DROIT,  0);


    //Initialisation de la premiere locomotive
    locomotive.fixerNumero(1);
    locomotive.fixerVitesse(12);
    locomotive.fixerPosition(19, 20);
    locomotive.allumerPhares();
    locomotive.afficherMessage("Ready!");

    // Initialisation de la deuxieme locomotive
    loco2.fixerNumero(2);
    loco2.fixerVitesse(14);
    loco2.fixerPosition(23,24);
    loco2.allumerPhares();
    loco2.demarrer();
    loco2.afficherMessage("Loco2 Ready");

    // Demare les trains
    tthread1 = new TrainThread(parcours, &locomotive, sectionCritique,manager,2);
    tthread2 = new TrainThread(parcours2, &loco2, sectionCritique,manager,1);
    tthread1->start();
    tthread2->start();


    // Fin du parcours
    tthread1->wait();
    tthread2->wait();

    mettre_maquette_hors_service();

    return EXIT_SUCCESS;
}
