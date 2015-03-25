#include "trainthread.h"
#include "ctrain_handler.h"

void TrainThread::run() {
    train->demarrer();
    while(true) {

        for (int i = 1; i < parcour.size(); i++) {
            attendre_contact(parcour.at(i));
            afficher_message(qPrintable(QString("The engine no. %1 has reached contact no. %2.").arg(train->numero()).arg(parcour.at(i))));
            train->afficherMessage(QString("I've reached contact no. %1.").arg(parcour.at(i)));

            if(isInterruptionRequested()){
                train->arreter();
                return;
            }
        }

        nbrTour++;
        if(nbrTour % 2 == 0){
            train->arreter();
            inverser_sens_loco(train->numero());
            for(int k = 0; k < (parcour.size()/2); k++)
                parcour.swap(k,parcour.size()-(1+k));
            train->demarrer();

        }

        //Arreter la locomotive

        train->afficherMessage("Yeah, piece of cake!");
    }
    return;
}
