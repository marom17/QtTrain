#include "trainthread.h"
#include "ctrain_handler.h"

void TrainThread::run() {

    train->demarrer();
    while(true) {

        for (int i = 1; i < parcour.size(); i++) {
            //Stop le train car acquire est bloquant
            train->arreter();
            sections.at(parcour.at(i)-1)->acquire();
            //Redémarre le train quand tronçon libre
            train->demarrer();
            attendre_contact(parcour.at(i));
            sections.at(parcour.at(i)-1)->release();
            afficher_message(qPrintable(QString("The engine no. %1 has reached contact no. %2.").arg(train->numero()).arg(parcour.at(i))));
            train->afficherMessage(QString("I've reached contact no. %1.").arg(parcour.at(i)));


            //Stop le train si arrêt d'urgence
            if(isInterruptionRequested()){
                train->arreter();
                return;
            }
        }

        nbrTour++;
        //Change de sens tous les 2 tours
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





