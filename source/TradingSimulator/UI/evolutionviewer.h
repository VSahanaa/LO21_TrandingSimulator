#ifndef EVOLUTIONVIEWER_H
#define EVOLUTIONVIEWER_H
#include <QWidget>
#include <QtCharts>
#include <QScrollBar>
#include <QDate>
#include "../Core_Devises/trading.h"
#include "../Controller/transaction.h"

namespace Ui {
    class Bougie;
    class EvolutionViewer;
    class VolumeViewer;
}
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
    void hoverBougie(CoursOHLCV* cours);
private slots:
    void pickCours(){ emit clickBougie(cours); }
    void viewForm() { emit hoverBougie(cours);}
};


class EvolutionViewer: public QWidget{
    Q_OBJECT
    EvolutionCours* evolutionCours;
    EMA* ema;
    MACD* macd;
    EvolutionCours::iterator currentCours;
    qint64 maxDateShown = 30;
    QCandlestickSeries* series; //un ensemble de bougies
    QLineSeries* EMA_series;
    QLineSeries* MACD_series, *MACD_signal, *MACD_histogram;
    QBarCategoryAxis *axisX;
    QValueAxis* axisY;
    QChart* chart;  //un graphe sur un ensemble de bougies
    QChartView* chartView;
    QScrollBar* scrollBar;
    QVBoxLayout* layout;
    void clearCharts();
public:
    EvolutionViewer(EvolutionCours* evolutionCours, EvolutionCours::iterator currentCours, QWidget *parent = nullptr);
    ~EvolutionViewer();
    void showChart(QDate firstdate, QDate lastdate);
    void setCurrentCours(EvolutionCours::iterator currentCours) {
        this->currentCours = currentCours;
        emit currentCours_changed();
    }
    void activateEMA(bool val) {EMA_series->setVisible(val);   emit scrollBar->valueChanged(scrollBar->value());}
    void activateMACD(bool val) {
        MACD_series->setVisible(val);
        MACD_signal->setVisible(val);
        MACD_histogram->setVisible(val);
        emit scrollBar->valueChanged(scrollBar->value());
    }
    //void resizeEvent(QResizeEvent *event);
signals:
    void currentCours_changed();
    void coursPicked(CoursOHLCV* cours);
private slots:
    void updateChart(int value);
    void currentCoursChanged_react();
    void pickCours(CoursOHLCV* cours) {emit coursPicked(cours);}
public slots:
    void analyseForm(CoursOHLCV* cours);
};


class VolumeViewer: public QWidget {
    Q_OBJECT
    EvolutionCours* evolutionCours;
    RSI* rsi;
    EvolutionCours::iterator currentCours;
    qint64 maxDateShown = 30;
    QBarSeries *series;
    QLineSeries* RSI_series;
    QChart *chart;
    QChartView* chartView;
    QChart* chartRSI;
    QChartView* chartViewRSI;       //un graphe pour RSI
    QBarCategoryAxis *axisX;
    QBarCategoryAxis *RSI_axisX;
    QValueAxis *axisY;
    QValueAxis* RSI_axisY;
    QScrollBar* scrollBar;
    QVBoxLayout* layout;
    void clearCharts();
public:
    VolumeViewer(EvolutionCours* evolutionCours, EvolutionCours::iterator currentCours, QWidget *parent = nullptr);
    ~VolumeViewer();
    void showChart(QDate firstdate, QDate lastdate);
    void setCurrentCours(EvolutionCours::iterator currentCours) {
        this->currentCours = currentCours;
        emit currentCours_changed();
    }
signals:
    void currentCours_changed();
private slots:
    void updateChart(int value);
    void currentCoursChanged_react();
};



#endif // EVOLUTIONVIEWER_H
