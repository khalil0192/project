#ifndef EMPRUNT_H_INCLUDED
#define EMPRUNT_H_INCLUDED
#include <string>
#include "livre.h"
#include "adherent.h"

class Emprunt{
    std::string dateRetourtheo;
    std::string dateReservation;
    Adherent adh;
    Livre liv;
    public:
        Emprunt();
        void faireEmprunt(std::string,std::string);
        void finaliserEmprunt(std::string,std::string);
        void faireReservation(std::string,std::string);
        void annulerReservation(std::string,std::string);
        bool dejaReserver(std::string);
        void afficheEmprunt();
        void afficheReserve();
        void afficheStock();
        ~Emprunt();
};

#endif // EMPRUNT_H_INCLUDED
