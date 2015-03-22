#include "trainthread.h"
#include "ctrain_handler.h"

void TrainThread::run() {
    while(true) {
        train->demarrer();
        for (int i = 1; i < parcour.size(); i++) {
            attendre_contact(parcour.at(i));
            afficher_message(qPrintable(QString("The engine no. %1 has reached contact no. %2.").arg(train->numero()).arg(parcour.at(i))));
            train->afficherMessage(QString("I've reached contact no. %1.").arg(parcour.at(i)));
            if(isInterruptionRequested()) {
                train->arreter();
                train->afficherMessage("Recu interruption");
                return;
            }
            noTour++;
            //Arreter la locomotive
            if(!(noTour %= 2)) {
                train->arreter();
                inverser_sens_loco(train->numero());
                for(int i = 0; i < parcour.size()/2; i++) {
                    parcour.swap(i, parcour.size()-(1+i));
                }

            }

        }
        return;
    }
}
QList<QSemaphore *> TrainThread::getSections() const
{
    return sections;
}

void TrainThread::setSections(const QList<QSemaphore *> &value)
{
    sections = value;
}
QList<int> TrainThread::getParcour() const
{
    return parcour;
}

void TrainThread::setParcour(const QList<int> &value)
{
    parcour = value;
}
Locomotive *TrainThread::getTrain() const
{
    return train;
}

void TrainThread::setTrain(Locomotive *value)
{
    train = value;
}
int TrainThread::getNoTour() const
{
    return noTour;
}

void TrainThread::setNoTour(int value)
{
    noTour = value;
}





