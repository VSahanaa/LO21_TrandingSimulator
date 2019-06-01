#include "evolutionviewer.h"

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
EvolutionViewer::EvolutionViewer(EvolutionCours* evolutionCours, EvolutionCours::iterator currentCours, QWidget* parent) : QWidget (parent), evolutionCours(evolutionCours), currentCours(currentCours) {
    //set up chart
    chart = new QChart();
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->createDefaultAxes();

    //set up chart view
    chartView = new QChartView(chart, this);
    scrollBar = new QScrollBar(Qt::Horizontal, this);
    scrollBar->setMinimum(0);
    scrollBar->setMaximum(evolutionCours->begin()->getDate().daysTo((currentCours-maxDateShown)->getDate()));      //sync scroll bar with time range
    layout = new QVBoxLayout;
    layout->addWidget(chartView);
    layout->addWidget(scrollBar);
    this->setLayout(layout);

    //set up serie
    series = new QCandlestickSeries(this);
    series->setName(evolutionCours->getPaireDevises()->toString());          //name of EvolutionCours
    series->setIncreasingColor(QColor(Qt::green));
    series->setDecreasingColor(QColor(Qt::red));
    axisX = new QBarCategoryAxis;
    //binding sigals
    QObject::connect(scrollBar, SIGNAL(valueChanged(int)), this, SLOT(updateChart(int)));
    QObject::connect(this, SIGNAL(currentCours_changed()), this, SLOT(currentCoursChanged_react()));

    showChart(evolutionCours->begin()->getDate(), evolutionCours->begin()->getDate().addDays(maxDateShown));
}

void EvolutionViewer::showChart(QDate firstdate, QDate lastdate) {
    EvolutionCours::iterator cours = evolutionCours->searchCours(firstdate);
    if(series->count() > 0) series->clear();
    axisX->clear();
    chart->setTitle(evolutionCours->getPaireDevises()->toString() + " en " + cours->getDate().toString("yyyy"));
    chart->removeSeries(series);
    chart->removeAxis(axisX);
    QStringList dates;
    dates << firstdate.toString("dd/MM");
    int i = 0;
    for (; cours->getDate() <= lastdate; cours++){
            Bougie* bougie = new Bougie(cours->getOpen(), cours->getHigh(), cours->getLow(), cours->getClose(), cours);
            //QObject::connect(bougie, SIGNAL(clickBougie(Bougie*)), this, SLOT(showCoursOHLCV(Bougie*)));
            series->append(bougie);
            qDebug() << i++;
            dates << cours->getDate().toString("dd/MM");
            if (cours == currentCours) break;       //only show up to current cours
        }
    dates << lastdate.toString("dd/MM");
    axisX->append(dates);
    chart->addSeries(series);
    chart->setAxisX(axisX,series);
}

void EvolutionViewer::updateChart(int value) {
    QDate firstDateShowed = evolutionCours->begin()->getDate().addDays(value);
    showChart(firstDateShowed, firstDateShowed.addDays(maxDateShown));
    qDebug() << firstDateShowed.toString("yy.MM.dd")<<endl;
}

void EvolutionViewer::currentCoursChanged_react() {
    int old_maximum = scrollBar->maximum();
    scrollBar->setMaximum(evolutionCours->begin()->getDate().daysTo((currentCours-maxDateShown)->getDate()));
    if(scrollBar->value() == old_maximum) {
        //if user is navigating  => don't update viewport
        scrollBar->setValue(scrollBar->maximum());      //trigger updateChart()
    }
}

