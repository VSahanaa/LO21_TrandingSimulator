#include "indicateur.h"
/*----------------------------------------------- Methodes de classe Indicateur -------------------------------------------------*/
Indicateur::Indicateur(EvolutionCours* evolutionCours, QString nom = "un named indicator"): nom(nom) {
    if (!evolutionCours) throw TradingException("Idicateur: evolutionCours est null");
        this->evolutionCours = evolutionCours;
    nbMaxIndicateur = evolutionCours->getNbCours();
    indices = new IndiceIndicateur[nbMaxIndicateur];
}

IndiceIndicateur* Indicateur::searchIndice(CoursOHLCV* cours) {
    QDate date = cours->getDate();
    iterator indiceIterator;
    for (indiceIterator = begin(); indiceIterator != end(); indiceIterator++) {
        if(indiceIterator->getDate() == date) break;
        if(indiceIterator->getDate() > date) return nullptr;
    }
    if (indiceIterator == end()) return nullptr;
    return indiceIterator;
}


/*----------------------------------------------- Methodes de classe EMA -------------------------------------------------*/
//information sur EMA (https://www.investopedia.com/ask/answers/122314/what-exponential-moving-average-ema-formula-and-how-ema-calculated.asp)

EMA::EMA(EvolutionCours* evolutionCours, QString nom, unsigned int period = 10) : Indicateur(evolutionCours, nom), period(period) {

    //EMA initial est SMA pour cette periode
    //il n'y a pas de SMA et EMA pendant la premiere periode
    double sum = 0;
    nbIndicateur = nbMaxIndicateur - period + 1;
    EvolutionCours::iterator coursIterator;

    //cacule premier SMA
    for(coursIterator = evolutionCours->begin(); coursIterator != evolutionCours->begin() + period; coursIterator++) {
        sum += coursIterator->getClose();
        nbIndicateur++;
    }

    iterator indiceIterator = begin();
    indiceIterator->setDate((coursIterator-1)->getDate());
    indiceIterator->setIndice(sum/period);       //premier SMA
    indiceIterator++;

 while(indiceIterator != end()) {
        indiceIterator->setDate(coursIterator->getDate());
        indiceIterator->setIndice((coursIterator->getClose()-(indiceIterator-1)->getIndice())*2/(period+1) + (indiceIterator-1)->getIndice());
        indiceIterator++;
        coursIterator++;
    }
}


/*----------------------------------------------- Methodes de classe RSI -------------------------------------------------*/
 //information sur RSI (https://stockcharts.com/school/doku.php?id=chart_school:technical_indicators:relative_strength_index_rsi)

RSI::RSI(EvolutionCours* evolutionCours, QString nom, unsigned int lookbackPeriod = 14, double overboughtBound= 70, double oversoldBound= 30)
    : Indicateur(evolutionCours, nom), lookBackPeriod(lookbackPeriod), overboughtBound(overboughtBound), oversoldBound(oversoldBound) {


    nbIndicateur = nbMaxIndicateur-lookbackPeriod;
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
    avgGain /= lookBackPeriod;
    avgLost /= lookBackPeriod;
    RS = avgGain/avgLost;

    //il n'y a pas d'indicateur RSI pendant le look back periode
    iterator indiceIterator = begin();
    indiceIterator->setDate((coursIterator-1)->getDate());
    indiceIterator->setIndice(100-100/(1+RS));
    indiceIterator++;

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
        indiceIterator++;
        coursIterator++;
	}
}



/*----------------------------------------------- Methodes de classe MACD -------------------------------------------------*/


MACD::MACD(EvolutionCours* evolutionCours, QString nom, unsigned int shortPeriod=12, unsigned int longPeriod=26, unsigned int signalPeriod=9) :Indicateur(evolutionCours, nom), longPeriod(longPeriod), shortPeriod(shortPeriod), signalPeriod(signalPeriod) {
    if(longPeriod < shortPeriod || longPeriod < signalPeriod) throw TradingException("MACD: long period doit etre le plus grand");
    signalLine = new IndiceIndicateur[nbMaxIndicateur];
    histogram = new IndiceIndicateur[nbMaxIndicateur];
    nbIndicateur = nbMaxIndicateur - longPeriod + 1;
    Indicateur* shortEMA = new EMA(evolutionCours, QString::number(shortPeriod)+ "-EMA", shortPeriod);
    Indicateur* longEMA = new EMA(evolutionCours, QString::number(longPeriod)+ "-EMA", longPeriod);
    Indicateur* signalEMA = new EMA(evolutionCours, QString::number(signalPeriod)+ "-EMA", signalPeriod);
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

        indiceIterator->setIndice(shortEMA_Iterator++->getIndice() - longEMA_Iterator->getIndice());
        signalLine_Iterator->setIndice(signalEMA_Iterator++->getIndice());
        histogram_Iterator++->setIndice(indiceIterator++->getIndice() - signalLine_Iterator++->getIndice());

        longEMA_Iterator++;

    }
    delete[] shortEMA;
    delete[] longEMA;
    delete[] signalEMA;
}

