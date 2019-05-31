#include "evolutionviewer.h"

EvolutionViewer::EvolutionViewer(EvolutionCours* evolutionCours, QWidget *parent): QWidget(parent), evolutionCours(evolutionCours){
    //installer la serie evolutionCours

    series = new QCandlestickSeries(this);
    series->setName(evolutionCours->getPaireDevises()->toString());          //name of EvolutionCours
    series->setIncreasingColor(QColor(Qt::green));
    series->setDecreasingColor(QColor(Qt::red));
    chart = new QChart();
    chart->setTitle("Cours OHLCV");                             // !!! set name tu paire devise
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->createDefaultAxes();

    QStringList dates;
    QDate oldestDate = evolutionCours->begin()->getDate();
    dates << oldestDate.toString("yy.MM.dd");
    series->clear();
    chart->removeAllSeries();
    dates.empty();

    EvolutionCours::iterator coursIterator = evolutionCours->begin();
    while(coursIterator->getDate() < oldestDate.addDays(maxDateShown) ) {
        Bougie* bougie = new Bougie(coursIterator->getOpen(), coursIterator->getHigh(), coursIterator->getLow(), coursIterator->getClose(), coursIterator);
        //QObject::connect(bougie, SIGNAL(clickBougie(Bougie*)), this, SLOT(showCoursOHLCV(Bougie*)));
        series->append(bougie);
        dates << coursIterator->getDate().toString("yy.MM.dd");
        coursIterator++;
    }
    dates << oldestDate.addDays(maxDateShown).toString("yy.MM.dd");
    chart->addSeries(series);
    QBarCategoryAxis *axisX = new QBarCategoryAxis;
    axisX->append(dates);
    chart->setAxisX(axisX,series);


    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chartView = new QChartView(chart, this);
    scrollBar = new QScrollBar(Qt::Horizontal, this);
    QObject::connect(scrollBar, SIGNAL(sliderMoved(int)), this, SLOT(updateChart()));


    layout = new QVBoxLayout;
    layout->addWidget(chartView);
    layout->addWidget(scrollBar);
    this->setLayout(layout);
    //ajouter des bougies
  /*  QStringList dates;
    int i = 0;
    for (EvolutionCours::iterator coursIterator=evolutionCours->begin(); coursIterator!=evolutionCours->cend(); coursIterator++){
        Bougie* bougie = new Bougie(coursIterator->getOpen(), coursIterator->getHigh(), coursIterator->getLow(), coursIterator->getClose(), coursIterator);
        QObject::connect(bougie, SIGNAL(clickBougie(Bougie*)), this, SLOT(showCoursOHLCV(Bougie*)));
        series->append(bougie);
        qDebug() << i++;
        dates << coursIterator->getDate().toString("yy.MM.dd");
    }
    */
  //installer chart

   // chart->addSeries(series);

    //QBarCategoryAxis *axisX = new QBarCategoryAxis;
   // axisX->append(dates);
   // chart->setAxisX(axisX,series);
    //installer chartView

    //chartView->setFixedSize(1000, 600);
/*

    open = new QLineEdit;
    high = new QLineEdit;
    low = new QLineEdit;
    close = new QLineEdit;
    formLayout = new QFormLayout;
    formLayout->addRow("&Open", open);
    formLayout->addRow("&High", high);
    formLayout->addRow("&Low", low);
    formLayout->addRow("&Close", close);

    saveButton = new QPushButton("Save", this);
    saveButton->setStyleSheet("border: 1px solid black; background: white; height: 20px;width: 50px");
    QObject::connect(saveButton, SIGNAL(clicked()), this, SLOT(saveCoursOHLCV()));
*/
   // coucheCours = new QVBoxLayout;
//    coucheCours->addLayout(formLayout);
//    coucheCours->addWidget(saveButton);
   // fenetre = new QHBoxLayout;
  //  fenetre->addWidget(chartView);
 //   fenetre->addLayout(coucheCours);
  //  this->setLayout(fenetre);
}
/*
void EvolutionViewer::showCoursOHLCV(Bougie* bougie){
    QString buffer;
    buffer.setNum(bougie->getCoursOHLCV().getOpen());
    open->setText(buffer);
    buffer.setNum(bougie->getCoursOHLCV().getHigh());
    high->setText(buffer);
    buffer.setNum(bougie->getCoursOHLCV().getLow());
    low->setText(buffer);
    buffer.setNum(bougie->getCoursOHLCV().getClose());
    close->setText(buffer);
    last_bougie_clicked = bougie;
}

void EvolutionViewer::saveCoursOHLCV(){
    double o = open->text().toDouble(), h = high->text().toDouble(), l = low->text().toDouble(), c = close->text().toDouble();
    last_bougie_clicked->getCoursOHLCV().setCours(o,h,l,c);
    last_bougie_clicked->setOpen(o);
    last_bougie_clicked->setHigh(h);
    last_bougie_clicked->setLow(l);
    last_bougie_clicked->setClose(c);
}
*/
QDate EvolutionViewer::getoldesDateVisible() const {
    qint64 nb_Days = evolutionCours->begin()->getDate().daysTo((evolutionCours->end()-1)->getDate());
    qDebug() << nb_Days;
    qint64 correspond = (nb_Days - maxDateShown)* (scrollBar->value()/(scrollBar->maximum() - scrollBar->minimum())) - maxDateShown;
    qDebug()<< correspond;
    return evolutionCours->begin()->getDate().addDays(correspond);
}

void EvolutionViewer::updateChart() {
    QStringList dates;
    QDate oldestDate = getoldesDateVisible();
    qDebug() << oldestDate.toString("yy.MM.dd");
    dates << oldestDate.toString("yy.MM.dd");
    series->clear();

    dates.empty();
    EvolutionCours::iterator coursIterator = evolutionCours->searchCours(oldestDate);
    while(coursIterator->getDate() < oldestDate.addDays(maxDateShown) ) {
        Bougie* bougie = new Bougie(coursIterator->getOpen(), coursIterator->getHigh(), coursIterator->getLow(), coursIterator->getClose(), coursIterator);
        //QObject::connect(bougie, SIGNAL(clickBougie(Bougie*)), this, SLOT(showCoursOHLCV(Bougie*)));
        series->append(bougie);
        dates << coursIterator->getDate().toString("yy.MM.dd");
    }
    if (series == nullptr) throw qDebug() <<"series is null";
    dates << oldestDate.addDays(maxDateShown).toString("yy.MM.dd");

    qDebug() << "gethere";

    qDebug() << "gethere";
}
