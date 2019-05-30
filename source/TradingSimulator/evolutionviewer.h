#ifndef EVOLUTIONVIEWER_H
#define EVOLUTIONVIEWER_H
#include <QWidget>
#include <QtCharts>
#include <QDate>
#include "trading.h"

class csSeriesBrowser
{
    QDate name;
    int index;
    QStringList categories;
    csSeriesBrowser *last = nullptr;
    QCandlestickSeries *current = nullptr;
    csSeriesBrowser *next = nullptr;
public:
    csSeriesBrowser() {}
    csSeriesBrowser(QDate date, int i): name(date), index(i) {}
    ~csSeriesBrowser() = default;
    csSeriesBrowser *getLast() const {return last;}
    QCandlestickSeries *getCurrent() const {return current;}
    csSeriesBrowser *getNext() const {return next;}
    void setLast(csSeriesBrowser* serie) {last = serie;}
    void setCurrent(QCandlestickSeries* serie) {current = serie;}
    void setNext(csSeriesBrowser* serie) {next = serie;}
    QString getName() {return name.toString("yyyy.MM");}
    bool isSameMonth(int year, int month) {if((year == name.year())&&(month == name.month())) return true; else return false;}
    void appendCatego(QString cate) {categories<<cate;}
    QStringList getAxis() {return categories;}
    int getIndex() {return index;}
};

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
    csSeriesBrowser *series = nullptr; //un ensemble de bougies
    QStringList labels;
    QChart* chart;  //un graphique sur un ensemble de bougies
    QChartView* chartView;  //un viewer graphique
    int nb_series;

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
    void changeChart(int i);
    void setNbSeries(int nb) {nb_series = nb;}
    QStringList getLabels() {return labels;}
signals:
private slots:
    void showCoursOHLCV(Bougie *bougie);
    void saveCoursOHLCV();
public slots:
private:
    void wheelEvent(QWheelEvent *eve) {qDebug()<< eve->delta(); int i=eve->delta()>0?1:-1; changeChart(series->getIndex()-i);}
};
#endif // EVOLUTIONVIEWER_H
