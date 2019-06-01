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
    ema = static_cast<EMA*>(evolutionCours->getCollection()->getIndicateur("EMA"));
    macd = static_cast<MACD*>(evolutionCours->getCollection()->getIndicateur("MACD"));
    if(!ema) qDebug()<< "ema is null";
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

    //set up series
    series = new QCandlestickSeries(this);
    series->setName(evolutionCours->getPaireDevises()->toString());          //name of EvolutionCours
    series->setIncreasingColor(QColor(Qt::green));
    series->setDecreasingColor(QColor(Qt::red));

    EMA_series = new QLineSeries();
    EMA_series->setName("EMA");
    EMA_series->setColor(Qt::blue);
    EMA_series->setVisible(false);              //not shown by default
    //ema->generateIndice();

    MACD_series =  new QLineSeries();
    MACD_series->setName("MACD");
    MACD_series->setColor(Qt::black);
    MACD_series->setVisible(false);              //not shown by default
    //macd->generateIndice();

    axisX = new QBarCategoryAxis;
    axisY= new QValueAxis;
    //binding sigals
    QObject::connect(scrollBar, SIGNAL(valueChanged(int)), this, SLOT(updateChart(int)));
    QObject::connect(this, SIGNAL(currentCours_changed()), this, SLOT(currentCoursChanged_react()));

    showChart(evolutionCours->begin()->getDate(), evolutionCours->begin()->getDate().addDays(maxDateShown));
}

void EvolutionViewer::showChart(QDate firstdate, QDate lastdate) {
    EvolutionCours::iterator cours = evolutionCours->searchCours(firstdate);
    series->clear();
    EMA_series->clear();
    MACD_series->clear();
    axisX->clear();
    chart->setTitle(evolutionCours->getPaireDevises()->toString() + " en " + cours->getDate().toString("yyyy"));
    QList<QAbstractSeries*> liste_series = chart->series();
    for (int i=0; i<liste_series.count(); i++) {
        chart->removeSeries(liste_series[i]);
    }

    //chart->removeAxis(axisX);
    Indicateur::iterator emaIterator, macdIterator;
    QStringList dates;
    dates << firstdate.toString("dd/MM");
    int i = 0;
    for (; cours->getDate() <= lastdate; cours++){
            if (cours->getHigh() > axisY->max()) axisY->setMax(cours->getHigh()*1.3);
            if (cours->getLow() < axisY->min()) axisY->setMin(cours->getLow()*0.7);
            Bougie* bougie = new Bougie(cours->getOpen(), cours->getHigh(), cours->getLow(), cours->getClose(), cours);
            //QObject::connect(bougie, SIGNAL(clickBougie(Bougie*)), this, SLOT(showCoursOHLCV(Bougie*)));
            series->append(bougie);

            if(EMA_series->isVisible()) {
                emaIterator = ema->searchIndice(cours);
                if(!emaIterator) {
                    EMA_series->append(i, 0);
                }
                else {
                    EMA_series->append(i, emaIterator->getIndice());
                }
            }
            if(MACD_series->isVisible()) {
                macdIterator = macd->searchIndice(cours);
                if(!macdIterator) {
                    MACD_series->append(i, 0);
                }
                else {
                    MACD_series->append(i, macdIterator->getIndice());
                }
            }
            i++;
            dates << cours->getDate().toString("dd/MM");
            if (cours == currentCours) break;       //only show up to current cours
        }
    dates << lastdate.toString("dd/MM");
    axisX->append(dates);
    chart->addSeries(series);
    if(EMA_series->isVisible()) chart->addSeries(EMA_series);
    if(MACD_series->isVisible()) chart->addSeries(MACD_series);
    chart->setAxisX(axisX,series);
    chart->setAxisY(axisY,series);
}

void EvolutionViewer::updateChart(int value) {
    QDate firstDateShowed = evolutionCours->begin()->getDate().addDays(value);
    qDebug() << firstDateShowed.toString("yy.MM.dd")<<endl;
    showChart(firstDateShowed, firstDateShowed.addDays(maxDateShown));
}

void EvolutionViewer::currentCoursChanged_react() {
    int old_maximum = scrollBar->maximum();
    scrollBar->setMaximum(evolutionCours->begin()->getDate().daysTo((currentCours-maxDateShown)->getDate()));
    if(scrollBar->value() == old_maximum) {
        //if user is navigating  => don't update viewport
        scrollBar->setValue(scrollBar->maximum());      //trigger updateChart()
    }
}
