#ifndef TRADING_H
#define TRADING_H
#include <QString>
#include <QDate>
#include <QStringList>
#include <QFile>
#include <QDebug>
#include<cmath>

using namespace std;
/* *Class Trading Exception: Contain the error message of the application
 */
class TradingException {
public:
    TradingException(const QString& message) :info(message) {}
    QString getInfo() const { return info; }
private:
    QString info;
};
/*-------------------------------------------------------- Partie Devises ----------------------------------------------------*/

/* * Class Devise: Contains the 3-letter code, the currency and zone of a Currency
 */
class Devise {
    QString code;
    QString monnaie, zone;
    Devise(const QString& code, const QString& monnaie, const QString& zone = "");
    ~Devise() = default;
    friend class DevisesManager;
public:
    QString getCode() const { return code; }
    const QString& getMonnaie() const { return monnaie; }
    const QString& getZoneGeographique() const { return zone; }
};

/* * Class PaireDevises: contains info of a pair of currency:
 * - base, contrepartie are the currecies of the pair
 * - nom: name of the pair
 * The constructur and destructor are private => can only created by DevisesManager
 */
class PaireDevises {
    const Devise* base;
    const Devise* contrepartie;
    QString surnom;
    PaireDevises(const Devise& base, const Devise& contrepartie, const QString& surnom = "");
    ~PaireDevises() = default;
    friend class DevisesManager;
public:
    const Devise& getBase() const { return *base; }
    const Devise& getContrepartie() const { return *contrepartie; }
    const QString& getSurnom() const { return surnom; }
    QString toString() const;
};

/* * Class DevisesManager: container of Devise and PaireDevises, applies Singleton Pattern
 * - it contains an array of pointer to Devise objects and an array of pointer to PaireDevises objects
 */
class DevisesManager {
    Devise** devises = nullptr;                 // tableau de pointeurs sur objets Devise
    unsigned int nbDevises = 0;
    unsigned int nbMaxDevises = 0;
    mutable PaireDevises** paires = nullptr;    // tableau de pointeurs sur objets PaireDevises
    mutable unsigned int nbPaires = 0;
    mutable unsigned int nbMaxPaires = 0;
    // empêcher la duplication par recopie ou affectation
    DevisesManager(const DevisesManager& deviseManager) = delete;
    DevisesManager& operator=(const DevisesManager& deviseManager) = delete;
    DevisesManager() {}
    ~DevisesManager();
    struct Handler {
        DevisesManager* instance = nullptr;
        ~Handler() { delete instance; }
    };
    static Handler handler;
public:
    static DevisesManager& getManager() {
        if (handler.instance == nullptr)
            handler.instance = new DevisesManager;
        return *handler.instance;
    }
    static void libererManager() {
        delete handler.instance;  handler.instance = nullptr;
    }
    const Devise& creationDevise(const QString& code, const QString& monnaie, const QString& zone);
    const Devise& getDevise(const QString& code)const;
    const PaireDevises& getPaireDevises(const QString & code1, const QString & code2) const;
};



/*------------------------------------------------ Partie EvolutionCours --------------------------------------------*/

/* * Class CoursOHLCV: contains open price, high price, low price, close price and the trading volume of a date
 */
class CoursOHLCV {
    double open = 0, high = 0, low = 0, close = 0;
    unsigned int volume = 0;
    QDate date;
public:
    CoursOHLCV() {}
    CoursOHLCV(double open, double high, double low, double close, unsigned int volume, const QDate& date);
    double getOpen() const { return open; }
    double getHigh() const { return high; }
    double getLow() const { return low; }
    double getClose() const { return close; }
    unsigned getVolume() const {return volume;}
    void setCours(double open, double high, double low, double close);
    void setVolume(unsigned int volume) {this->volume = volume;}
    QDate getDate() const { return date; }
    void setDate(const QDate& d) { date=d; }
};

/* *Class ListEvolutionCours: contains a list of csv file name that can used to charge to EvolutionCours
 */
class ListEvolutionCours {
    QStringList filenames;
    int nbFiles;
public:
    ListEvolutionCours(QStringList list) {filenames = list; nbFiles = list.length();}
    ~ListEvolutionCours() = default;
    void addFile(QString file) {filenames<<file; nbFiles++;}
};

class IndicateurCollection;     //forward declaration of IndicateurCollection

/* * Class EvolutionCours: an array of pointer to CoursOHLCV, => the evolution cours of a PaireDevises during a time period
 * - it can be created by charging a csv file
 */
class EvolutionCours {
    const PaireDevises* paire;
    IndicateurCollection* indicateurCollection;
    QString filen;
    CoursOHLCV* cours = nullptr;
    unsigned int nbCours = 0;
    unsigned int nbMaxCours = 0;
public:
    EvolutionCours(const PaireDevises& paire);
    EvolutionCours(const PaireDevises& pair, QString filename); //charger depuis fichier csv
    ~EvolutionCours();
    EvolutionCours(const EvolutionCours& evolutionCours);

    void addCours(double open, double high, double low, double close, unsigned int volume, const QDate& date);  
    EvolutionCours& operator=(const EvolutionCours& evolutionCours);
    unsigned int getNbCours() const { return nbCours; }
    const PaireDevises* getPaireDevises() const { return paire; }
    IndicateurCollection* getCollection() const {return indicateurCollection;}
    const QString& getNomFichier() const {return filen;}
    using iterator = CoursOHLCV*;
    iterator begin() { return iterator(cours); }
    iterator end() { return iterator(cours + nbCours); }
    using const_iterator = const CoursOHLCV*;
    const_iterator cbegin() const { return cours; }
    const_iterator cend() const { return cours + nbCours; }
    int saveFile();
};


/*-------------------------------------------------- Partie Indicateur ------------------------------------------------------------*/
//Information de Indicateurs: (https://stockcharts.com/school/doku.php?id=chart_school:technical_indicators:introduction_to_technical_indicators_and_oscillators#momentum_oscillators)


/* * Class Indiceindicateur: stocks every day data of an Indicateur
 * has a attribute donnee and a date
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

/* * Indicateur Class: abstract base class of every Indicateur
 * has a name and associates with an evolutionCours
 * it contans an array of IndiceIndicateur
 * The constructor and destrcutor is protected therefore can only be used by Inherited classes or IndicateurCollection
 * Each Indicateur is created with an empty array of Indiceindicateur, the array is generate after the call of method generateIndice() or setParameters()
 */
class Indicateur {
    friend class IndicateurCollection;
protected:
    QString nom;
    EvolutionCours* evolutionCours;
    IndiceIndicateur* indices = nullptr;  //array de IndiceIndicateur
    unsigned int nbIndicateur;
    unsigned int nbMaxIndicateur;
    Indicateur(EvolutionCours* evolutionCours, QString nom = "unnamed indicator"); //peut instancier que des classes dérivé
    Indicateur() = delete;
    virtual ~Indicateur() {delete[] indices;}
public:
    //pure virtual function for abstract class
    virtual void generateIndice() = 0;          //where array of Indices is generated
    using iterator = IndiceIndicateur*;
    using const_iterator = const IndiceIndicateur*;
    iterator begin(){return indices;}
    iterator end(){return indices + nbIndicateur;}
    const_iterator cbegin() const {return indices;}
    const_iterator cend() const {return indices+ nbIndicateur;}
    IndiceIndicateur* searchIndice(CoursOHLCV* cours);
    virtual void setParameters(QMap<QString, QVariant> parameters) = 0;         //encapsulate parameters inside an QMap object and pass it as argument
    virtual QMap<QString, QVariant> getParameters() const = 0;
};

/* * class EMA: EMA indicator, derived class of Indicateur
 * Info on EMA - https://www.investopedia.com/ask/answers/122314/what-exponential-moving-average-ema-formula-and-how-ema-calculated.asp
 * The constructor and destrcutor is privated therefore can only be used by MACD class or IndicateurCollection
 * EMA have only one parameter: period(unsigned int)
 */
class EMA : public Indicateur{
    friend class IndicateurCollection;     //can only created by IndicateurCollection
    friend class MACD;
private:
    unsigned int period;
    EMA(EvolutionCours* evolutionCours, unsigned int period = 10) : Indicateur(evolutionCours, "EMA"), period(period) {}      //create instance with an empty array of indices
public:
    void generateIndice();        //where array of indice is really instanciate
    void setParameters(QMap<QString, QVariant> parameters);
    QMap<QString, QVariant> getParameters() const;
};

/* * Class RSI: RSI indicator, derived class of Indicateur
 * information on RSI - https://stockcharts.com/school/doku.php?id=chart_school:technical_indicators:relative_strength_index_rsi
 * The constructor and destrcutor is privated therefore can only be created and destroyed by IndicateurCollection
 * Parameters of RSI: lookbackPeriod(unsigned int), overboughtBound(double), oversoldBound(double)
 */
class RSI : public Indicateur {
    friend class IndicateurCollection;     //can only created by IndicateurCollection
private:
    unsigned int lookbackPeriod;
    double overboughtBound, oversoldBound;
    RSI(EvolutionCours* evolutionCours, unsigned int lookbackPeriod = 14, double overboughtBound= 80, double oversoldBound= 20) :
        Indicateur(evolutionCours, "RSI"), lookbackPeriod(lookbackPeriod), overboughtBound(overboughtBound), oversoldBound(oversoldBound) {}      //create instance with an empty array of indices
public:
    void generateIndice();
    void setOverboughtBound(double overboughtBound=80) {this->overboughtBound = overboughtBound;}
    void setOversoldBound(double oversoldBound=20) {this->oversoldBound = oversoldBound;}
    void setLookbackPeriod(unsigned int lookbackPeriod=14);
    void setParameters(QMap<QString, QVariant> parameters);
    QMap<QString, QVariant> getParameters() const;
};


/* * Class MACD: MACD indicator, derived class of Indicateur
 * information on MACD - https://stockcharts.com/school/doku.php?id=chart_school:technical_indicators:moving_average_convergence_divergence_macd
 * The constructor and destrcutor is privated therefore can only be created and destroyed by IndicateurCollection
 * Parameters of RSI: longPeriod(unsigned int), shortPeriod(unsigned int), signalPeriod(unsigned int)
 */
class MACD : public Indicateur {
    friend class IndicateurCollection;     //can only created by IndicateurCollection
private:
    unsigned int longPeriod;
    unsigned int shortPeriod;
    unsigned int signalPeriod;
    IndiceIndicateur* signalLine = nullptr;
    IndiceIndicateur* histogram = nullptr;
    //create instance with an empty array of indices
    MACD(EvolutionCours* evolutionCours, unsigned int shortPeriod=12, unsigned int longPeriod=26, unsigned int signalPeriod=9) : Indicateur(evolutionCours, "MACD") {
        if(longPeriod < shortPeriod || longPeriod < signalPeriod) throw TradingException("MACD: long period doit etre le plus grand");
        this->longPeriod = longPeriod;  this->shortPeriod = shortPeriod;    this->signalPeriod = signalPeriod;
    }
public:
    void generateIndice();
    void setParameters(QMap<QString, QVariant> parameters);
    QMap<QString, QVariant> getParameters() const;
};

/* * Class IndicateurCollection: Collection of Indicateur, it contains a hash table of pointer to Indicateur object
 * Each IndicateurCollection belongs to a EvolutionCours, it contains all Indicateurs relative to this EvolutionCours
 * It instanciates empty indicateurs, when is used, an Indicateur is official instanciated with an array of index after the all parameters is set
 * An old Indicateur can be access from the collection to save the compute time
 */
class IndicateurCollection {
    friend class EvolutionCours;        //can only be created and deleted by EvolutionCours
    QHash<QString, Indicateur*> indicateurDictionary;
    IndicateurCollection(EvolutionCours* evolutionCours);
    ~IndicateurCollection();
public:
    Indicateur* getIndicateur(QString nom);
};
#endif // TRADING_H
