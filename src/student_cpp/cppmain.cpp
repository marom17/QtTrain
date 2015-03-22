#include "ctrain_handler.h"
#include "locomotive.h"
#include "trainthread.h"
#include <QList>

//Creation d'une locomotive
static Locomotive locomotive;
static Locomotive loco2;

//Arret d'urgence
void emergency_stop()
{
    locomotive.arreter();
    afficher_message("\nSTOP!");
}

//Fonction principale
int cmain()
{
    afficher_message("Hit play to start the simulation...");

    //Choix de la maquette
    selection_maquette(MAQUETTE_A);

    //Initialisation d'un parcours
    QList<int> parcours;
    parcours << 7 << 15 << 14 << 7 << 6 << 5 << 34 << 33 << 32 << 25 << 24;
    QList<int> parcours2;
    parcours2 << 12 << 11 << 10 << 4 << 3 << 2 << 1 << 31 << 30 << 29 << 28 << 22 << 21 << 20;
    QList<QSemaphore *> sections;
    sections << new QSemaphore(1);

    //Initialisation des aiguillages
    diriger_aiguillage(8,  DEVIE,       0);
    diriger_aiguillage(2,  DEVIE,       0);
    diriger_aiguillage(20, DEVIE,       0);
    diriger_aiguillage(14, DEVIE,       0);
    diriger_aiguillage(11, TOUT_DROIT,  0);
    diriger_aiguillage(17, TOUT_DROIT,  0);
    diriger_aiguillage(23, TOUT_DROIT,  0);

    diriger_aiguillage(4,  TOUT_DROIT,  0);
    diriger_aiguillage(10, TOUT_DROIT,  0);
    diriger_aiguillage(13, TOUT_DROIT,  0);
    diriger_aiguillage(7,  TOUT_DROIT,  0);
    diriger_aiguillage(1,  TOUT_DROIT,  0);
    diriger_aiguillage(22, TOUT_DROIT,  0);
    diriger_aiguillage(19, TOUT_DROIT,  0);
    diriger_aiguillage(16, TOUT_DROIT,  0);

    //Initialisation de la locomotive
    locomotive.fixerNumero(1);
    locomotive.fixerVitesse(12);
    locomotive.fixerPosition(16, 23);
    locomotive.allumerPhares();
    locomotive.demarrer();
    locomotive.afficherMessage("Ready!");

    loco2.fixerNumero(2);
    loco2.fixerVitesse(14);
    loco2.fixerPosition(13,19);
    loco2.allumerPhares();
    loco2.demarrer();
    loco2.afficherMessage("Loco2 Ready");

    TrainThread tthread(parcours, &locomotive, sections);
    TrainThread tthread2(parcours2, &loco2, sections);
    tthread.start();
    tthread2.start();

    //Attente du passage sur les contacts
    /*for (int i = 1; i < parcours.size(); i++) {
        attendre_contact(parcours.at(i));
        afficher_message(qPrintable(QString("The engine no. %1 has reached contact no. %2.").arg(locomotive.numero()).arg(parcours.at(i))));
        locomotive.afficherMessage(QString("I've reached contact no. %1.").arg(parcours.at(i)));
    }

    //Arreter la locomotive
    locomotive.arreter();
    locomotive.afficherMessage("Yeah, piece of cake!");*/

    //Fin de la simulation
    tthread.wait();
    tthread2.wait();
    mettre_maquette_hors_service();

    //Exemple de commande
    afficher_message("Enter a command in the input field at the top of the window.");
    QString commande = getCommand();
    afficher_message(qPrintable(QString("Your command is: ") + commande));

    return EXIT_SUCCESS;
}
