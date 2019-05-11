#ifndef EVOLUTIONVIEWER_H
#define EVOLUTIONVIEWER_H
#include <QWidget>
#include <QtCharts>
#include <QDate>
#include "trading.h"

class Bougie : public QCandlestickSet {
    Q_OBJECT
    CoursOHLCV* cours;
public:
    Bougie(qreal open, qreal high, qreal low, qreal close, CoursOHLCV* cours, qreal timestamp = 0.0, QObject *parent = nullptr): QCandlestickSet(open, high, low, close, timestamp, parent), cours(cours){
        connect(this,SIGNAL(clicked()),this, SLOT( viewCoursOHLCV()));
    }
    CoursOHLCV& getCoursOHLCV() { return *cours; }
    const CoursOHLCV& getCoursOHLCV() const { return *cours; }
signals:
    void clickBougie(Bougie* cours);
private slots:
    void viewCoursOHLCV(){ emit clickBougie(this); }
};

class EvolutionViewer: public QWidget{
    Q_OBJECT
    EvolutionCours& evolutionCours;
    Bougie* last_bougie_clicked = nullptr;
    QCandlestickSeries* series; //un ensemble de bougies
    QChart* chart;  //un graphique sur un ensemble de bougies
    QChartView* chartView;  //un viewer graphique

    //barre d'edition
    QLineEdit* open;
    QLineEdit* high;
    QLineEdit* low;
    QLineEdit* close;
    QPushButton* saveButton;
    QFormLayout* formLayout;
    QVBoxLayout* coucheCours;
    QHBoxLayout* fenetre;
public:
    explicit EvolutionViewer(EvolutionCours& evolutionCours, QWidget *parent = nullptr);
signals:
private slots:
    void showCoursOHLCV(Bougie *bougie);
    void saveCoursOHLCV();
public slots:
};
#endif // EVOLUTIONVIEWER_H
