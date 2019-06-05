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
        connect(this, SIGNAL(pressed()), this, SLOT(viewForm()));
        connect(this,SIGNAL(clicked()),this, SLOT(pickCours()));
    }
    const CoursOHLCV& getCoursOHLCV() const { return *cours;}

signals:
    void clickBougie(CoursOHLCV* cours);
    void hoverBougie(QString form);
private slots:
    void pickCours(){ emit clickBougie(cours); }
    void viewForm() { emit hoverBougie(cours->forme());}
};


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
    QMouseEvent *mouseMoveEvent;
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
public slots:
    void analyseForm(QString form);
};

#endif // EVOLUTIONVIEWER_H
