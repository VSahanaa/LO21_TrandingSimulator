#ifndef TRADING_H
#define TRADING_H

/**
 * \file 	trading.h
 * \brief 	Contient le noyau de l'application
 * 	
 * 	Contient les classes concernant les Devises : TradingException, Devise, PaireDevises, DevisesManager
 * 	Contient les classes concernant les Cours : coursOHLCV, ListEvolutionCours, EvolutionCours
 * 	Contient les classes concernant les Indicateurs : Indicateur, IndicateurCollection, IndiceIndicateur, EMA, MACD, RSI
 * 			
 */

#include <QString>
#include <QDate>
#include <QStringList>
#include <QFile>
#include <QDebug>
#include<cmath>

using namespace std;

class TradingException {
	/**
	* \class TradingException
	* \brief Contient le message d'erreur
	*/
public:
	//! constructor
	/** \param message :const QString&*/
    TradingException(const QString& message) :info(message) {}
	//! method getInfo ; retourne un QString : la valeur contenue dans l'attribut info 
    QString getInfo() const { return info; }
private:
    QString info; /**< info :Qstring contient l'information sur les erreurs */
};
/*-------------------------------------------------------- Partie Devises ----------------------------------------------------*/

class Devise {
	/**
	* \class Devise
	* \brief Représente une devise
	* attributs : code, monnaie, zone
	* methodes : getCode, getMonnaie, getZoneGeographique
	* amitiés : class DeviseManager
	* remarque : constructeur privé et destructeur privé
	*/
    QString code; /**< code :Qstring contient le code de la devise */
    QString monnaie; /**< monnaie :Qstring contient le nom de la monnaie concernée */
	QString zone; /**< zone :Qstring contient le nom de la zone géographique associée à la devise */
    //! constructor
	/** 
	* \param code :const QString&
	* \param monnaie :const QString&
	* \param zone :const QString&
	*/
	Devise(const QString& code, const QString& monnaie, const QString& zone = "");
	//! destructor
    ~Devise() = default;
    friend class DevisesManager; /**< declaration d'amitié : DevisesManager */
public:
	//! method getCode ; retourne QString : la valeur de l'attribut code
    QString getCode() const { return code; }
	//! method getMonnaie ; retourne QString : la valeur de l'attribut monnaie
    const QString& getMonnaie() const { return monnaie; }
	//! method getZoneGeographique ; retourne QString : la valeur de l'attribut zone
    const QString& getZoneGeographique() const { return zone; }
};

class PaireDevises {
	/**
	* \class PaireDevises
	* \brief Représente une paire de devise
	* attributs : base, contrepartie, surnom
	* methodes : getBase, getContrepartie, getSurnom
	* amitiés : class DeviseManager
	* remarque : constructeur privé et destructeur privé
	*/
    const Devise* base; /**< base : const Devise* pointe sur la devise de base */
    const Devise* contrepartie; /**< contrepartie : const Devise* pointe sur la devise de contrepartie */
    QString surnom; /**< surnom : Qstring contient le surnom de la paire */
    
	//! constructor
	/** 
	* \param base :const Devise&
	* \param contrepartie :const Devise&
	* \param surnom :const Qstring&
	*/
	PaireDevises(const Devise& base, const Devise& contrepartie, const QString& surnom = "");
    //! destructor
	~PaireDevises() = default;
    friend class DevisesManager;/**< declaration d'amitié : DevisesManager */
public:
	//! method getBase ; retourne const Devise& : la valeur de l'attribut base
    const Devise& getBase() const { return *base; }
	//! method getContrepartie ; retourne const Devise& : la valeur de l'attribut contrepartie
    const Devise& getContrepartie() const { return *contrepartie; }
    //! method getSurnom ; retourne const QString& : la valeur de l'attribut surnom
	const QString& getSurnom() const { return surnom; }
	//! method setSurnom ; retourne void
	/** 
	* \brief Permet de modifier le surnom
	* \param surnom :Qstring
	*/
    void setSurnom(QString surnom) {this->surnom = surnom;}
	//! method toString ; retourne Qstring : donne le nom de la paire sous forme de string
	/** 
	* \brief  renvoie <code>.<contrepartie>/<contrepartie>.<code> sous forme de string
	*/
    QString toString() const;
};


class DevisesManager {
	/**
	* \class DeviseManager
	* \brief DeviseManager est la classe qui permet de gérer les devises et les paires
	* attributs : devises, nbDevises, nbMaxDevises, paires, nbPaires, nbMaxPaires
	* attribut statique : handler
	* methodes : getDeviseCodes, creationDevise, getDevise, getPaireDevises
	* methodes statiques : getManager, libererManager
	* amitiés : class DeviseManager
	* remarque : duplication par recopie ou affectation supprimée, constructeur privé et destructeur privé
	*/
    Devise** devises = nullptr; /**< devise : Devise** représente un tableau de pointeurs qui pointent sur Devise de taille nbMaxDevises */
    unsigned int nbDevises = 0; /**< nbDevises : unsigned int représente le nombre d'éléments dans le tableau devises */
    unsigned int nbMaxDevises = 0 /**< nbMaxDevises : unsigned int représente le nombre d'éléments maximum que peut contenir le tableau devises */
    mutable PaireDevises** paires = nullptr; /**< paires : mutable PaireDevises** représente un tableau de pointeurs qui pointent sur PaireDevises de taille nbMaxPaires */
    mutable unsigned int nbPaires = 0; /**< nbPaires : mutable unsigned int représente le nombre d'éléments dans le tableau PaireDevises */
    mutable unsigned int nbMaxPaires = 0; /**< nbMaxPaires : unsigned int représente le nombre d'éléments dans le tableau paires */
    // empêcher la duplication par recopie ou affectation
    DevisesManager(const DevisesManager& deviseManager) = delete;
    DevisesManager& operator=(const DevisesManager& deviseManager) = delete;
	//! constructor
    DevisesManager() {}
	//! destructor
    ~DevisesManager();
	//! \struct Handler
	/** 
	* \brief Avoir une unique instance de DevisesManager 
	* attribut : instance
	*/
    struct Handler {
        DevisesManager* instance = nullptr; /**< instance :DevisesManager* pointe sur l'unique DeviseManager */
        //! destructor
		/** \brief Permet de libérer la mémoire allouée lors de la création de instance */
		~Handler() { delete instance; }
    };
    static Handler handler; /**< handler: static Handler représente l'unique DeviseManager */
public:
	//! method getManager ; retourne static DevisesManager& : la valeur de handler.instance, si elle n'existe pas, elle la créée 
    static DevisesManager& getManager() {
        if (handler.instance == nullptr)
            handler.instance = new DevisesManager;
        return *handler.instance;
    }
	//! method libererManager ; libère l'instance handler.instance
    static void libererManager() {
        delete handler.instance;  handler.instance = nullptr;
    }
	//! method getDeviseCodes ; retourne QstringList : la liste des codes des devises 
    QStringList getDeviseCodes() const;
	//! method creationDevise ; retourne Devise* : la valeur de l'adresse de la devise qui vient d'être créée et nullptr en cas d'échec
	/** 
	* \param code :const QString&
	* \param monnaie :const Qstring&
	* \param zone :const QString&
	*/
    Devise* creationDevise(const QString& code, const QString& monnaie, const QString& zone);
    //! method getDevise ; retourne Devise* : la valeur de l'adresse de la devise dont le code est égale au code donné en entrée
	/** 
	* \param code :const QString&
	*/
	Devise* getDevise(const QString& code)const;
	//! method getPaireDevises ; retourne PaireDevises& : la valeur de l'adresse de la paire recherchée s'il existe. Sinon elle est créée
	/** 
	* \param code1 :const QString&
	* \param code2 :const Qstring&
	*/
    PaireDevises& getPaireDevises(const QString & code1, const QString & code2) const;
};



/*------------------------------------------------ Partie EvolutionCours --------------------------------------------*/

/* * Class CoursOHLCV: contains open price, high price, low price, close price and the trading volume of a date
 */
class CoursOHLCV {
	/**
	* \class CoursOHLCV
	* \brief CoursOHLCV est la classe qui gère les cours d'une paire de devise sur un jour
	* attributs : open, high, low, close, volume, date
	* methodes : getOpen, getLow, getHigh, getClose, getVolume, getDate
	* methodes : setCours, setVolume, setDate, forme, 
isBigBlackCandle, isBigWhiteCandle, isSpinningTop, isDoji, isDragonflyDoji, isGraveStoneDoji,
isHanngingMan, isHammer, isInvertedHammer, isInvertedBlackHammer, isLongLowerShadow,
isLongUpperShadow, isMarubozu, isShootingStar, isShavenBottom, isShavenHead
	*/
    double open = 0; /**< open :double représente le prix d'ouverture */
	double high = 0; /**< high :double représente le prix le plus haut */
	double low = 0; /**< low :double représente le prix le plus bas */
	double close = 0; /**< close :double représente le prix de fermeture */
    unsigned int volume = 0; /**< volume :unsigned int représente le volume échangé */
    QDate date; /**< Qdate :date représente la date */
public:
	//! constructor 1
    CoursOHLCV() {}
	//! constructor 2
	/**
	* \param open :double
	* \parma high :double
	* \param low :double
	* \param close :double
	* \param volume :unsigned int 
	* \param date :Qdate
	*/
    CoursOHLCV(double open, double high, double low, double close, unsigned int volume, const QDate& date);
    //! method getOpen ; retourne double : la valeur de l'attribut open
	double getOpen() const { return open; }
    //! method getHigh ; retourne double : la valeur de l'attribut high
	double getHigh() const { return high; }
    //! method getLow ; retourne double : la valeur de l'attribut low
	double getLow() const { return low; }
    //! method getClose ; retourne double : la valeur de l'attribut close
	double getClose() const { return close; }
	//! method getVolume ; retourne double : la valeur de l'attribut volume
    unsigned getVolume() const {return volume;}
	//! method setCours ; modifie les valeurs des attributs d'un cours
	/** 
	* \param open :double
	* \parma high :double
	* \param low :double
	* \param close :double
	*/
    void setCours(double open, double high, double low, double close);
	//! method setVolume ; modifie la valeur de l'attribut volume
	/** 
	* \param volume: unsigned int 
	*/
    void setVolume(unsigned int volume) {this->volume = volume;}
    //! method getDate ; retourne Qdate : la valeur de l'attribut date
	QDate getDate() const { return date; }
	//! method setDate ; modifie la date du cours
	/**
	* \param date :Qdate
	*/
    void setDate(const QDate& d) { date=d;}
	//! method form ; retourne QString : donne les caractéristiques liées à la forme de la bougie
    QString forme() const;
	//! method isBigBlackCandle ; retourne bool : true si la bougie est noir, false sinon
    bool isBigBlackCandle() const;
	//! method isBigWhiteCandle ; retourne bool : true si la bougie est blanche, false sinon
    bool isBigWhiteCandle() const;
	//! method isSpinningTop ; retourne bool : true si la bougie est une toupie, false sinon
    bool isSpinningTop() const;          //a.k.a toupie
	//! method isDoji ; retourne bool : true si la bougie est une doji, false sinon
    bool isDoji() const;
	//! method isDragonflyDoji ; retourne bool : true si la bougie est une doji dragon, false sinon
    bool isDragonflyDoji() const;
	//! method isGraveStoneDoji ; retourne bool : true si la bougie est une doji pierre, false sinon
    bool isGraveStoneDoji() const;
	//! method isHanngingMan ; retourne bool : true si la bougie est un pendu, false sinon	
    bool isHanngingMan() const;
	//! method isHammer ; retourne bool : true si la bougie est un marteau, false sinon
    bool isHammer() const;
	//! method isInverteHammer ; retourne bool : true si la bougie est un marteau inversé, false sinon
    bool isInvertedHammer() const;
	//! method isInvertedBlackHammer ; retourne bool : true si la bougie est un marteau noir inversé, false sinon
    bool isInvertedBlackHammer() const;
	//! method isLongLowerShadow ; retourne bool : true si la bougie a une longue meche en bas, false sinon
    bool isLongLowerShadow() const;
	//! method isLongUpperShadow ; retourne bool : true si la bougie a une longue meche en haut, false sinon
    bool isLongUpperShadow() const;
	//! is Marubozu ; retourne bool : true si la bougie est un marubozu, false sinon
    bool isMarubozu() const;
	//! isShootingStar ; retourne bool : true si la bougie est une étoile filante, false sinon
    bool isShootingStar() const;
	//! method isShavenBottom ; retourne bool : true si la bougie est un shoven bottom, false sinon
    bool isShavenBottom() const;
	//! method isShavenHead ; retourne bool : true si la bougie est un shaven head, false sinon
    bool isShavenHead() const;
};

/* *Class ListEvolutionCours: contains a list of csv file name that can used to charge to EvolutionCours
 */
class ListEvolutionCours {
	/**
	* \class ListEvolutionCours
	* \brief liste des fichiers EvolutionCours
	* attributs : filename, nbFiles
	* methodes : addFile
	*/
    QStringList filenames; /**< filenames :QstringList représente la liste des noms des fichiers*/
    int nbFiles; /**< nbFiles :int représente le nombre de noms de fichiers contenu dans filenames */
public:
	//! constructor
	/**
	* \param list :QStringList
	*/
    ListEvolutionCours(QStringList list) {filenames = list; nbFiles = list.length();}
    ~ListEvolutionCours() = default;
	//! method addFile ; ajoute un nouveau nom de fichier à la liste filenames
	/**
	* \param file :QString
	*/
    void addFile(QString file) {filenames<<file; nbFiles++;}
};

class IndicateurCollection;     //forward declaration of IndicateurCollection

/* * Class EvolutionCours: an array of pointer to CoursOHLCV, => the evolution cours of a PaireDevises during a time period
 * - it can be created by charging a csv file
 */
class EvolutionCours {
/**
	* \class EvolutionCours
	* \brief associé à une paire de devises et composé de ses cours, elle représente l'éevolution de la paire sur une période
	* attributs : paire, indicateurCollection, filen, cours, nbCours, nbMaxCours
	* methodes : addCours, operator=, getNbCours, getPaireDevises, getCollection, getNomFichier, saveFile
	* Remarque : possède un iterateur
				- iterator qui correspond à CoursOHLCV*
				- const_iterator qui correspond à const CoursOHLCV*
				avec les méthodes : begin, end, searchcours associées
*/
    const PaireDevises* paire; /**< paire :const PaireDevises* pointe sur une paire de devise*/
    IndicateurCollection* indicateurCollection; /**< indicateurCollection :IndicateurCollection* */
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
    iterator begin() { return cours; }
    iterator end() { return cours + nbCours; }
    using const_iterator = const CoursOHLCV*;
    const_iterator cbegin() const { return cours; }
    const_iterator cend() const { return cours + nbCours; }
    iterator searchCours(QDate date);
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
