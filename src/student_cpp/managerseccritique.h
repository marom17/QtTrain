#ifndef MANAGERSECCRITIQUE_H
#define MANAGERSECCRITIQUE_H

#include <QSemaphore>


class ManagerSecCritique
{
public:
    ManagerSecCritique();
    ~ManagerSecCritique();

    void requete(int prio);
    void entree();
    void sortie();

private:
    QSemaphore* mutex;

    int prioActuelle;
};

#endif // MANAGERSECCRITIQUE_H
