#ifndef INDICATEUR_H
#define INDICATEUR_H
#include <QString>
#include "trading.h"
/*Information de Indicateurs (https://stockcharts.com/school/doku.php?id=chart_school:technical_indicators:introduction_to_technical_indicators_and_oscillators#momentum_oscillators)
 */
class IndiceIndicateur {
private:
		double donnee;
        QDate  date;
public:
        IndiceIndicateur(){}
        double getIndice() const { return donnee;}
        QDate  getDate() const { return date;}
        void setIndice(double donnee) { this->donnee = donnee;}
        void setDate(QDate date) { this->date = date;}
        //for debugging
        QString toString() const {return date.toString() + " indicateur: " + QString::number(donnee);}
};

//classe abstrait des indicateur

class Indicateur {
protected:
	EvolutionCours* evolutionCours;
    QString nom;
    IndiceIndicateur* indices;  //array de IndiceIndicateur
    unsigned int nbIndicateur;
    unsigned int nbMaxIndicateur;
    Indicateur(EvolutionCours* evolutionCours, QString nom);    //peut utiliser que des classes dérivé
public:
    Indicateur() = delete;
    ~Indicateur(){delete[] indices;}
    using iterator = IndiceIndicateur*;
    using const_iterator = const IndiceIndicateur*;
    iterator begin(){return indices;}
    iterator end(){return indices + nbIndicateur;}
    const_iterator cbegin() const {return indices;}
    const_iterator cend() const {return indices+ nbIndicateur;}
    IndiceIndicateur* searchIndice(CoursOHLCV* cours);
};


class EMA : public Indicateur{
private:
    unsigned int period;
public:
    EMA(EvolutionCours* evolutionCours, unsigned period=10);
};


class RSI : public Indicateur {
private:
    unsigned int lookBackPeriod;
    double overboughtBound, oversoldBound;
public:
    RSI(EvolutionCours* evolutionCours, unsigned int lookbackPeriod = 14, double overboughtBound= 70, double oversoldBound= 30);
};


class MACD : public Indicateur {
private:
    unsigned int longPeriod;
    unsigned int shortPeriod;
    unsigned int signalPeriod;
    IndiceIndicateur* signalLine;
    IndiceIndicateur* histogram;
public:
    MACD(EvolutionCours* evolutionCours, unsigned int shortPeriod=12, unsigned int longPeriod=26, unsigned int signalPeriod=9);
};

/*
class IndicateurManage {
private:
	Indicateur* listeIndicateur;
	int nbIndicateur;
};
*/
#endif // INDICATEUR_H

