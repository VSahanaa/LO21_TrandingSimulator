#ifndef EVOLUTIONVIEWER_H
#define EVOLUTIONVIEWER_H
#include <QWidget>
#include <QtCharts>
#include <QScrollBar>
#include <QDate>
#include "../Core_Devises/trading.h"

class Bougie : public QCandlestickSet {
    Q_OBJECT
    CoursOHLCV* cours;
public:
    Bougie(qreal open, qreal high, qreal low, qreal close, CoursOHLCV* cours, qreal timestamp = 0.0, QObject *parent = nullptr): QCandlestickSet(open, high, low, close, timestamp, parent), cours(cours){
        //connect(this,SIGNAL(clicked()),this, SLOT( viewCoursOHLCV()));
    }
    CoursOHLCV& getCoursOHLCV() { return *cours; }
    const CoursOHLCV& getCoursOHLCV() const { return *cours; }
signals:
    void clickBougie(Bougie* cours);
private slots:
    void viewCoursOHLCV(){ emit clickBougie(this); }
};

/*

class EvolutionViewer: public QWidget{
    Q_OBJECT
    unsigned int maxDateShown = 60;
    EvolutionCours* evolutionCours;
    EvolutionCours::iterator endData;
    qint64 nbData;
    //Bougie* last_bougie_clicked = nullptr;
    //QCandlestickSeries* series; //un ensemble de bougies
    QChart* chart;  //un graphique sur un ensemble de bougies
    QChartView* chartView;  //un viewer graphique
    QScrollBar* scrollBar;

    //barre d'edition
    QLineEdit* open;
    QLineEdit* high;
    QLineEdit* low;
    QLineEdit* close;
    QPushButton* saveButton;
    QFormLayout* formLayout;

    QVBoxLayout *layout;
    QDate getoldesDateVisible() const;


public:
    explicit EvolutionViewer(EvolutionCours* evolutionCours, QWidget *parent = nullptr);
    //void setname(QString name) {series->setName(name);}
signals:
private slots:
    void updateChart(int position);
    //void showCoursOHLCV(Bougie *bougie);
    //void saveCoursOHLCV();
public slots:
};
    */

class EvolutionViewer: public QWidget{
    Q_OBJECT
    EvolutionCours* evolutionCours;
    EMA* ema;
    MACD* macd;
    RSI* rsi;
    EvolutionCours::iterator currentCours;
    qint64 maxDateShown = 30;
    QCandlestickSeries* series; //un ensemble de bougies
    QLineSeries* EMA_series;
    QLineSeries* MACD_series;
    QLineSeries* RSI_series, *RSI_overbought, *RSI_oversold;
    QBarCategoryAxis *axisX;
    QBarCategoryAxis *RSI_axisX;
    QValueAxis* axisY;
    QValueAxis* RSI_axisY;
    QChart* chart;  //un graphe sur un ensemble de bougies
    QChartView* chartView;
    QChart* chartRSI;
    QChartView* chartViewRSI;       //un graphe pour RSI
    QScrollBar* scrollBar;
    QVBoxLayout* layout;
    void clearCharts();
public:
    EvolutionViewer(EvolutionCours* evolutionCours, EvolutionCours::iterator currentCours, QWidget *parent = nullptr);
    void showChart(QDate firstdate, QDate lastdate);
    void setCurrentCours(EvolutionCours::iterator currentCours) {
        this->currentCours = currentCours;
        emit currentCours_changed();
    }
    void activateEMA() {EMA_series->setVisible(true);   emit scrollBar->valueChanged(scrollBar->value());}
    void activateMACD() {MACD_series->setVisible(true);   emit scrollBar->valueChanged(scrollBar->value());}
    //void resizeEvent(QResizeEvent *event);
signals:
    void currentCours_changed();
private slots:
    void updateChart(int value);
    void currentCoursChanged_react();
};

#endif // EVOLUTIONVIEWER_H
