#include "trainthread.h"
#include "ctrain_handler.h"

void TrainThread::run() {

    train->demarrer();
    while(true) {

        for (int i = 1; i < parcour.size(); i++) {
            //Stop le train car acquire est bloquant
            train->arreter();

            sections.at(parcour.at(i-1%parcour.size())-1)->acquire();
            sections.at(parcour.at(i%parcour.size())-1)->acquire();

            //Redémarre le train quand tronçon libre
            train->demarrer();
            attendre_contact(parcour.at(i));
            int j = i+1 % parcour.size();
            //changerAiguillage(parcour.at(i), parcour.at(j));

            sections.at(parcour.at(i%parcour.size())-1)->release();
            sections.at(parcour.at(i-1%parcour.size())-1)->release();

            afficher_message(qPrintable(QString("The engine no. %1 has reached contact no. %2.").arg(train->numero()).arg(parcour.at(i))));
            train->afficherMessage(QString("I've reached contact no. %1.").arg(parcour.at(i)));

            diriger_aiguillage(6, TOUT_DROIT,  0);


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

void TrainThread::changerAiguillage(int sectionCourrante, int sectionSuivante) {
    switch (sectionCourrante) {
    case 1:
        if(sectionSuivante == 31)
            return;
        else if(sectionSuivante == 2) {
            diriger_aiguillage(1,  TOUT_DROIT,  0);
            return;
        } else if (sectionSuivante == 6) {
            diriger_aiguillage(1,  DEVIE,  0);
            return;
        } else {
            return;
        }
    case 2:
        if(sectionSuivante == 1) {
            diriger_aiguillage(1,  TOUT_DROIT,  0);
            return;
        } else
            return;
    case 3:
        if(sectionSuivante == 4) {
            diriger_aiguillage(4, TOUT_DROIT, 0);
        } else {
            return;
        }
    case 4:
        if(sectionSuivante == 3) {
            diriger_aiguillage(4, TOUT_DROIT, 0);
            return;
        } else if (sectionSuivante == 6) {
            diriger_aiguillage(4, DEVIE, 0);
            return;
        } else
            return;
    case 5:
        if(sectionSuivante == 6){
            diriger_aiguillage(2,DEVIE,0);
            return;
        } else {
            return;
        }
    case 6:
        if(sectionSuivante == 1){
            diriger_aiguillage(1,DEVIE,0);
            diriger_aiguillage(2,TOUT_DROIT,0);
            return;
        } else if (sectionSuivante == 5){
            diriger_aiguillage(2,DEVIE,0);
            return;
        } else if (sectionSuivante == 4){
            diriger_aiguillage(4,DEVIE,0);
            diriger_aiguillage(3,TOUT_DROIT,0);
            return;
        } else if (sectionSuivante == 7){
            diriger_aiguillage(3, DEVIE, 0);
            diriger_aiguillage(5,TOUT_DROIT,0);
            return;
        } else if (sectionSuivante == 8){
            diriger_aiguillage(3, DEVIE, 0);
            diriger_aiguillage(5,DEVIE,0);
            return;
        } else {
            return;
        }
    case 7:
        break;
    case 8:
        break;
    case 9:
        break;
    case 10:
        if (sectionSuivante == 11) {
            diriger_aiguillage(7, TOUT_DROIT, 0);
            return;
        } else if (sectionSuivante == 15) {
            diriger_aiguillage(7, DEVIE, 0);
            return;
        }
        break;
    case 11:
        break;
    case 12:
        break;
    case 13:
        break;
    case 14:
        break;
    case 15:
        break;
    case 16:
        break;
    case 17:
        break;
    case 18:
        break;
    case 19:
        break;
    case 20:
        break;
    case 21:
        break;
    case 22:
        break;
    case 23:
        break;
    case 24:
        break;
    case 25:
        break;
    case 26:
        break;
    case 27:
        break;
    case 28:
        break;
    case 29:
        break;
    case 30:
        break;
    case 31:
        break;
    case 32:
        break;
    case 33:
        break;
    case 34:
        break;
    case 35:
        break;
    case 36:
        break;
    case 37:
        break;
    case 38:
        break;
    }
}



