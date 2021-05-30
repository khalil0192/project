#ifndef ADHERENT_H_INCLUDED
#define ADHERENT_H_INCLUDED
#include <string>

class Adherent{
    std::string nom;
    std::string prenom;
    std::string codeMassar;
    public:
        Adherent();
        void ajouterAdherent();
        bool existeAdherent(std::string);
        void supprimerAdherent(std::string);
        void afficherAdherent();
        ~Adherent();

};

#endif // ADHERENT_H_INCLUDED
