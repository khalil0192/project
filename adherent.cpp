#include <iostream>
#include "adherent.h"
#include <string>
#include <fstream>
#include <iomanip>      // std::setw
using namespace std;

Adherent::Adherent(){
    //Constructeurs de l'Adherent
}

void Adherent::ajouterAdherent(){
    ofstream adherent;
    adherent.open ("adherent.txt", ofstream::out | ofstream::app);
    cout<<"\n----- veuillez saisir les infos de l'adherent a ajouter -----\n";
    cout<<"nom: ";cin>>nom;
    cout<<"prenom: ";cin>>prenom;
    cout<<"code massar: ";cin>>codeMassar;
    if(existeAdherent(codeMassar)==1){
        adherent<<"|nom:"<<setw(12)<<nom<<"|prenom:"<<setw(12)<<prenom<<"|codeMassar:"<<setw(12)<<codeMassar<<endl;
        adherent.close();
        cout<<"\nl'adherent est bien ajoute";
        }
        else{
            cout<<"cette adherent existe deja dans la liste";
        }
}

bool Adherent::existeAdherent(string codeMassar){
    ifstream fichier("adherent.txt");
    if(fichier){
        string ligne;
        while(getline(fichier, ligne)){
            if(ligne.find(codeMassar)!= string::npos){
                //adherent existe dans la liste
                return 0;
                break;
            }
        }
    }
    return 1;
}

void Adherent::supprimerAdherent(string codeM){
    if(existeAdherent(codeM)==0){
        ifstream f1("adherent.txt");
        ofstream f2;
        string ligne;
        while(getline(f1,ligne)){
            if(ligne.find(codeM)==std::string::npos){
                f2.open("temp.txt",ofstream::out | ofstream::app);
                f2<<ligne<<endl;
                f2.close();
            }
        }
        f1.close();
        remove("adherent.txt");
        rename("temp.txt","adherent.txt");
        cout<<"\nl'adherent est bien supprime";
    }
}

void Adherent::afficherAdherent(){
    int nb=0;
    string ligne;
    ifstream adherent("adherent.txt");
    while(getline(adherent,ligne)){
        ++nb;
        cout<<"eleve N°"<<setw(5)<<nb<<": "<<ligne<<endl;
    }
    adherent.close();
    cout<<"\n------ le nombre des eleves inscrit est : "<<nb<<" ------\n";
}

Adherent::~Adherent(){
    //Destructeur de lAdherent
}
