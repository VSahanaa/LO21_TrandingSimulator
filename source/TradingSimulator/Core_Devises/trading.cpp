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

QString PaireDevises::toString() const{
    QString string;
    string = getBase().getCode()+"/"+getContrepartie().getCode();
    if (getSurnom()!="") string+="("+getSurnom()+")";
    return string;
}

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
        while (!file.atEnd()) {
            QString line = file.readLine();
            wordlist = line.split(',');
            //qDebug() << wordlist;
            date = QDate::fromString(wordlist.at(0), "yyyy-MM-dd");
            //qDebug() << date.toString();
            open = wordlist.at(1).toDouble();
            high = wordlist.at(2).toDouble();
            low = wordlist.at(3).toDouble();
            close = wordlist.at(4).toDouble();
            volume = wordlist.at(6).toInt();
            addCours(open, high, low, close, static_cast<unsigned>(volume), date);
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
    nbCours++;
}

EvolutionCours::~EvolutionCours() {
    delete[] cours;
}

EvolutionCours::EvolutionCours(const EvolutionCours& evolutionCours) :
    paire(evolutionCours.paire),
    cours(new CoursOHLCV[evolutionCours.nbCours]),
    nbCours(evolutionCours.nbCours),
    nbMaxCours(evolutionCours.nbCours)
{
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

/*------------------------------------------------ Methodes de classe DevisesManager ---------------------------------------------*/
const Devise& DevisesManager::creationDevise(const QString& code, const QString& monnaie, const QString& zone) {
    if (nbDevises == nbMaxDevises) { // agrandissement tableau
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
    return *devises[nbDevises++];
}

const Devise& DevisesManager::getDevise(const QString& code)const {
    for (unsigned int i = 0; i < nbDevises; i++)
        if (devises[i]->getCode() == code) return *devises[i];
    throw TradingException("devise inexistante");
}

const PaireDevises& DevisesManager::getPaireDevises(const QString & code1, const QString & code2) const {
    const Devise& devise1 = getDevise(code1);
    const Devise& devise2 = getDevise(code2);
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
    paires[nbPaires] = new PaireDevises(devise1, devise2);
    return *paires[nbPaires++];
}

DevisesManager::~DevisesManager() {
    for (unsigned int i = 0; i < nbPaires; i++) delete paires[i];
    for (unsigned int i = 0; i < nbDevises; i++) delete devises[i];
    delete[] paires; delete[] devises;
}

DevisesManager::Handler DevisesManager::handler= DevisesManager::Handler();
