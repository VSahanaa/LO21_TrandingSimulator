#ifndef INDICATEUR_H
#define INDICATEUR_H
#include <QString>
#include "trading.h"
/*Information de Indicateurs
 * (https://stockcharts.com/school/doku.php?id=chart_school:technical_indicators:introduction_to_technical_indicators_and_oscillators#momentum_oscillators)
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

//classe base des indicateur
class Indicateur {
protected:
	EvolutionCours* evolutionCours;
    QString nom;
    IndiceIndicateur* indices = nullptr;  //array de IndiceIndicateur
    unsigned int nbIndicateur;
    unsigned int nbMaxIndicateur;
    Indicateur(EvolutionCours* evolutionCours, QString nom);    //peut instancier que des classes dérivé
public:
    Indicateur() = delete;
    virtual ~Indicateur(){delete[] indices;}
    virtual void generateIndice() = 0;          //pure virtual function for abstract class
    using iterator = IndiceIndicateur*;
    using const_iterator = const IndiceIndicateur*;
    iterator begin(){return indices;}
    iterator end(){return indices + nbIndicateur;}
    const_iterator cbegin() const {return indices;}
    const_iterator cend() const {return indices+ nbIndicateur;}
    IndiceIndicateur* searchIndice(CoursOHLCV* cours);
};

class IndicateurFactory {
private:
    static IndicateurFactory* instance; //singleton
    EvolutionCours* evolutionCours;
    QHash<QString, Indicateur*> indicateurDictionary;

    IndicateurFactory(EvolutionCours* evolutionCours);
    ~IndicateurFactory() { indicateurDictionary.clear();}
    IndicateurFactory(IndicateurFactory*) = delete;
    IndicateurFactory& operator=(IndicateurFactory*) = delete;

public:
    static IndicateurFactory* getIndicateurFactory(EvolutionCours* evolutionCours){
        if (instance == nullptr) {
            instance = new IndicateurFactory(evolutionCours);
        }
        else if (instance->evolutionCours != evolutionCours) {
            //create new factory
            IndicateurFactory::libererFactory();
            instance = new IndicateurFactory(evolutionCours);
        }
        return instance;
    }

    static void libererFactory() {
        delete instance;
        instance = nullptr;
    }

    Indicateur* getIndicateur(QString nom); //????????
};

/*-----------------------------------------------------------------Derived classes of Indicateur---------------------------------------------------*/
class EMA : public Indicateur{
    friend class IndicateurFactory;     //can only created by IndicateurFactory
    friend class MACD;
private:
    unsigned int period;
    EMA(EvolutionCours* evolutionCours, unsigned int period = 10) : Indicateur(evolutionCours, "EMA"), period(period) {}      //create instance with an empty array of indices
public:
    void generateIndice();        //where array of indice is really instanciate
    void setPeriod(unsigned int period=10) {
        //refresh array of indice
        this->period = period;
        generateIndice();
    }
};


class RSI : public Indicateur {
    friend class IndicateurFactory;     //can only created by IndicateurFactory
private:
    unsigned int lookbackPeriod;
    double overboughtBound, oversoldBound;
    RSI(EvolutionCours* evolutionCours, unsigned int lookbackPeriod = 14, double overboughtBound= 70, double oversoldBound= 30) :
        Indicateur(evolutionCours, "RSI"), lookbackPeriod(lookbackPeriod), overboughtBound(overboughtBound), oversoldBound(oversoldBound) {}      //create instance with an empty array of indices
public:
    void generateIndice();
    void setOverboughtBound(double overboughtBound) {this->overboughtBound = overboughtBound;}
    void setOversoldBound(double oversoldBound) {this->oversoldBound = oversoldBound;}
};


class MACD : public Indicateur {
    friend class IndicateurFactory;     //can only created by IndicateurFactory
private:
    unsigned int longPeriod;
    unsigned int shortPeriod;
    unsigned int signalPeriod;
    IndiceIndicateur* signalLine;
    IndiceIndicateur* histogram;
    //create instance with an empty array of indices
    MACD(EvolutionCours* evolutionCours, unsigned int shortPeriod=12, unsigned int longPeriod=26, unsigned int signalPeriod=9) : Indicateur(evolutionCours, "MACD") {
        if(longPeriod < shortPeriod || longPeriod < signalPeriod) throw TradingException("MACD: long period doit etre le plus grand");
        this->longPeriod = longPeriod;  this->shortPeriod = shortPeriod;    this->signalPeriod = signalPeriod;
    }
public:
    void generateIndice();
};

#endif // INDICATEUR_H

