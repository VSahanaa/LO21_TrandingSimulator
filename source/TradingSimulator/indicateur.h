#ifndef INDICATEUR_H
#define INDICATEUR_H
#include<iostream>
#include<string.h>
#include <QString>
#include "trading.h"

class IndiceIndicateur {
private:
		double donnee;
        QDate  date;
public:
        IndiceIndicateur(){}
        double getIndice() { return donnee;}
        QDate  getDate() { return date;}
        void setIndice(double donnee) { this->donnee = donnee;}
        void setDate(QDate date) { this->date = date;}
};

//classe abstrait des indicateur
class Indicateur {
protected:
	EvolutionCours* evolutionCours;
    QString nom;
    IndiceIndicateur* indices;  //array de IndiceIndicateur
    unsigned int nbIndicateur;
    unsigned int nbMaxIndicateur;
public:
    Indicateur(EvolutionCours* evolutionCours, QString nom = ""): evolutionCours(evolutionCours), nom(nom) {if (!evolutionCours) throw TradingException("Idicateur: evolutionCours est null");}
    ~Indicateur(){delete[] indices;}
    using iterator = IndiceIndicateur*;
    iterator begin(){return indices;}
    iterator end(){return indices + nbIndicateur;}
};


class EMA : public Indicateur{
    friend class MACD;
private:
    CoursOHLCV* startingPoint;
    CoursOHLCV* endPoint;
    unsigned int periode;
public:
    EMA(CoursOHLCV* startingPoint, CoursOHLCV* endPoint, EvolutionCours* evolutionCours, QString nom);
};


class RSI: public Indicateur {
private:
	int	parametre;
public:
	RSI(const int p, EvolutionCours* e, char* n);
	~RSI();
};





class MACD:public Indicateur {
private:
	int	longPeriode;
	int	shortPeriode;
public:
	MACD(const int longPeriode,const int shortPeriode, EvolutionCours* e,char* n);
	~MACD() ;
};

class IndicateurManage {
private:
	Indicateur* listeIndicateur;
	int nbIndicateur;
};
#endif // INDICATEUR_H

