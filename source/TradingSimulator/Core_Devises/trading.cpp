#include "trading.h"
/* Implement Trading
 */

/*----------------------------------------------- Methodes de classe Devise -------------------------------------------------*/
Devise::Devise(const QString& code, const QString& monnaie, const QString& zone) :
    monnaie(monnaie), zone(zone) {
    if (code.size() != 3) throw TradingException("code devise incorrect");
    for (unsigned int i = 0; i < 3; i++) {
        if (code[i] <= 'A' || code[i] >= 'Z') throw TradingException("code devise incorrect");
    }
    this->code=code;
}

/*----------------------------------------------- Methodes de classe PaireDevises -------------------------------------------*/
PaireDevises::PaireDevises(const Devise& base, const Devise& contrepartie, const QString& surnom) : base(&base), contrepartie(&contrepartie), surnom(surnom) {}

QString PaireDevises::toString() const {
    QString string;
    string = getBase().getCode()+"/"+getContrepartie().getCode();
    if (getSurnom()!="") string+="("+getSurnom()+")";
    return string;
}

/*------------------------------------------------ Methodes de classe DevisesManager ---------------------------------------------*/
Devise* DevisesManager::creationDevise(const QString& code, const QString& monnaie, const QString& zone) {
    if (nbDevises == nbMaxDevises) {
        // agrandissement tableau
        Devise** newTable = new Devise*[nbMaxDevises + 10];
        for (unsigned int i = 0; i < nbDevises; i++) newTable[i] = devises[i];
        // mise à jour des attributs
        Devise** old = devises;
        nbMaxDevises += 10;
        devises = newTable;
        delete[] old;
    }
    // cération et ajout de la nouvelle devise...
    devises[nbDevises] = new Devise(code, monnaie, zone);
    return devises[nbDevises++];
}

Devise* DevisesManager::getDevise(const QString& code)const {
    for (unsigned int i = 0; i < nbDevises; i++)
        if (devises[i]->getCode() == code) return devises[i];
    throw TradingException("devise inexistante");
}

PaireDevises& DevisesManager::getPaireDevises(const QString & code1, const QString & code2) const {
    const Devise* devise1 = getDevise(code1);
    const Devise* devise2 = getDevise(code2);
    for (unsigned int i = 0; i < nbPaires; i++)
        if (paires[i]->getBase().getCode() == code1 && paires[i]->getContrepartie().getCode() == code2)
            return *paires[i];
    // si la paire de devises n'est pas trouvée, il faut la créer
    if (nbPaires == nbMaxPaires) { // agrandissement du tableau
        PaireDevises** newTable = new PaireDevises*[nbMaxPaires + 10];
        for (unsigned int i = 0; i < nbPaires; i++) newTable[i] = paires[i];
        PaireDevises** old = paires;
        nbMaxPaires += 10;
        paires = newTable;
        delete[] old;
    }
    paires[nbPaires] = new PaireDevises(*devise1, *devise2);
    return *paires[nbPaires++];
}

QStringList DevisesManager::getDeviseCodes() const {
    QStringList listeCodes;
    for (unsigned int i=0; i<nbDevises; i++) {
        listeCodes<<devises[i]->getCode();
    }
    return listeCodes;
}

DevisesManager::~DevisesManager() {
    for (unsigned int i = 0; i < nbPaires; i++) delete paires[i];
    for (unsigned int i = 0; i < nbDevises; i++) delete devises[i];
    delete[] paires; delete[] devises;
}

DevisesManager::Handler DevisesManager::handler= DevisesManager::Handler();


/*----------------------------------------------- Methodes de classe CoursOHLCV ---------------------------------------------*/
CoursOHLCV::CoursOHLCV(double open, double high, double low, double close, unsigned int volume, const QDate& date):date(date) {
    if (open < 0 || high < 0 || low < 0 || close < 0 || low > high) throw TradingException("Cours OHLCV incorrect");
        this->open = open;
        this->high = high;
        this->low = low;
        this->close = close;
        this->volume = volume;
}

void CoursOHLCV::setCours(double open, double high, double low, double close) {
    if (open < 0 || high < 0 || low < 0 || close < 0 || low > high) throw TradingException("Cours OHLCV incorrect");
        this->open = open;
        this->high = high;
        this->low = low;
        this->close = close;
}


bool CoursOHLCV::isSpinningTop() const {
    if(abs(open - close) <= 0.75*abs(high - low)) return true;
        return false;

}

bool CoursOHLCV::isDoji() const {
    if(isSpinningTop() && abs(close - open) <= 0.1 ) return true;
        return false;
}

bool CoursOHLCV::isDragonflyDoji() const {
    /*
     * Dragonfly Doji Formed when the opening and the closing prices are at the highest of the day.
     * If it has a longer lower shadow it signals a more bullish trend. When appearing at market bottoms it is considered to be a reversal signal.
     */
    if(isDoji() && open > high) return true;
        return false;
}

bool CoursOHLCV::isGraveStoneDoji() const {
    /*
     * Gravestone Doji Formed when the opening and closing prices are at the lowest of the day.
     * If it has a longer upper shadow it signals a bearish trend. When it appears at market top it is considered a reversal signal.
     */
    if (isDoji() && open < low) return true;
        return false;
}

bool CoursOHLCV::isHanngingMan() const {
    /*
     * Hanging Man A black or a white candlestick that consists of a small body near the high with a little or no upper shadow and a long lower tail.
     * The lower tail should be two or three times the height of the body. Considered a bearish pattern during an uptrend.
     */
    if ( ((high - open) < 0.1*(high - low) || (high - close) < 0.1*(high - low)) && abs(open - close) < (1/3)*(high - low)) return true;
        return false;
}

bool CoursOHLCV::isHammer() const {
    /*
     * Hammer A black or a white candlestick that consists of a small body near the high with a little or no upper shadow and a long lower tail.
     * Considered a bullish pattern during a downtrend.
     */
    if ( ((high - open) < 0.2*(high - low) || (high - close) < 0.2*(high - low)) &&  abs(open - close) < (1/2)*(high - low)) return true;
        return false;
}

bool CoursOHLCV::isInvertedHammer() const {
    /*
     * Inverted Hammer A black or a white candlestick in an upside-down hammer position.
     */
    if ( ((open - low) < 0.2*(high - low) || (close - low) < 0.2*(high - low)) &&  abs(open - close) < (1/2)*(high - low)) return true;
        return false;
}

bool CoursOHLCV::isInvertedBlackHammer() const {
    /*
     * Inverted Black Hammer A black body in an upside-down hammer position. Usually considered a bottom reversal signal.
     */
    if (isInvertedHammer() && (open > close)) return true;
        return false;
}

bool CoursOHLCV::isLongLowerShadow() const {
    /*
     * Long Lower Shadow A black or a white candlestick is formed with a lower tail that has a length of 2/3 or more of the total range of the candlestick.
     * Normally considered a bullish signal when it appears around price support levels.
     */
    if(open > close) {
        if(close - low > (2/3)*(high - low)) return true;
            return false;
    }
    else {
        if(open - low > (2/3)*(high - low)) return true;
            return false;
    }
}

bool CoursOHLCV::isLongUpperShadow() const {
    /*
     * Long Upper Shadow A black or a white candlestick with an upper shadow that has a length of 2/3 or more of the total range of the candlestick.
     * Normally considered a bearish signal when it appears around price resistance levels.
     */
    if(open > close) {
        if(high - open > (high - low)*(2/3)) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        if(high - close > (high - low)*(2/3)) {
            return true;
        }
        else {
            return false;
        }

    }
}

bool CoursOHLCV::isMarubozu() const {
    /*
     * Marubozu A long or a normal candlestick (black or white) with no shadow or tail.
     * The high and the lows represent the opening and the closing prices. Considered a continuation pattern.
     */
    if(abs(open - close) == abs(high - abs(low))) return true;
        return false;
}

bool CoursOHLCV::isShootingStar() const {
    /*
     * Shooting Star A black or a white candlestick that has a small body, a long upper shadow and a little or no lower tail. Considered a bearish pattern in an uptrend
     */
    double delta;
    if ( open > close) {
        delta = close - low;
    }
    else {
        delta = open - low;
    }
    if (isSpinningTop() && delta <= 0.05*abs(open - close) ) return true;
        return false;
}

bool CoursOHLCV::isShavenBottom() const {
    /*
     * Shaven Bottom A black or a white candlestick with no lower tail. [Compare with Inverted Hammer.]
     */
    if (open == low || close == low) return true;
        return false;
}

bool CoursOHLCV::isShavenHead() const {
    /*
     * Shaven Head A black or a white candlestick with no upper shadow. [Compared with hammer.]
     */
    if (open == high || close == high) return true;
        return false;
}

QString CoursOHLCV::forme() const {
    if (isSpinningTop()) {
        if (isDoji()) {
            if (isDragonflyDoji()) {
                return "Dragonfly Doji";
            }
            else if (isGraveStoneDoji()){
                return "Grave Stone Doji";
            }
            else {
                return "Doji";
            }
        }
        else if (isShootingStar()) {
            return "Shooting Star";
        }
        else {
            return "Spinning Top \n";
        }
    }
    if (isHanngingMan()) return "Hannging Man";
    if (isLongLowerShadow()) return "Long Lower Shadow";
    if (isLongUpperShadow()) return "Long Upper Shadow";
    if (isHammer()) {
        if (isInvertedHammer()) {
            if (isInvertedBlackHammer()) {
                return "Inverted Black Hammer";
            }
            else {
                return "Inverted Hammer";
            }
        }
        else {
            return "Hammer";
        }
     }

    if (isMarubozu()) return "Marubozu";
    if (isShavenBottom()) return "Shaven Bottom";
    if (isShavenHead()) return "Shaven Head";
    return "";
}

/*---------------------------------------------- Methodes de classe EvolutionCours --------------------------------------------*/
EvolutionCours::EvolutionCours(const PaireDevises& paire) :paire(&paire) { indicateurCollection = new IndicateurCollection(this);}

EvolutionCours::EvolutionCours(const PaireDevises &pair, QString filename) {
    paire = &pair;
    filen = filename;
    QDate date;
    double open, high, close, low;
    unsigned int volume;
    QFile file(filen);
    QStringList wordlist;
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << file.errorString();
        }
        QString line = file.readLine();            //avoid legendre
        while (!file.atEnd()) {
            line = file.readLine();
            wordlist = line.split(',');
            //qDebug() << wordlist;
            date = QDate::fromString(wordlist.at(0), "yyyy-MM-dd");
            //qDebug() << date.toString();
            open = wordlist.at(1).toDouble();
            high = wordlist.at(2).toDouble();
            low = wordlist.at(3).toDouble();
            close = wordlist.at(4).toDouble();
            volume = static_cast<unsigned>(wordlist.at(6).toInt());
            addCours(open, high, low, close, volume, date);
        }
        file.close();
        indicateurCollection = new IndicateurCollection(this);  //initalize collection
}

void EvolutionCours::addCours(double open, double high, double low, double close, unsigned int volume, const QDate& date) {
    if (nbMaxCours == nbCours) { // agrandissement du tableau
        CoursOHLCV* newTable = new CoursOHLCV[nbMaxCours + 100];
        for (unsigned int i = 0; i < nbCours; i++) newTable[i] = cours[i];
        // mise à jour des attributs
        CoursOHLCV* old = cours;
        cours = newTable;
        nbMaxCours += 100;
        delete[] old; // destruction de l'ancien tableau
    }
    // ajout du cours
    cours[nbCours].setCours(open, high, low, close);
    cours[nbCours].setVolume(volume);
    cours[nbCours].setDate(date);
    qDebug() << open <<" " <<high<< " "<< low <<" "<<close<<" "<<volume<<date.toString("yyyy-MM-dd");
    nbCours++;
}

EvolutionCours::~EvolutionCours() {
    delete[] cours;
}

EvolutionCours::EvolutionCours(const EvolutionCours& evolutionCours) :
    paire(evolutionCours.paire),
    cours(new CoursOHLCV[evolutionCours.nbCours]),
    nbCours(evolutionCours.nbCours),
    nbMaxCours(evolutionCours.nbCours) {
    for (unsigned int i = 0; i < nbCours; i++) cours[i] = evolutionCours.cours[i];
}

EvolutionCours& EvolutionCours::operator=(const EvolutionCours& evolutionCours) {
    if (this != &evolutionCours) { // se protéger de l'ato-affectation
        paire = evolutionCours.paire;
        nbCours = 0;
        for (unsigned int i = 0; i < evolutionCours.nbCours; i++)
            addCours(evolutionCours.cours[i].getOpen(), evolutionCours.cours[i].getHigh(),evolutionCours.cours[i].getLow(), evolutionCours.cours[i].getClose(), evolutionCours.cours[i].getVolume(), evolutionCours.cours[i].getDate());
    }
    return *this;
}

EvolutionCours::iterator EvolutionCours::searchCours(QDate date) {
        iterator coursIterator = begin();
        while(coursIterator && coursIterator != end()) {
            if(coursIterator->getDate() >= date) {
                return coursIterator;
            }
            coursIterator++;
        }
        return nullptr;
}

int EvolutionCours::saveFile() {
    QFile file(filen);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << file.errorString();
        return 1;
    }
    for(unsigned int i=0; i<nbCours; i++) {
        QStringList line;
        line << QString::number(cours[i].getOpen());
        line << QString::number(cours[i].getHigh());
        line << QString::number(cours[i].getLow());
        line << QString::number(cours[i].getClose());
        line << QString::number(cours[i].getVolume());
        line << cours[i].getDate().toString("yyyy,M,d\n");

        /*
         * date = QDate::fromString(wordlist.at(0), "yyyy-MM-dd");
            //qDebug() << date.toString();
            open = wordlist.at(1).toDouble();
            high = wordlist.at(2).toDouble();
            low = wordlist.at(3).toDouble();
            close = wordlist.at(4).toDouble();
            volume = wordlist.at(6).toInt();
            */
        file.write(line.join(',').toLocal8Bit());
    }
    return 0;
}
