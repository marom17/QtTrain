#include "trainthread.h"
#include "ctrain_handler.h"

void TrainThread::run(){
    for (int i = 1; i < parcour.size(); i++) {
        attendre_contact(parcour.at(i));
        afficher_message(qPrintable(QString("The engine no. %1 has reached contact no. %2.").arg(train->numero()).arg(parcour.at(i))));
        train->afficherMessage(QString("I've reached contact no. %1.").arg(parcour.at(i)));
    }

    //Arreter la locomotive
    train->arreter();
    train->afficherMessage("Yeah, piece of cake!");
    return;
}
