#ifndef TRADING_H
#define TRADING_H
#include <QString>
#include <QDate>
#include <QStringList>
#include <QFile>
#include <QDebug>
#include<cmath>

using namespace std;

class TradingException {
public:
    TradingException(const QString& message) :info(message) {}
    QString getInfo() const { return info; }
private:
    QString info;
};

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

class CoursOHLCV {
    double open = 0, high = 0, low = 0, close = 0;
    unsigned int volume = 0;
    QDate date;
public:
    CoursOHLCV() {}
    CoursOHLCV(double open, double high, double low, double close, unsigned volume, const QDate& date);
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

class ListEvolutionCours {
    QStringList filenames;
    int nbFiles;
public:
    ListEvolutionCours(QStringList list) {filenames = list; nbFiles = list.length();}
    ~ListEvolutionCours() = default;
    void addFile(QString file) {filenames<<file; nbFiles++;}
};

class EvolutionCours {
    const PaireDevises* paire;
    QString filen;
    CoursOHLCV* cours = nullptr;
    unsigned int nbCours = 0;
    unsigned int nbMaxCours = 0;
public:
    //EvolutionCours() {}
    EvolutionCours(const PaireDevises& paire) :paire(&paire) {}
    EvolutionCours(QString filename); //charger depuis fichier csv
    ~EvolutionCours();
    EvolutionCours(const EvolutionCours& evolutionCours);

    void addCours(double open, double high, double low, double close, unsigned int volume, const QDate& date);  
    EvolutionCours& operator=(const EvolutionCours& evolutionCours);
    unsigned int getNbCours() const { return nbCours; }
    const PaireDevises& getPaireDevises() const { return *paire; }
    using iterator = CoursOHLCV*;
    iterator begin() { return iterator(cours); }
    iterator end() { return iterator(cours + nbCours); }
    using const_iterator = const CoursOHLCV*;
    const_iterator cbegin() const { return cours; }
    const_iterator cend() const { return cours + nbCours; }
    void readFile(QString filename);
    int saveFile();
};

class DevisesManager {
    Devise** devises = nullptr; // tableau de pointeurs sur objets Devise
    unsigned int nbDevises = 0;
    unsigned int nbMaxDevises = 0;
    mutable PaireDevises** paires = nullptr; // tableau de pointeurs sur objets PaireDevises
    mutable unsigned int nbPaires = 0;
    mutable unsigned int nbMaxPaires = 0;
    // empêcher la duplication par recopie ou affectation
    DevisesManager(const DevisesManager& deviseManager) = delete;
    DevisesManager& operator=(const DevisesManager& deviseManager) = delete;
    // pour le singleton
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

#endif // TRADING_H
