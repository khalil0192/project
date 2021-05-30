#include <iostream>
#include "emprunt.h"
#include <string>
#include <fstream>
#include <iomanip>      // std::setw
using namespace std;

Emprunt::Emprunt(){
    //Constructeurs d'Emprunt
}

void Emprunt::faireEmprunt(std::string codeM,std::string isbn){
    ofstream emprunt;
    emprunt.open ("emprunt.txt", ofstream::out | ofstream::app);
    if(liv.existeLivre(isbn)==0 && adh.existeAdherent(codeM)==0){
        emprunt<<"|ISBN:"<<setw(30)<<isbn<<"|code massar:"<<setw(30)<<codeM<<"|date d'emprunt:"<<setw(30)<<__DATE__<<endl;
        emprunt.close();
        liv.supprimerLivre(isbn,"1");
    }
}

void Emprunt::finaliserEmprunt(string codeM,string isbn){
    string titre,auteur,edition;

    //supprimer l'emprunt dans le file des emprunt
    ifstream emprunt("emprunt.txt");
    ofstream empEE;
    string ligne;
    while(getline(emprunt,ligne)){
        if(ligne.find(codeM)==string::npos && ligne.find(isbn)==string::npos){
            empEE.open("tempEE.txt",ofstream::out | ofstream::app);
            empEE<<ligne<<endl;
            empEE.close();
        }
    }
    emprunt.close();
    remove("emprunt.txt");
    rename("tempEE.txt","emprunt.txt");

    //remplir les infos de livre d'après le stock_livre
    ifstream stock("stock_livre.txt");
    string line;
    while(getline(stock,line)){
        if(line.find(codeM)!=string::npos && line.find(isbn)!=string::npos){
            titre=line.substr(7,30);
            auteur=line.substr(45,30);
            edition=line.substr(120,4);
            break;
        }
    }
    stock.close();

    //return le livre au fichier livre
    if(liv.existeLivre(isbn)==1){
        ofstream livre;
        livre.open ("livre.txt", ofstream::out | ofstream::app);
        livre<<"|titre:"<<setw(30)<<titre<<"|auteur:"<<setw(30)<<auteur<<"|ISBN:"<<setw(30)<<isbn<<"|edition:"<<setw(4)<<edition<<"|compteur:"<<setw(4)<<1<<endl;
        livre.close();
        }
    else{
        ifstream f1("livre.txt");
        ofstream f2;
        string ligne;
        while(getline(f1,ligne)){
            if(ligne.find(isbn)==string::npos){
                f2.open("tempL.txt",ofstream::out | ofstream::app);
                f2<<ligne<<endl;
                f2.close();
            }
            else{
                f2.open("tempL.txt",ofstream::out | ofstream::app);
                f2<<"|titre:"<<setw(30)<<titre<<"|auteur:"<<setw(30)<<auteur<<"|ISBN:"<<setw(30)<<isbn<<"|edition:"<<setw(4)<<edition<<"|compteur:"<<setw(4)<<stoi(ligne.substr(134,138))+1<<endl;
                f2.close();
            }
        }
        f1.close();
        remove("livre.txt");
        rename("tempL.txt","livre.txt");
    }
}

bool Emprunt::dejaReserver(std::string isbn){
    ifstream fichier("reserve.txt");
    if(fichier){
        string ligne;
        while(getline(fichier,ligne)){
            if(ligne.find(isbn)!= string::npos){
                //adherent existe dans la liste
                return 0;
                break;
            }
        }
    }
    return 1;
}

void Emprunt::faireReservation(string codeM,string isbn){
    ofstream reserve;
    reserve.open ("reserve.txt", ofstream::out | ofstream::app);
    if(liv.existeLivre(isbn)==0 && adh.existeAdherent(codeM)==0 && dejaReserver(isbn)==1){
        reserve<<"|ISBN:"<<setw(30)<<isbn<<"|code massar:"<<setw(30)<<codeM<<"|date de reservation:"<<setw(30)<<__DATE__<<endl;
        reserve.close();
    }
}

void Emprunt::annulerReservation(string codeM,string isbn){
    ifstream f1("reserve.txt");
    ofstream f2;
    string ligne;
    while(getline(f1,ligne)){
        if(ligne.find(isbn)==string::npos){
            f2.open("tempRR.txt",ofstream::out | ofstream::app);
            f2<<ligne<<endl;
            f2.close();
        }
    }
    f1.close();
    remove("reserve.txt");
    rename("tempRR.txt","reserve.txt");
}

void Emprunt::afficheEmprunt(){
    cout<<"\n                la liste de tous les livres empruntes\n";
    int nb=0;
    string ligne;
    ifstream emprunt("emprunt.txt");
    if(emprunt){
        while(getline(emprunt,ligne)){
            ++nb;
            cout<<"|."<<nb<<": "<<ligne<<endl;
        }
        emprunt.close();
        cout<<"\n------ le nombre des livres empruntes est : "<<nb<<" ------\n";
    }
}

void Emprunt::afficheReserve(){
    cout<<"\n                la liste de tous les livres reserves\n";
    int nb=0;
    string ligne;
    ifstream reserve("reserve.txt");
    if(reserve){
        while(getline(reserve,ligne)){
            ++nb;
            cout<<"|."<<nb<<": "<<ligne<<endl;
        }
        reserve.close();
        cout<<"\n------ le nombre des livres reserves est : "<<nb<<" ------\n";
    }
}

void Emprunt::afficheStock(){
    cout<<"\n------------------------la liste de tous les livres qu'on dans cette bibliotheque---------------------\n\n";
    int nb=0,nbs=0;
    string ligne;
    ifstream stock_livre("stock_livre.txt");
    if(stock_livre){
        while(getline(stock_livre,ligne)){
            ++nb;
            cout<<"|."<<nb<<": "<<ligne<<endl;
            nbs+=stoi(ligne.substr(134,4));
        }
        stock_livre.close();
        cout<<"\n------ le nombre des livres dans cette bibliotheque est : "<<nbs<<" ------\n";
    }
}


Emprunt::~Emprunt(){
    //Destructeur d'Emprunt
}
