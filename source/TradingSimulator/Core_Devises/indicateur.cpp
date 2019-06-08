#include "trading.h"
/* Implement Indicateurs
 */
/*----------------------------------------------- Methodes de classe Indicateur -------------------------------------------------*/
Indicateur::Indicateur(EvolutionCours* evolutionCours, QString nom): nom(nom) {
    if (!evolutionCours) throw TradingException("Idicateur: evolutionCours est null");
        this->evolutionCours = evolutionCours;
    nbIndicateur = 0;
}

IndiceIndicateur* Indicateur::searchIndice(CoursOHLCV* cours) {     //map indice Indicateur with CoursOHLCV
    QDate date = cours->getDate();
    iterator indiceIterator = begin();
    while(indiceIterator && indiceIterator->getDate() <= date) {
        if(indiceIterator->getDate() == date) return indiceIterator;
        indiceIterator++;
    }
    return nullptr;
}
/*----------------------------------------------- Methodes de classe EMA -------------------------------------------------*/
void EMA::generateIndice() {
    delete [] indices;
    nbMaxIndicateur = evolutionCours->getNbCours();
    indices = new IndiceIndicateur[nbMaxIndicateur];
    //EMA initial est SMA pour cette periode
    //il n'y a pas de SMA et EMA pendant la premiere periode
    double sum = 0;
    nbIndicateur = nbMaxIndicateur - period + 1;
    //qDebug() << nbMaxIndicateur <<" " << nbIndicateur;
    EvolutionCours::iterator coursIterator;
    //cacule premier SMA
    int i=0;
    for(coursIterator = evolutionCours->begin(); coursIterator != evolutionCours->begin() + period; coursIterator++) {
        //qDebug() << i++;
        sum += coursIterator->getClose();
    }

    iterator indiceIterator = begin();
    indiceIterator->setDate((coursIterator-1)->getDate());
    indiceIterator->setIndice(sum/period);       //premier SMA
    //qDebug() << indiceIterator->toString();
    indiceIterator++;

    while(indiceIterator != end()) {
        indiceIterator->setDate(coursIterator->getDate());
        indiceIterator->setIndice((coursIterator->getClose()-(indiceIterator-1)->getIndice())*2/(period+1) + (indiceIterator-1)->getIndice());
        //qDebug() << indiceIterator->toString();
        indiceIterator++;
        coursIterator++;
    }
}

void EMA::setParameters(QMap<QString, QVariant> parameters) {
    //refresh array of indice if period is changed or array of index is empty
    if (!parameters.contains("period") && !indices){
        generateIndice();
    }
    else if (this->period != static_cast<unsigned int>(parameters["period"].toInt()) || !indices) {
        this->period = static_cast<unsigned int>(parameters["period"].toInt());
        generateIndice();
    }
}

QMap<QString, QVariant> EMA::getParameters() const {
    QMap<QString, QVariant> parameters;
    parameters["period"] = period;
    return parameters;
}

/*----------------------------------------------- Methodes de classe RSI -------------------------------------------------*/
void RSI::generateIndice() {
    //set parameters
    nbMaxIndicateur = evolutionCours->getNbCours();
    nbIndicateur = nbMaxIndicateur - lookbackPeriod -1;
    delete [] indices;
    indices = new IndiceIndicateur[nbMaxIndicateur];

    double avgGain=0, avgLost=0, RS;
    EvolutionCours::iterator coursIterator;
    double e;
    for (coursIterator = evolutionCours->begin()+1; coursIterator != evolutionCours->begin()+lookbackPeriod+1; coursIterator++) {
        e = coursIterator->getClose() - (coursIterator-1)->getClose();
        if (e>0) {
            avgGain += e;
        }
        else {
            avgLost += -e;
        }
    }
    avgGain /= lookbackPeriod;
    avgLost /= lookbackPeriod;

    //il n'y a pas d'indicateur RSI pendant le look back periode
    iterator indiceIterator = begin();

    //element suivant
    while(indiceIterator != end()) {
        e = coursIterator->getClose() - (coursIterator-1)->getClose();
        if (e > 0) {
            avgGain = (avgGain*(lookbackPeriod-1) + e)/lookbackPeriod;
        }
        else {
            avgLost = (avgLost*(lookbackPeriod-1) - e)/lookbackPeriod;
        }
        RS = avgGain/avgLost;
        indiceIterator->setDate(coursIterator->getDate());
        indiceIterator->setIndice(100 - 100/(1+RS));
        //qDebug() << indiceIterator->toString();
        indiceIterator++;
        coursIterator++;
    }
}

void RSI::setLookbackPeriod(unsigned int lookbackPeriod) {
    //refresh array of indice if look back period is changed
    if(this->lookbackPeriod != lookbackPeriod || !indices) {
        this->lookbackPeriod = lookbackPeriod;
        generateIndice();
    }
}

void RSI::setParameters(QMap<QString, QVariant> parameters) {
    if (parameters.contains("overboughtBound")) setOverboughtBound(parameters["overboughtBound"].toDouble());
    if (parameters.contains("oversoldBound")) setOversoldBound(parameters["oversoldBound"].toDouble());
    if (parameters.contains("lookbackPeriod")) setLookbackPeriod(parameters["lookbackPeriod"].toInt());
}

QMap<QString, QVariant> RSI::getParameters() const {
    QMap<QString, QVariant> parameters;
    parameters["lookbackPeriod"] = lookbackPeriod;
    parameters["overboughtBound"] = overboughtBound;
    parameters["oversoldBound"] = oversoldBound;
    return parameters;
}

/*----------------------------------------------- Methodes de classe MACD -------------------------------------------------*/
void MACD::generateIndice() {
    delete[] signalLine;
    delete[] histogram;
    delete[] indices;
    nbMaxIndicateur = evolutionCours->getNbCours();
    //qDebug() << "nbCOurs" << evolutionCours->getNbCours();
    signalLine = new IndiceIndicateur[nbMaxIndicateur];
    histogram = new IndiceIndicateur[nbMaxIndicateur];
    indices = new IndiceIndicateur[nbMaxIndicateur];
    nbIndicateur = nbMaxIndicateur - longPeriod;

    EMA* shortEMA = new EMA(evolutionCours, shortPeriod);
    shortEMA->generateIndice();
    EMA* longEMA = new EMA(evolutionCours, longPeriod);
    longEMA ->generateIndice();
    EMA* signalEMA = new EMA(evolutionCours, signalPeriod);
    signalEMA->generateIndice();
    iterator shortEMA_Iterator, longEMA_Iterator, signalEMA_Iterator, indiceIterator, signalLine_Iterator, histogram_Iterator;

    longEMA_Iterator = longEMA->begin();
    shortEMA_Iterator = shortEMA->begin() + longPeriod - shortPeriod;
    signalEMA_Iterator = signalEMA->begin() + longPeriod - signalPeriod;
    indiceIterator = begin();
    signalLine_Iterator = signalLine;
    histogram_Iterator = histogram;
    while(longEMA_Iterator != longEMA->end()) {
        indiceIterator->setDate(longEMA_Iterator->getDate());
        signalLine_Iterator->setDate(longEMA_Iterator->getDate());
        histogram_Iterator->setDate(longEMA_Iterator->getDate());
        qDebug() <<"short EMA" << shortEMA_Iterator->toString();
        qDebug() <<"long EMA" <<longEMA_Iterator->toString();
        qDebug() <<"signal EMA" <<signalEMA_Iterator->toString();
        indiceIterator->setIndice(shortEMA_Iterator++->getIndice() - longEMA_Iterator++->getIndice());
        signalLine_Iterator->setIndice(signalEMA_Iterator++->getIndice());
        histogram_Iterator++->setIndice(indiceIterator++->getIndice() - signalLine_Iterator++->getIndice());
    }
    delete shortEMA;
    delete longEMA;
    delete signalEMA;
}

void MACD::setParameters(QMap<QString, QVariant> parameters) {   
    unsigned int old_longPeriod = longPeriod, old_shortPeriod = shortPeriod, old_signalPeriod = signalPeriod;
    if (parameters.contains("longPeriod") && static_cast<unsigned int>(parameters["longPeriod"].toInt()) != longPeriod)
        longPeriod = static_cast<unsigned int>(parameters["longPeriod"].toInt());

    if (parameters.contains("shortPeriod") && static_cast<unsigned int>(parameters["shortPeriod"].toInt()) != shortPeriod)
        shortPeriod = static_cast<unsigned int>(parameters["shortPeriod"].toInt());

    if (parameters.contains("signalPeriod") && static_cast<unsigned int>(parameters["signalPeriod"].toInt()) != signalPeriod)
        signalPeriod = static_cast<unsigned int>(parameters["signalPeriod"].toInt());

    if(longPeriod < shortPeriod || longPeriod<signalPeriod) {
        //roll back
        longPeriod = old_longPeriod;    shortPeriod= old_shortPeriod;    signalPeriod = old_signalPeriod;
        throw TradingException("MACD: long period doit etre le plus grand");
    }
    generateIndice();
}

QMap<QString, QVariant> MACD::getParameters() const {
    QMap<QString, QVariant> parameters;
    parameters["longPeriod"] = longPeriod;
    parameters["shortPeriod"] = shortPeriod;
    parameters["signalPeriod"] = signalPeriod;
    return parameters;
}

/*----------------------------------------------- Methode de classe IndicateurCollection -----------------------------------------------*/
IndicateurCollection::IndicateurCollection(EvolutionCours* evolutionCours) {
    indicateurDictionary.empty();
    //insert empty indicateur to the collection
    indicateurDictionary.insert("EMA", new EMA(evolutionCours));
    indicateurDictionary.insert("RSI", new RSI(evolutionCours));
    indicateurDictionary.insert("MACD", new MACD(evolutionCours));
}

IndicateurCollection::~IndicateurCollection() {
    foreach(Indicateur* indicateur, indicateurDictionary.values()) {
        delete indicateur;
    }
    indicateurDictionary.clear();
}

Indicateur* IndicateurCollection::getIndicateur(QString nom) {
    if (!indicateurDictionary.contains(nom)) throw TradingException("IndicateurCollection: collection not containing requested item");
    return indicateurDictionary[nom];
}

