#ifndef LIVRE_H_INCLUDED
#define LIVRE_H_INCLUDED
#include <string>

class Livre{
    std::string titre;
    std::string auteur;
    std::string ISBN;
    std::string edition;
    unsigned int compteur;
    unsigned int nbLivreLibre;
    public:
        Livre();
        void ajouterLivre();
        void supprimerLivre(std::string,std::string);
        bool existeLivre(std::string);
        void afficherLivre();
        ~Livre();
};


#endif // LIVRE_H_INCLUDED
