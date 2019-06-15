#ifndef TRADING_H
#define TRADING_H

/**
 * \file 	trading.h
 * \brief 	Contient le noyau de l'application
 * 	
 * 	Contient les classes concernant les Devises : TradingException, Devise, PaireDevises, DevisesManager
 * 	Contient les classes concernant les Cours : coursOHLCV, EvolutionCours
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

/**
* \class TradingException
* \brief Contient le message d'erreur
*/
class TradingException {
public:
    //! Constructeur
    /** \param message :const QString&*/
    TradingException(const QString& message) :info(message) {}
    //! Information d'une exception
    /**
    * \return   un QString : la valeur contenue dans l'attribut info
    */
    QString getInfo() const { return info; }
private:
    QString info; /**< info :Qstring contient l'information sur les erreurs */
};

/*-------------------------------------------------------- Partie Devises ----------------------------------------------------*/

/**
* \class Devise
* \brief Représente une devise
* attributs : code, monnaie, zone
* méthodees : getCode, getMonnaie, getZoneGeographique
* amitiéss : class DeviseManager
* Remarques : constructeur privé et destructeur privé
*/
class Devise {
    QString code; /**< code :Qstring contient le code de la devise */
    QString monnaie; /**< monnaie :Qstring contient le nom de la monnaie concernée */
    QString zone; /**< zone :Qstring contient le nom de la zone géographique associée à la devise */
    //! Constructeur
    /**
    * \param code :const QString&
    * \param monnaie :const QString&
    * \param zone :const QString&
    */
    Devise(const QString& code, const QString& monnaie, const QString& zone = "");
    //! Destructor par défault
    ~Devise() = default;
    friend class DevisesManager; /**< declaration d'amitiés : DevisesManager */
public:
    //! Code de la devise
    /**
    * \return  QString : la valeur de l'attribut code
    */
    QString getCode() const { return code; }
    //! Monnaie de la devise
    /**
    * \return   QString : la valeur de l'attribut monnaie
    */
    const QString& getMonnaie() const { return monnaie; }
    //! Zone geographique de la devise
    /**
    * \return   QString : la valeur de l'attribut zone
    */
    const QString& getZoneGeographique() const { return zone; }
};

/**
* \class PaireDevises
* \brief Représente une paire de devises
* attributs : base, contrepartie, surnom
* méthodees : getBase, getContrepartie, getSurnom
* amitiéss : class DeviseManager
* Remarques : constructeur privé et destructeur privé
*/
class PaireDevises {
    const Devise* base; /**< base : const Devise* pointe sur la devise de base */
    const Devise* contrepartie; /**< contrepartie : const Devise* pointe sur la devise de contrepartie */
    QString surnom; /**< surnom : Qstring contient le surnom de la paire */

    //! Constructeur
    /**
    * \param base :const Devise&
    * \param contrepartie :const Devise&
    * \param surnom :const Qstring&
    */
    PaireDevises(const Devise& base, const Devise& contrepartie, const QString& surnom = "");
    //! Destructor par défault
    ~PaireDevises() = default;
    friend class DevisesManager;/**< declaration d'amitiés : DevisesManager */
public:
    //! Devise de base
    /**
    * \return   const Devise& : la valeur de l'attribut base
    */
    const Devise& getBase() const { return *base; }
    //! Devise de contre partie
    /**
    * \return   const Devise& : la valeur de l'attribut contrepartie
    */
    const Devise& getContrepartie() const { return *contrepartie; }
    //! Sur nom de la paire
    /**
    * \return   const QString& : la valeur de l'attribut surnom
    */
    const QString& getSurnom() const { return surnom; }
    //! Mettre le sur nom de la devise
    /**
    * \return   void : permet de modifier le surnom
    * \param surnom :Qstring
    */
    void setSurnom(QString surnom) {this->surnom = surnom;}
    //! Information complet de la paire
    /**
    * \return  Qstring : donne le nom de la paire sous forme de string
    * \brief  renvoie <code>.<contrepartie>/<contrepartie>.<code> sous forme de string
    */
    QString toString() const;
};

/**
* \class DeviseManager
* \brief DeviseManager est la classe singleton qui permet de gérer les devises et les paires
* attributs : devises, nbDevises, nbMaxDevises, paires, nbPaires, nbMaxPaires
* attribut statique : handler
* méthodees : getDeviseCodes, creationDevise, getDevise, getPaireDevises
* méthodees statiques : getManager, libererManager
* amitiéss : class DeviseManager
* Remarques : duplication par recopie ou affectation supprimée, constructeur privé et destructeur privé
*/
class DevisesManager {
    Devise** devises = nullptr; /**< devise : Devise** représente un tableau de pointeurs qui pointent sur Devise de taille nbMaxDevises */
    unsigned int nbDevises = 0; /**< nbDevises : unsigned int représente le nombre d'éléments dans le tableau devises */
    unsigned int nbMaxDevises = 0; /**< nbMaxDevises : unsigned int représente le nombre d'éléments maximum que peut contenir le tableau devises */
    mutable PaireDevises** paires = nullptr; /**< paires : mutable PaireDevises** représente un tableau de pointeurs qui pointent sur PaireDevises de taille nbMaxPaires */
    mutable unsigned int nbPaires = 0; /**< nbPaires : mutable unsigned int représente le nombre d'éléments dans le tableau PaireDevises */
    mutable unsigned int nbMaxPaires = 0; /**< nbMaxPaires : unsigned int représente le nombre d'éléments dans le tableau paires */
    // empêcher la duplication par recopie ou affectation
    DevisesManager(const DevisesManager& deviseManager) = delete;
    DevisesManager& operator=(const DevisesManager& deviseManager) = delete;
    //! Constructeur privé
    /** tous les attributs sont nuls par default*/
    DevisesManager() {}
    //! Destructor privé
    ~DevisesManager();

    //! \struct Handler
    /**
    * \brief Avoir une unique instance de DevisesManager
    * attribut : instance
    */
    struct Handler {
        DevisesManager* instance = nullptr; /**< instance :DevisesManager* pointe sur l'unique DeviseManager */
        //! Destructor de handler
        /** \brief Permet de libérer la mémoire allouée lors de la création de instance */
        ~Handler() { delete instance; }
    };
    static Handler handler; /**< handler: static Handler représente l'unique DeviseManager */
public:
    //! Retourne la référence du objet DevisesManager unique du programme
    /**
    * \return  static DevisesManager& : la référence à instance unique, si elle n'existe pas, elle la créée
    */
    static DevisesManager& getManager() {
        if (handler.instance == nullptr)
            handler.instance = new DevisesManager;
        return *handler.instance;
    }
    //! Libérer le manager
    /**
    * \return void : libère l'instance handler.instance
    */
    static void libererManager() {
        delete handler.instance;  handler.instance = nullptr;
    }
    //! Liste de codes des devises
    /**
    * \return  QstringList : la liste des codes des devises
    */
    QStringList getDeviseCodes() const;
    //! Créer une nouvelle devise
    /**
    * \param code :const QString&
    * \param monnaie :const Qstring&
    * \param zone :const QString&
    * \return Devise* : la valeur de l'adresse de la devise qui vient d'être créée
    */
    Devise* creationDevise(const QString& code, const QString& monnaie, const QString& zone);
    //! Chercher une devise
    /**
    * \param code :const QString&
    * \return Devise* : la valeur de l'adresse de la devise dont le code est égale au code donné en entrée
    */
    Devise* getDevise(const QString& code)const;
    //! Retouner une paire de devises
    /**
    * \param baseCode :const QString&
    * \param contrepartieCode :const Qstring&
    * \return PaireDevises& : la valeur de l'adresse de la paire recherchée s'il existe. Sinon elle est créée
    */
    PaireDevises& getPaireDevises(const QString & baseCode, const QString & contrepartieCode) const;
};



/*------------------------------------------------ Partie EvolutionCours --------------------------------------------*/

/**
* \class CoursOHLCV
* \brief CoursOHLCV est la classe qui gère les cours d'une paire de devise sur un jour
* attributs : open, high, low, close, volume, date
* méthodees : getOpen, getLow, getHigh, getClose, getVolume, getDate
* méthodees : setCours, setVolume, setDate, forme,
isBigBlackCandle, isBigWhiteCandle, isSpinningTop, isDoji, isDragonflyDoji, isGraveStoneDoji,
isHanngingMan, isHammer, isInvertedHammer, isInvertedBlackHammer, isLongLowerShadow,
isLongUpperShadow, isMarubozu, isShootingStar, isShavenBottom, isShavenHead
*/
class CoursOHLCV {

    double open = 0; /**< open :double représente le prix d'ouverture */
    double high = 0; /**< high :double représente le prix le plus haut */
    double low = 0; /**< low :double représente le prix le plus bas */
    double close = 0; /**< close :double représente le prix de fermeture */
    unsigned int volume = 0; /**< volume :unsigned int représente le volume échangé */
    QDate date; /**< QDate :date représente la date */
public:
    //! Constructeur par défault
    /** tous les attributs sont nuls par default, sauf la date qui n'est pas fixé*/
    CoursOHLCV() {}
    //! Constructeur avec des informations d'un cours
    /**
    * \param open :double
    * \parma high :double
    * \param low :double
    * \param close :double
    * \param volume :unsigned int
    * \param date :QDate
    */
    CoursOHLCV(double open, double high, double low, double close, unsigned int volume, const QDate& date);
    //! valeur du prix d'ouverture
    /**
    * \return  double : la valeur de l'attribut open
    */
    double getOpen() const { return open; }
    //! valeur du prix le plus haut
    /**
    * \return  double : la valeur de l'attribut high
    */
    double getHigh() const { return high; }
    //! valeur du prix le plus bas
    /**
    * \return  double : la valeur de l'attribut low
    */
    double getLow() const { return low; }
    //! valeur du prix ferméture
    /**
    * \return  double : la valeur de l'attribut close
    */
    double getClose() const { return close; }
    //! value de la volume
    /**
    * \return  double : la valeur de l'attribut volume
    */
    unsigned getVolume() const {return volume;}
    //! méthode setCours ; modifie les valeurs des prix d'un cours
    /**
    * \param open :double
    * \parma high :double
    * \param low :double
    * \param close :double
    * \return void
    */
    void setCours(double open, double high, double low, double close);
    //! méthode setVolume ; modifie la valeur de l'attribut volume
    /**
    * \param volume: unsigned int
    * \return void
    */
    void setVolume(unsigned int volume) {this->volume = volume;}
    //! méthode getDate
    /**
    * \return  QDate : la valeur de l'attribut date
    */
    QDate getDate() const { return date; }
    //! méthode setDate ; modifie la date du cours
    /**
    * \param date :QDate
    * \return void
    */
    void setDate(const QDate& d) { date=d;}
    //! Forme de la bougie
    /**
    * \return  QString : donne la forme de la bougie
    */
    QString forme(double minLocal, double maxLocal) const;
    //! méthode isToupie
    /**
    * \return  bool : true si la bougie est une toupie, false sinon
    */
    bool isToupie(double minLocal=0, double maxLocal=0) const;          //a.k.a toupie
    //! méthode isDoji
    /**
    * \return  bool : true si la bougie est une doji, false sinon
    */
    bool isDoji(double minLocal, double maxLocal) const;
    //! méthode isDragonflyDoji
    /**
    * \return  bool : true si la bougie est une doji dragon, false sinon
    */
    bool isDragonflyDoji(double minLocal, double maxLocal) const;
    //! méthode isGraveStoneDoji
    /**
    * \return  bool : true si la bougie est une doji pierre, false sinon
    */
    bool isGraveStoneDoji(double minLocal, double maxLocal) const;
    //! méthode isHanggingMan
    /**
    * \return  bool : true si la bougie est un pendu, false sinon
    */
    bool isHanggingMan(double minLocal, double maxLocal) const;
    //! méthode isHammer
    /**
    * \return  bool : true si la bougie est un marteau, false sinon
    */
    bool isHammer(double minLocal, double maxLocal) const;
    //! méthode isInverteHammer
    /**
    * \return  bool : true si la bougie est un marteau inversé, false sinon
    */
    bool isInvertedHammer(double minLocal, double maxLocal) const;
    //! méthode isInvertedBlackHammer
    /**
    * \return  bool : true si la bougie est un marteau noir inversé, false sinon
    */
    bool isInvertedBlackHammer(double minLocal, double maxLocal) const;
    //! méthode isLongLowerShadow
    /**
    * \return  bool : true si la bougie a une longue meche en bas, false sinon
    */
    bool isLongLowerShadow(double minLocal, double maxLocal) const;
    //! méthode isLongUpperShadow
    /**
    * \return  bool : true si la bougie a une longue meche en haut, false sinon
    */
    bool isLongUpperShadow(double minLocal, double maxLocal) const;
    //! is Marubozu
    /**
    * \return  bool : true si la bougie est un marubozu, false sinon
    */
    bool isMarubozu(double minLocal, double maxLocal) const;
    //! isShootingStar
    /**
    * \return  bool : true si la bougie est une étoile filante, false sinon
    */
    bool isShootingStar(double minLocal, double maxLocal) const;
    //! méthode isShavenBottom
    /**
    * \return  bool : true si la bougie est un shoven bottom, false sinon
    */
    bool isShavenBottom(double minLocal, double maxLocal) const;
    //! méthode isShavenHead
    /**
    * \return  bool : true si la bougie est un shaven head, false sinon
    */
    bool isShavenHead(double minLocal, double maxLocal) const;
};

class IndicateurCollection;     //forward declaration of IndicateurCollection

/**
* \class EvolutionCours
* \brief associé à une paire de devises et composé de ses cours, elle représente l'éevolution de la paire sur une période
* attributs : paire, indicateurCollection, filen, cours, nbCours, nbMaxCours
* méthodees : addCours, operator=, getNbCours, getPaireDevises, getCollection, getNomFichier, saveFile
* Remarques : possède un iterateur
            - iterator qui correspond à CoursOHLCV*
            - const_iterator qui correspond à const CoursOHLCV*
            avec les méthodes : begin, end, searchcours associées
*/
class EvolutionCours {
    const PaireDevises* paire; /**< paire :const PaireDevises* pointe sur une paire de devise*/
    IndicateurCollection* indicateurCollection; /**< indicateurCollection :IndicateurCollection* */
    QString filen; /**< filen :Qstring contient le nom du fichier csv*/
    CoursOHLCV* cours = nullptr; /**< cours:coursOHLCV* pointe sur le tableau de coursOHLCV*/
    unsigned int nbCours = 0; /**< nbCours :unsigned int représente le nombre d'éléments dans le tableau de cours*/
    unsigned int nbMaxCours = 0; /**< nbMaxCours :unsigned int représente le nombre maximal d'éléments qu'on peut mettre dans le tableau de cours*/
public:
    //! Constructeur créer l'evolution cours vide
    /**
    * \param paire :const PaireDevises&
    */
    EvolutionCours(const PaireDevises& paire);
    //! Constructeur charge un fichier csv de données
    /**
    * \brief constructeur pour charger les cours d'un fichier csv
    * \param pair :const PaireDevises&
    * \param filename: QString
    */
    EvolutionCours(const PaireDevises& pair, QString filename); //charger depuis fichier csv
    //! Destructor
    ~EvolutionCours();
    //! Constructeur dupplication par recopie
    /**
    * \brief duplication par recopie
    * \param evolutionCours :const EvolutionCours&
    */
    EvolutionCours(const EvolutionCours& evolutionCours);
    //! Ajoute un cours au tableau
    /**
    * \param open :double
    * \parma high :double
    * \param low :double
    * \param close :double
    * \param volume :unsigned int
    * \param date :QDate
    * \return void
    */
    void addCours(double open, double high, double low, double close, unsigned int volume, const QDate& date);
    //! Recopie par operator =
    /**
    * \param evolutionCours :const EvolutionCours&
    * \return EvolutionCours& : duplication par affectation
    */
    EvolutionCours& operator=(const EvolutionCours& evolutionCours);
    //! nombre de cours dans la série
    /**
    * \return  unsigned int : la valeur de l'attribut NbCours
    */
    unsigned int getNbCours() const { return nbCours; }
    //! Paire de devises associé
    /**
    * \return  const PaireDevises* : la valeur de l'attribut paire
    */
    const PaireDevises* getPaireDevises() const { return paire; }
    //! Collection des indicateurs associée
    /**
    * \return  IndicateurCollection* : la valeur de l'attribut indicateurCollection
    */
    IndicateurCollection* getCollection() const {return indicateurCollection;}
    //! Nom de fichier .csv qui utilisé pour chargé évolution cours
    /**
    * \return  const QString&* : la valeur de l'attribut filen
    */
    const QString& getNomFichier() const {return filen;}

    using iterator = CoursOHLCV*; /**< iterator correspond à coursOHLCV* */
    //! Debut de la table de cours
    /**
    * \return  iterator : la valeur du pointeur du premier cours
    */
    iterator begin() { return cours; }
    //! Fin de la table de cours
    /**
    * \return  iterator : pointe vers la fin de la table de Cours
    */
    iterator end() { return cours + nbCours; }
    using const_iterator = const CoursOHLCV*; /**< const_iterator correspond à const coursOHLCV* */
    //! Pointeur constant du debut de la table de cours
    /**
    * \return  const_iterator : la valeur du pointeur const du premier cours
    */
    const_iterator cbegin() const { return cours; }
    //! Pointeur constant de la fin de la table de cours
    /**
    * \return  const_iterator : pointeur constant vers la fin de la table de Cours
    */
    const_iterator cend() const { return cours + nbCours; }
    //! Chercher un cours en utilisant le date
    /**
    * \param date :Qdate
    * \return iterator : la valeur du pointeur du cours associé avec le date correspondant ou just après la date entrée si elle existe et nullptr, sinon.
    */
    iterator searchCours(QDate date);
};


/*-------------------------------------------------- Partie Indicateur ------------------------------------------------------------*/

/**
* \class IndiceIndicateur
* \brief contient la valeure d'un indicateur sur une journée
* attributs : donnee, date
* méthodees : getIndice, getDate, setIndice, setDate, toString
* remarques : https://stockcharts.com/school/doku.php?id=chart_school:technical_indicators:introduction_to_technical_indicators_and_oscillators#momentum_oscillators
*/
class IndiceIndicateur {

private:
        double donnee; /**< donnee :double contient la valeur de l'indicateur pour un jour*/
        QDate  date; /**< date :QDate contient la date à laquelle donnee est associée*/
public:
        //! Constructeur
        /**
        * \param list :QStringList
        */
        IndiceIndicateur(){}
        //! valeur d'idicateur
        /**
        * \return  double : la valeur de l'attribut donnee
        */
        double getIndice() const { return donnee;}
        //! Date associé avec cet indicateur
        /**
        * \return  QDate :  la valeur de la date
        */
        QDate  getDate() const { return date;}
        //! Changer la valeur d'indicateur
        /**
        * \param donnee :double
        * \return void : modifie la valeur de l'indice
        */
        void setIndice(double donnee) { this->donnee = donnee;}
        //! Change la date
        /**
        * \param date :QDate
        * \return void : modifie la valeur de date
        */
        void setDate(QDate date) { this->date = date;}
        //for debugging
        //! Information de l'indicateur, peut utiliser pour debugging
        /**
        * \return  QString : la concaténation <date>.indicateur.<donnee
        */
        QString toString() const {return date.toString("dd.MM.yyyy") + " indicateur: " + QString::number(donnee);}
};

/**
* \class Indicateur
* \brief classe abstraite pour les indicateurs
* attributs protégés : nom, evolutionCours, indices, nbIndicateur, nbMaxIndicateur
* méthodees : searchIndice
* méthodees virtuelles pures : generateIndice, setParameters, getParameters
* amitiés : IndicateurCollection
* Remarques : Utiliser seul pour Polymorphisme, possède un iterateur
            - iterator qui correspond à IndiceIndicateur*
            - const_iterator qui correspond à const IndiceIndicateur*
            avec les méthodes : begin, end, searchIndice associées
*/
class Indicateur {
    friend class IndicateurCollection;
protected:
    QString nom; /**< nom :QString contient le nom de l'indicateur */
    EvolutionCours* evolutionCours; /**< evolutionCours :EvolutionCours* contient la valeur du pointeur sur EvolutionCours */
    IndiceIndicateur* indices = nullptr;  /**< indices :IndiceIndicateur* pointe sur un tableau de IndiceIndicateur */
    unsigned int nbIndicateur; /**< nbIndicateur :unsigned int contient la valeur du nombre d'éléments dans le tableau indices */
    unsigned int nbMaxIndicateur; /**< nbMaxIndicateur :unsigned int contient la valeur du nombre maximal d'éléments que peut contenir le tableau indices*/
    //! Constructeur avec une série d'indice vide
    /**
    * \param evolutionCours :EvolutionCours*
    * \param nom :QString = "unnamed indicator" par default
    */
    Indicateur(EvolutionCours* evolutionCours, QString nom = "unnamed indicator"); //peut instancier que des classes dérivé
    Indicateur() = delete;
    //! destructor virtuel
    /** \brief libère la mémoire allouée pour le tableau indices
    */
    virtual ~Indicateur() {delete[] indices;}
public:
    //! Interface virtual pure generateIndice, generer la series d'indicateur
    /**
    * \return  void : génére le tableau d'indice
    */
    virtual void generateIndice() = 0;          //where array of Indices is generated
    using iterator = IndiceIndicateur*; /**< iterator correspond à IndiceIndicateur* */
    using const_iterator = const IndiceIndicateur*; /**< const_iterator correspond à const IndiceIndicateur* */
    //! Debut de la série d'indicateur
    /**
    * \return  iterator : pointe sur premier élément du tableau indices
    */
    iterator begin(){return indices;}
    //! Fin de la série d'indicateur
    /**
    * \return  iterator : pointe sur la fin du tableau indices
    */
    iterator end(){return indices + nbIndicateur;}
    //! Pointeur constant du debut de la série d'indicateur
    /**
    * \return  const_iterator : la valeur du pointeur const sur le premier élément du tableau indices
    */
    const_iterator cbegin() const {return indices;}
    //! Pointeur constant de la fin de la série d'indicateur
    /**
    * \return  	const_iterator : la valeur du pointeur const sur la fin du tableau indices
    */
    const_iterator cend() const {return indices+ nbIndicateur;}
    //! Cherche un indice selon le coursOHLCV qu'il associé
    /**
    * \param cours :coursOHLCV*
    * \return IndiceIndicateur*
    */
    IndiceIndicateur* searchIndice(CoursOHLCV* cours);
    //! Interface virtual pure setParameters pour modifier les paramtres d'indicateur et regénérer la série d'indices
    /**
    * \param QMap<QString
    * \param QVariant> parameter
    * \return void : modifie les paramatres
    */
    virtual void setParameters(QMap<QString, QVariant> parameters) = 0;         //encapsulate parameters inside an QMap object and pass it as argument
    //! Interface virtual pure getParameters pour prendre des valeur de parametres
    virtual QMap<QString, QVariant> getParameters() const = 0;
    //! méthode index
    /**
    * \param indice : Indicateur::iterator
    * \return int : position d'un IndiceIndicateur dans la chaine
    */
    int index(iterator indice){
        for (int i=0; i<nbIndicateur; i++) {
            if(begin()+i == indice) return i;
        }
        return -1;
    }
};

/**
* \class EMA
* \brief l'indicateur EMA : Exponential Moving Average
* attributs : period
* méthodees : generateIndice, setParameters, getParameters
* amitiés : IndicateurCollection, MACD
* Remarques : 	hérite de la classe Indicateur
                https://www.investopedia.com/ask/answers/122314/what-exponential-moving-average-ema-formula-and-how-ema-calculated.asp
*/
class EMA : public Indicateur{
    friend class IndicateurCollection;     //can only be created by IndicateurCollection
    friend class MACD;
private:
    unsigned int period; /**< period :unsigned int contient la période utilisé pour cacule l'indicateur*/
    //! Constructeur
    /**
    * \param evolutionCours :EvolutionCours*
    * \param period :unsigned int
    */
    EMA(EvolutionCours* evolutionCours, unsigned int period = 10) : Indicateur(evolutionCours, "EMA"), period(period) {}      //create instance with an empty array of indices
public:
    //! Implementer l'interface generateIndice()
    /**
    * \return  void : création du tableau d'indices
    */
    void generateIndice();        //where array of indice is really instanciate
    //! Implémenter l'interface setParameters()
    /**
    * \param QMap<QString
    * \param QVariant> parameter
    * \return void : modifie les paramatres
    */
    void setParameters(QMap<QString, QVariant> parameters);
    //! Implémenter l'interface getParameters ;
    QMap<QString, QVariant> getParameters() const;
};

/**
* \class RSI
* \brief l'indicateur RSI : Relative Strength Index
* attributs : lookbackPeriod, overboughtBound, oversoldBound
* méthodees : generateIndice, setParameters, getParameters, setOverboughtBound, setOversoldBound, setLookbackPeriod
* amitiés : IndicateurCollection
* Remarques : 	hérite de la classe Indicateur
                https://stockcharts.com/school/doku.php?id=chart_school:technical_indicators:relative_strength_index_rsi
*/
class RSI : public Indicateur {
    friend class IndicateurCollection;     //can only be created by IndicateurCollection
private:
    unsigned int lookbackPeriod; /**< lookbackPeriod :unsigned int contient la valeur de la periode précédente*/
    double overboughtBound; /**< overboughtBound :double si RSI>overboughtBound alors on se trouve en sur-achat*/
    double oversoldBound; /**< overboughtBound :double si RSI<overboughtBound alors on se trouve en sur-vente*/
    //! Constructeur
    /**
    * \param evolutionCours :EvolutionCours*
    * \param lookbackPeriod :unsigned int =14 par défault
    * \param overboughtBound :double =80 par défault
    * \param oversoldBound :double =20 par défault
    */
    RSI(EvolutionCours* evolutionCours, unsigned int lookbackPeriod = 14, double overboughtBound= 80, double oversoldBound= 20) :
        Indicateur(evolutionCours, "RSI"), lookbackPeriod(lookbackPeriod), overboughtBound(overboughtBound), oversoldBound(oversoldBound) {}      //create instance with an empty array of indices
public:
    //! Implémenter l'interface generateIndice
    /**
    * \return  void : création du tableau d'indices
    */
    void generateIndice();
    //! Changer la valeur de la borne sur-achat
    /**
    * \param overboughtBound :double =80 par défault
    * \return void :  modifie la valeur de overboughtBound
    */
    void setOverboughtBound(double overboughtBound=80) {this->overboughtBound = overboughtBound;}
    //! Changer la valeur de la borne sur-vente
    /**
    * \param oversoldBound :double =20 par défault
    * \return void : modifie la valeur de oversoldBound
    */
    void setOversoldBound(double oversoldBound=20) {this->oversoldBound = oversoldBound;}
    //! Changer la valeur de la periode précédente
    /**
    * \param lookbackPeriod :unsigned int =14 par défault
    * \return void : modifie la valeur de lookbackPeriod
    */
    void setLookbackPeriod(unsigned int lookbackPeriod=14);
    //! Implémenter l'interface setParameters()
    /**
    * \param QMap<QString
    * \param QVariant> parameter
    * \return void : modifie les paramatres
    */
    void setParameters(QMap<QString, QVariant> parameters);
    //! Implémenter l'interface getParameters ;
    QMap<QString, QVariant> getParameters() const;
};

/**
* \class MACD
* \brief l'indicateur MACD : Moving Average Convergence Divergence
* attributs : longPeriod, shortPeriod, signalPeriod, signalLine, histogram
* méthodees : generateIndice, setParameters, getParameters
* amitiés : IndicateurCollection
* Remarques : 	hérite de la classe Indicateur
                https://stockcharts.com/school/doku.php?id=chart_school:technical_indicators:moving_average_convergence_divergence_macd
*/
class MACD : public Indicateur {
    friend class IndicateurCollection;     //can only created by IndicateurCollection
private:
    unsigned int longPeriod; /**< longPeriod :unsigned int */
    unsigned int shortPeriod; /**< shortPeriod :unsigned int */
    unsigned int signalPeriod; /**< signalPeriod :unsigned int */
    IndiceIndicateur* signalLine = nullptr; /**< signalLine :IndiceIndicateur* */
    IndiceIndicateur* histogram = nullptr; /**< histogram :IndiceIndicateur* */
    //create instance with an empty array of indices
    //! Constructeur
    /**
    * \param evolutionCours :EvolutionCours*,
    * \param shortPeriod :unsigned int =12 par défault
    * \param longPeriod :unsigned int =26 par défault
    * \param signalPeriod :unsigned int =9 par défault
    */
    MACD(EvolutionCours* evolutionCours, unsigned int shortPeriod=12, unsigned int longPeriod=26, unsigned int signalPeriod=9) : Indicateur(evolutionCours, "MACD") {
        if(longPeriod < shortPeriod || longPeriod < signalPeriod) throw TradingException("MACD: long period doit etre le plus grand");
        this->longPeriod = longPeriod;  this->shortPeriod = shortPeriod;    this->signalPeriod = signalPeriod;
    }
public:
    //! Implémenter l'interface generateIndice
    /**
    * \return  void : création du tableau d'indices
    */
    void generateIndice();
    //! Implémenter l'interface setParameters
    /**
    * \param QMap<QString
    * \param QVariant> parameter
    * \return void : modifie les paramatres
    */
    void setParameters(QMap<QString, QVariant> parameters);
    //! Implémenter l'interface getParameters ;
    QMap<QString, QVariant> getParameters() const;
    //! Debut de la série signalLine
    /**
    * \return  iterator : pointe sur premier élément du tableau signalLine
    */
    iterator signalLine_begin() {return signalLine;}
    //! Fin de la série signalLine
    /**
    * \return  iterator : pointe sur la fin du tableau signalLine
    */
    iterator signalLine_end() {return signalLine + nbIndicateur;}
    //! Debut de la série histogram
    /**
    * \return  iterator : pointe sur premier élément du tableau histogram
    */
    iterator histogramLine_begin() {return histogram;}
    //! Fin de la série histogram
    /**
    * \return  iterator : pointe sur la fin du tableau histogram
    */
    iterator histogramLine_end() {return histogram+nbIndicateur;}
};

/**
* \class IndicateurCollection
* \brief collection des indicateurs, ils appartiennent à un objet EvolutionCours
* méthodes : getIndicateur
* amitiés : EvolutionCours
* Remarques : Appliquer design patern Factory
*/
class IndicateurCollection {
    friend class EvolutionCours;        //can only be created and deleted by EvolutionCours
    QHash<QString, Indicateur*> indicateurDictionary;
    //! Constructeur
    /**
    * \param evolutionCours :EvolutionCours*
    */
    IndicateurCollection(EvolutionCours* evolutionCours);
    ~IndicateurCollection();
public:
    //! Retourne un Indicateur choisir
    /**
    * \param nom :QString
    * \return Indicateur* :  le pointeur qui pointe sur l'indicateur demandé et nullptr, sinon
    */
    Indicateur* getIndicateur(QString nom);
};
#endif // TRADING_H
