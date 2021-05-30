#include <iostream>
#include "livre.h"
#include <string>
#include <fstream>
#include <iomanip>      // std::setw

using namespace std;

Livre::Livre(){
    //Constructeurs de livre
}

bool Livre::existeLivre(string isbn){
    ifstream fichier("livre.txt");
    if(fichier){
        string ligne;
        while(getline(fichier, ligne)){
            if(ligne.find(isbn)!= string::npos){
                //Livre existe dans la liste
                return 0;
                break;
            }
        }
    }
    return 1;
}

void Livre::ajouterLivre(){
    cout<<"\n----- veuillez saisir les infos de livre a ajouter -----\n";
    cout<<"titre: ";
    getline(cin,titre);
    cout<<"auteur: ";
    getline(cin,auteur);
    cout<<"ISBN: ";
    getline(cin,ISBN);
    cout<<"edition: ";
    getline(cin,edition);
    if(existeLivre(ISBN)==1){
        ofstream livre;
        ofstream stocklibre;
        livre.open ("livre.txt", ofstream::out | ofstream::app);
        livre<<"|titre:"<<setw(30)<<titre<<"|auteur:"<<setw(30)<<auteur<<"|ISBN:"<<setw(30)<<ISBN<<"|edition:"<<setw(4)<<edition<<"|compteur:"<<setw(4)<<1<<endl;
        livre.close();
        stocklibre.open ("stock_livre.txt", ofstream::out | ofstream::app);
        stocklibre<<"|titre:"<<setw(30)<<titre<<"|auteur:"<<setw(30)<<auteur<<"|ISBN:"<<setw(30)<<ISBN<<"|edition:"<<setw(4)<<edition<<"|compteur:"<<setw(4)<<1<<endl;
        stocklibre.close();
        }
        else{
            ifstream f1("livre.txt");
            ofstream f2;
            ofstream stock_livre;
            ofstream tempo;
            string ligne;
            while(getline(f1,ligne)){
                if(ligne.find(ISBN)==string::npos){
                    f2.open("tempL.txt",ofstream::out | ofstream::app);
                    f2<<ligne<<endl;
                    f2.close();

                    tempo.open("tempo.txt",ofstream::out | ofstream::app);
                    tempo<<ligne<<endl;
                    tempo.close();
                }
                else{
                    f2.open("tempL.txt",ofstream::out | ofstream::app);
                    f2<<"|titre:"<<setw(30)<<titre<<"|auteur:"<<setw(30)<<auteur<<"|ISBN:"<<setw(30)<<ISBN<<"|edition:"<<setw(4)<<edition<<"|compteur:"<<setw(4)<<stoi(ligne.substr(134,138))+1<<endl;
                    f2.close();

                    tempo.open("tempo.txt",ofstream::out | ofstream::app);
                    tempo<<"|titre:"<<setw(30)<<titre<<"|auteur:"<<setw(30)<<auteur<<"|ISBN:"<<setw(30)<<ISBN<<"|edition:"<<setw(4)<<edition<<"|compteur:"<<setw(4)<<stoi(ligne.substr(134,138))+1<<endl;
                    tempo.close();
                }
            }
            f1.close();
            remove("livre.txt");
            rename("tempL.txt","livre.txt");

            stock_livre.close();
            remove("stock_livre.txt");
            rename("tempo.txt","stock_livre.txt");
        }
}

void Livre::supprimerLivre(string isbn,string nb="tous"){
    if(existeLivre(isbn)==0){
        ifstream f1("livre.txt");
        ofstream f2;
        string ligne;
        while(getline(f1,ligne)){
            if(ligne.find(isbn)!=string::npos){
                if(nb=="tous" || stoi(nb)>=stoi(ligne.substr(134,4))){
                    //livre-supprimer
                }
                else{
                    f2.open("tempLL.txt",ofstream::out | ofstream::app);
                    f2<<ligne.substr(0,36)<<ligne.substr(37,37)<<ligne.substr(75,36)<<ligne.substr(111,13)<<"|compteur:"<<setw(4)<<stoi(ligne.substr(134,5))-1<<endl;
                    f2.close();
                }
            }else{
                f2.open("tempLL.txt",ofstream::out | ofstream::app);
                f2<<ligne<<endl;
                f2.close();
            }
        }
        f1.close();
        remove("livre.txt");
        rename("tempLL.txt","livre.txt");
        cout<<"\nlivre est bien supprime";
    }
}

Livre::~Livre(){
    //Destructeur de livre
}
