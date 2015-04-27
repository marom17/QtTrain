#include "trainthread.h"
#include "ctrain_handler.h"

void TrainThread::run() {

    train->demarrer();

    while(true) {

        int entreeCritique=0;

        for (int i = 0; i < parcour.size(); i++) {

            //Envoit de la requête d'entrée en section critique
            if(entreeCritique==0 && (parcour.at(i)==19||parcour.at(i)==23||parcour.at(i)==31||parcour.at(i)==34)) {

                manager->requete(priorite);
                afficher_message((qPrintable(QString("The engine no. %1 ask for the critical section").arg((train->numero())))));
                train->afficherMessage((QString("I've send my request for the critical section")));
            }

            //Entrée en section critique
            if(entreeCritique!=parcour.at(i)&&(parcour.at(i)==13||parcour.at(i)==16||parcour.at(i)==5||parcour.at(i)==1)) {

                entreeCritique=parcour.at(i);
                manager->entree(train,priorite);
            }

            attendre_contact(parcour.at(i));
            int j = (i+1) % (parcour.size());
            changerAiguillage(parcour.at(i), parcour.at(j));

            afficher_message(qPrintable(QString("The engine no. %1 has reached contact no. %2.").arg(train->numero()).arg(parcour.at(i))));
            train->afficherMessage(QString("I've reached contact no. %1.").arg(parcour.at(i)));

            //Sortie de la section critique
            if(entreeCritique!=parcour.at(i)&&(parcour.at(i)==13||parcour.at(i)==16||parcour.at(i)==5||parcour.at(i)==1)) {
                entreeCritique=0;
                manager->sortie();
            }

            //Elimine le risque qu'une requête soit lancée après la sortie de la section critique
            if(requete!=parcour.at(i)&&(parcour.at(i)==19||parcour.at(i)==23||parcour.at(i)==31||parcour.at(i)==34)) {
                requete=0;
            }

            //Stop le train si arrêt d'urgence
            if(isInterruptionRequested()) {
                train->arreter();
                return;
            }
        }

        nbrTour++;

        //Change de sens tous les 2 tours
        if(nbrTour % 2 == 0) {

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
        if(sectionSuivante == 2) {
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
        if(sectionSuivante == 6) {
            diriger_aiguillage(2,DEVIE,0);
            return;
        } else {
            return;
        }
    case 6:
        if(sectionSuivante == 1) {
            diriger_aiguillage(1,DEVIE,0);
            diriger_aiguillage(2,TOUT_DROIT,0);
            return;
        } else if (sectionSuivante == 5) {
            diriger_aiguillage(2,DEVIE,0);
            return;
        } else if (sectionSuivante == 4) {
            diriger_aiguillage(4,DEVIE,0);
            diriger_aiguillage(3,TOUT_DROIT,0);
            return;
        } else if (sectionSuivante == 7) {
            diriger_aiguillage(3, DEVIE, 0);
            diriger_aiguillage(5,TOUT_DROIT,0);
            return;
        } else if (sectionSuivante == 8) {
            diriger_aiguillage(3, DEVIE, 0);
            diriger_aiguillage(5,DEVIE,0);
            return;
        } else {
            return;
        }
    case 7:
        if(sectionSuivante == 6) {
            diriger_aiguillage(5,TOUT_DROIT,0);
            diriger_aiguillage(3,DEVIE,0);
            return;
        } else
            return;
    case 8:
        if(sectionSuivante == 6) {
            diriger_aiguillage(5,DEVIE,0);
            diriger_aiguillage(3,DEVIE,0);
            return;
        } else
            return;
    case 9:
        if(sectionSuivante == 27) {
            diriger_aiguillage(6,DEVIE,0);
            diriger_aiguillage(18,DEVIE,0);
            return;
        } else if (sectionSuivante == 35) {
            diriger_aiguillage(6,TOUT_DROIT,0);
            diriger_aiguillage(24,TOUT_DROIT,0);
            return;
        } else
            return;
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
        if(sectionSuivante == 10) {
            diriger_aiguillage(7, TOUT_DROIT, 0);
        } else {
            return;
        }
    case 12:
        if(sectionSuivante == 13) {
            diriger_aiguillage(10,  TOUT_DROIT,  0);
            return;
        } else
            return;
    case 13:
        if(sectionSuivante == 12) {
            diriger_aiguillage(1,  TOUT_DROIT,  0);
            return;
        } else if (sectionSuivante == 15) {
            diriger_aiguillage(1,  DEVIE,  0);
            diriger_aiguillage(9,  TOUT_DROIT,  0);
            return;
        } else {
            return;
        }
    case 14:
        if(sectionSuivante == 14) {
            diriger_aiguillage(8,TOUT_DROIT,0);
            diriger_aiguillage(11,DEVIE,0);
            return;
        } else
            return;
    case 15:
        if (sectionSuivante == 16) {
            diriger_aiguillage(9,DEVIE,0);
            return;
        } else if (sectionSuivante == 18) {
            diriger_aiguillage(11, DEVIE, 0);
            diriger_aiguillage(8,DEVIE,0);
            return;
        } else {
            return changerAiguillage(sectionSuivante,sectionCourrante);
        }
    case 16:
        if(sectionSuivante == 15) {
            diriger_aiguillage(9,DEVIE,0);
            return;
        } else {
            return;
        }
    case 17:
        if(sectionSuivante == 35) {
            diriger_aiguillage(12,DEVIE,0);
            diriger_aiguillage(24,DEVIE,0);
            return;
        } else if (sectionSuivante == 27) {
            diriger_aiguillage(12,TOUT_DROIT,0);
            diriger_aiguillage(18,TOUT_DROIT,0);
            return;
        } else {
            return;
        }
    case 18:
        if(sectionSuivante == 15) {
            diriger_aiguillage(11, DEVIE, 0);
            diriger_aiguillage(8,DEVIE,0);
            return;
        } else {
            return;
        }
    case 19:
        if(sectionSuivante == 20) {
            diriger_aiguillage(13,  TOUT_DROIT,  0);
            return;
        } else if (sectionSuivante == 24) {
            diriger_aiguillage(13,  DEVIE,  0);
            diriger_aiguillage(14,TOUT_DROIT,0);
            return;
        } else {
            return;
        }
    case 20:
        if(sectionSuivante == 19) {
            diriger_aiguillage(13,TOUT_DROIT,0);
            return;
        } else {
            return;
        }
    case 21:
        if(sectionSuivante == 22) {
            diriger_aiguillage(16,TOUT_DROIT,0);
            return;
        } else {
            return;
        }
    case 22:
        if(sectionSuivante == 21) {
            diriger_aiguillage(16,TOUT_DROIT,0);
            return;
        } else if (sectionSuivante == 24) {
            diriger_aiguillage(15,TOUT_DROIT,0);
            diriger_aiguillage(16,DEVIE,0);
            return;
        } else return;
    case 23:
        if(sectionSuivante == 24) {
            diriger_aiguillage(14,DEVIE,0);
            return;
        } else return;
    case 24:
        if(sectionSuivante == 22) {
            diriger_aiguillage(15,TOUT_DROIT,0);
            diriger_aiguillage(16,DEVIE,0);
            return;
        } else if (sectionSuivante == 23) {
            diriger_aiguillage(14,DEVIE,0);
            return;
        } else if (sectionSuivante == 19) {
            diriger_aiguillage(14,TOUT_DROIT,0);
            diriger_aiguillage(13,DEVIE,0);
            return;
        } else if (sectionSuivante == 25) {
            diriger_aiguillage(17,TOUT_DROIT,0);
            diriger_aiguillage(15,DEVIE,0);
            return;
        } else if (sectionSuivante == 26) {
            diriger_aiguillage(15,DEVIE,0);
            diriger_aiguillage(17,DEVIE,0);
            return;
        } else return;
    case 25:
        if(sectionSuivante == 24) {
            diriger_aiguillage(17,TOUT_DROIT,0);
            diriger_aiguillage(15,DEVIE,0);
            return;
        } else return;
    case 26:
        if(sectionSuivante == 24) {
            diriger_aiguillage(17,DEVIE,0);
            diriger_aiguillage(15,DEVIE,0);
            return;
        } else return;
    case 27:
        if(sectionSuivante == 9) {
            diriger_aiguillage(18,DEVIE,0);
            diriger_aiguillage(6,DEVIE,0);
            return;
        } else if (sectionSuivante == 17) {
            diriger_aiguillage(18,TOUT_DROIT,0);
            diriger_aiguillage(12,TOUT_DROIT,0);
            return;
        } else {
            return;
        }
    case 28:
        if(sectionSuivante == 29) {
            diriger_aiguillage(19,TOUT_DROIT,0);
            return;
        } else if (sectionSuivante == 33) {
            diriger_aiguillage(19,DEVIE,0);
            diriger_aiguillage(20,TOUT_DROIT,0);
            return;
        } else return;
    case 29:
        if(sectionSuivante == 28) {
            diriger_aiguillage(19,TOUT_DROIT,0);
            return;
        } else return;
    case 30:
        if(sectionSuivante == 31) {
            diriger_aiguillage(22,TOUT_DROIT,0);
            return;
        } else return;
    case 31:
        if(sectionSuivante == 30) {
            diriger_aiguillage(22,TOUT_DROIT,0);
            return;
        } else if (sectionSuivante == 33) {
            diriger_aiguillage(22,DEVIE,0);
            diriger_aiguillage(21,TOUT_DROIT,0);
            return;
        } else return;
    case 32:
        if(sectionSuivante == 33) {
            diriger_aiguillage(23, TOUT_DROIT,0);
            diriger_aiguillage(20,DEVIE,0);
            return;
        } else return;
    case 33:
        if(sectionSuivante == 34) {
            diriger_aiguillage(21,DEVIE,0);
            return;
        } else if (sectionSuivante == 26) {
            diriger_aiguillage(20,DEVIE,0);
            diriger_aiguillage(23,DEVIE,0);
        }
        else {
            changerAiguillage(sectionSuivante,sectionCourrante);
            return;
        }
    case 34:
        return changerAiguillage(sectionSuivante,sectionCourrante);
    case 35:
        if(sectionSuivante == 36) {
            return;
        } else {
            return changerAiguillage(sectionSuivante, sectionCourrante);
        }
    case 36:
        return changerAiguillage(sectionSuivante,sectionCourrante);
    }
}



