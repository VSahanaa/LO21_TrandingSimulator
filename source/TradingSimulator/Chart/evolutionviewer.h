#ifndef EVOLUTIONVIEWER_H
#define EVOLUTIONVIEWER_H
/**
 * \file 	evolutionviewer.h
 * \brief 	Contient les classes Bougie, EvolutionViewer, VolumeViewer
 */
#include <QWidget>
#include <QtCharts>
#include <QScrollBar>
#include <QDate>
#include "../Core_Devises/trading.h"
#include "../Controller/transaction.h"

/**
* \class Bougie
* \brief QObject, hérite de QCandlestickSet, interface des CoursOHLCV sous forme de bougies
* attributs : cours
* méthodes publiques : Bougie, getCoursOHLCV
* signals publics : clickBougie; hoverBougie
* slots privés : pickCours, viewForm
*/
class Bougie : public QCandlestickSet {
    Q_OBJECT
    CoursOHLCV* cours; /**< cours :CoursOHLCV* pointe sur le cours OHLCV associé à la bougie*/
public:
    //! Contructeur
    /**
    * \param open :qreal
    * \param high :qreal
    * \param low :qreal
    * \param close :qreal
    * \param cours :CoursOHLCV*
    * \param timestamp :qreal
    * \param parent :QObject*
    */
    Bougie(qreal open, qreal high, qreal low, qreal close, CoursOHLCV* cours, qreal timestamp = 0.0, QObject *parent = nullptr): QCandlestickSet(open, high, low, close, timestamp, parent), cours(cours){
        connect(this, SIGNAL(pressed()), this, SLOT(viewForm()));
        connect(this,SIGNAL(clicked()),this, SLOT(pickCours()));
    }
    //! Cours OHLCV associé avec la bougie
    /**
    * \return const CoursOHLCV& : retourne le cours associé à la bougie
    */
    const CoursOHLCV& getCoursOHLCV() const { return *cours;}
signals:
    //! signaler quand la bougie est appuyer
    /**
    * \param cours CoursOHLCV*
    * \return void
    */
    void clickBougie(CoursOHLCV* cours);
    //! signaler quand la bougie est pressé
    /**
    * \param cours CoursOHLCV*
    * \return void
    */
    void hoverBougie(CoursOHLCV* cours);
private slots:
    //! Choisir un cours
    /**
    * \return void : permet de passer le message que la bougie a été cliquée
    */
    void pickCours(){ emit clickBougie(cours); }
    //! slot viewForm de la bougie
    /**
    * \return void : permet créer la forme de la bougie
    */
    void viewForm() { emit hoverBougie(cours);}
};

/**
* \class EvolutionViewer
* \brief QObject, hérite de QWidget, représentation des bougies sous forme de graphique en chandelier
* attributs : evolutionCours, ema, macd, currentCours, maxDateShown, series, EMA_series, MACD_series, MACD_histogram, MACD_signal, axisX, axisY, chart, chartView, scrollBar, layout
* méthodes privées : clearCharts
* méthodes publiques : EvolutionViewer, showChart, setCurrentCours, activateEMA, activateMACD
* signals publics : currentCoursChanged, coursPicked
* slots privés : updateChart, currentCoursChanged_react, pickCours
* slot public : analyseForm
*/
class EvolutionViewer: public QWidget{
    Q_OBJECT
    EvolutionCours* evolutionCours; /**< evolutionCours :EvolutionCours* pointe sur la série de cours auquelle elle est associée*/
    EMA* ema; /**< ema :EMA* pointe sur la série d'indicateur EMA auquelle elle est associée*/
    MACD* macd; /**< macd :MACD* pointe sur la série d'indicateur MACD auquelle elle est associée*/
    EvolutionCours::iterator currentCours; /**< currentCours :EvolutionCours::iterator pointe sur le cours OHLCV en cours*/
    qint64 maxDateShown = 30; /**< maxDateShown :qint64 représente le nombre de date afficher à l'écran*/
    QCandlestickSeries* series; /**< series :QCandlestickSeries* pointe sur la série de bougies qui vont être représentées*/
    QLineSeries* EMA_series; /**< EMA_series :QLineSeries* pointe sur la série de EMA qui va être représentée*/
    QLineSeries* MACD_series, *MACD_signal, *MACD_histogram; /**< MACD_histogram, MACD_series, MACD_signal :QLineSeries* pointe sur les séries de MACD qui vont être représentées*/
    QBarCategoryAxis *axisX; /**< axisX :QBarCategoryAxis* pointe sur l'axe X*/
    QValueAxis* axisY; /**< axisY :QValueAxis* pointe sur l'axe Y */
    QChart* chart;  /**< chart :QChart* pointe sur le graphe de l'ensemble des bougies */
    QChartView* chartView; /**< chartView :QChartView* vue du graphe */
    QScrollBar* scrollBar; /**< scrollBar :QScrollBar* pointe sur la barre de scroll permettant de bouger sur le graphique*/
    QVBoxLayout* layout; /**< layout :QVBoxLayout* pointe sur la VBox dans laquelle seront alignées les données sur la bougie */
    //! Effacer le graphique
    /**
    * \return void : permet d'éffacer le graphique
    */
    void clearCharts();
public:
    //! Contructeur
    /**
    * \param evolutionCours :EvolutionCours*
    * \param currentCours :EvolutionCours::iterator
    * \param parent :QWidget
    */
    EvolutionViewer(EvolutionCours* evolutionCours, EvolutionCours::iterator currentCours, QWidget *parent = nullptr);
    //! Destructeur
    ~EvolutionViewer();
    //! Afficher le graphique
    /**
    * \param firstdate :QDate
    * \param lastdate :QDate
    * \return void : permet de montrer le graphique
    */
    void showChart(QDate firstdate, QDate lastdate);
    //! Changer le cours actuel
    /**
    * \param currentCours :EvolutionCours::iterator
    * \return void : permet de changer le cours OHLCV en cours
    */
    void setCurrentCours(EvolutionCours::iterator currentCours) {
        this->currentCours = currentCours;
        emit currentCours_changed();
    }
    //! activer EMA
    /**
    * \param val :bool
    * \return void : permet de rendre visible ou non le graphe d'EMA
    */
    void activateEMA(bool val) {EMA_series->setVisible(val);   emit scrollBar->valueChanged(scrollBar->value());}
    //! activer MACD
    /**
    * \param val :bool
    * \return void : permet de rendre visible ou non les graphes de MACD
    */
    void activateMACD(bool val) {
        MACD_series->setVisible(val);
        MACD_signal->setVisible(val);
        MACD_histogram->setVisible(val);
        emit scrollBar->valueChanged(scrollBar->value());
    }
signals:
    //! signal currentCours_changed
    /**
    * \return void : signal représentant le changement de cours
    */
    void currentCours_changed();
    //! signal coursPicked
    /**
    * \param cours :CoursOHLCV*
    * \return void : signal représentant le choix d'un cours OHLCV
    */
    void coursPicked(CoursOHLCV* cours);
private slots:
    //! slot updateChart
    /**
    * \param value :int
    * \return void : mise à jour du graphique
    */
    void updateChart(int value);
    //! slot currentCoursChanged_react
    /**
    * \return void : slot pour le changement de cours
    */
    void currentCoursChanged_react();
    //! slot pickCours
    /**
    * \return void : slot pour le choix d'un cours
    */
    void pickCours(CoursOHLCV* cours) {emit coursPicked(cours);}
public slots:
    //! Analyse de bougie
    /**
    * \param cours :CoursOHLCV*
    * \return void : analyse de la forme de la bougie du cours OHLCV
    */
    void analyseForm(CoursOHLCV* cours);
};

/**
* \class VolumeViewerViewer
* \brief QObject, hérite de QWidget, représentation du volume sous forme de graphique en bar
* attributs : evolutionCours, rsi, currentCours, maxDateShown, series, RSI_series, chartViewRSI, RSI_axisX, RSI_axisY, axisX, axisY, chart, chartView, scrollBar, layout
* méthodes privées : clearCharts
* méthodes publiques : VolumeViewer, ~VolumeViewer, showChart, setCurrentCours
* signals publics : currentCoursChanged
* slots privés : updateChart, currentCoursChanged_react
*/
class VolumeViewer: public QWidget {
    Q_OBJECT
    EvolutionCours* evolutionCours; /**< evolutionCours :EvolutionCours* pointe sur la série de cours associés */
    RSI* rsi; /**< rsi :RSI* pointe sur l'indicateur rsi associé*/
    EvolutionCours::iterator currentCours; /**< currentCours :EvolutionCours::iterator pointe sur le cours OHLCV en cours*/
    qint64 maxDateShown = 30; /**< maxDateShown :qint64 représente le nombre de date montré à l'écran (résolution) */
    QBarSeries *series; /**< series :QBarSeries* pointe sur la séries de bar (pour le volume) */
    QLineSeries* RSI_series; /**< RSI_series :QLineSeries* pointe sur la séries de RSI */
    QChart *chart; /**< chart :QChart* pointe sur le graphique des volumes*/
    QChartView* chartView; /**< chartView QChartView* pointe sur la vue du graphique */
    QChart* chartRSI; /**< chartRSI :QChart* pointe sur le graphique RSI */
    QChartView* chartViewRSI; /**< chartViewRSI :QChartView* pointe sur la vue du graphique RSI*/   //un graphe pour RSI
    QBarCategoryAxis *axisX; /**< axisX :QBarCategoryAxis* pointe sur l'axe X pour le graphe des volumes*/
    QBarCategoryAxis *RSI_axisX; /**< RSI_axisX :QBarCategoryAxis* pointe sur l'axe X pour le graphe RSI*/
    QValueAxis *axisY; /**< axisY :QValueAxis* pointe sur l'axe Y du graphe des volumes */
    QValueAxis* RSI_axisY; /**< axisY :QValueAxis* pointe sur l'axe Y du graphe RSI */
    QScrollBar* scrollBar;	/**< scrollBar ::QScrollBar* barre scrollable pour se déplacer sur le graphique*/
    QVBoxLayout* layout; /**< layout ::QVBoxLayout* pointe sur la VBox sur laquelle seront rangées les données*/
    //! Effacer le graphique
    /**
    * \return void : permet d'éffacer le graphique
    */
    void clearCharts();
public:
    //! Contructeur
    /**
    * \param evolutionCours :EvolutionCours*
    * \param currentCours :EvolutionCours::iterator
    * \param parent :QWidget
    */
    VolumeViewer(EvolutionCours* evolutionCours, EvolutionCours::iterator currentCours, QWidget *parent = nullptr);
    //! Destructeur
    ~VolumeViewer();
    //! Afficher le graphique
    /**
    * \param firstdate :QDate
    * \param lastdate :QDate
    * \return void : permet de montrer le graphique
    */
    void showChart(QDate firstdate, QDate lastdate);
    //! Changer le cours actuel
    /**
    * \param currentCours :EvolutionCours::iterator
    * \return void : permet de changer le cours OHLCV en cours
    */
    void setCurrentCours(EvolutionCours::iterator currentCours) {
        this->currentCours = currentCours;
        emit currentCours_changed();
    }
signals:
    //! signal currentCours_changed
    /**
    * \return void : signal représentant le changement de cours
    */
    void currentCours_changed();
private slots:
    //! slot updateChart
    /**
    * \param value :int
    * \return void : mise à jour du graphique
    */
    void updateChart(int value);
    //! slot currentCoursChanged_react
    /**
    * \return void : slot pour le changement de cours
    */
    void currentCoursChanged_react();
};

#endif // EVOLUTIONVIEWER_H
