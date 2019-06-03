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
    rsi = static_cast<RSI*>(evolutionCours->getCollection()->getIndicateur("RSI"));
    //set up chart for EvolutionCours
    chart = new QChart();
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->createDefaultAxes();
    chartView = new QChartView(chart, this);

    //setup RSI viewer
    chartRSI = new QChart();
    chartRSI->setAnimationOptions(QChart::SeriesAnimations);
    chartRSI->legend()->setVisible(true);
    chartRSI->legend()->setAlignment(Qt::AlignBottom);
    chartRSI->createDefaultAxes();
    chartViewRSI = new  QChartView(chartRSI, this);

    scrollBar = new QScrollBar(Qt::Horizontal, this);
    scrollBar->setMinimum(0);
    scrollBar->setMaximum(evolutionCours->begin()->getDate().daysTo((currentCours-maxDateShown)->getDate()));      //sync scroll bar with time range
    layout = new QVBoxLayout;
    layout->addWidget(chartView);
    layout->addWidget(scrollBar);
    layout->addWidget(chartViewRSI);
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

    RSI_series=  new QLineSeries();
    RSI_series->setName("RSI");
    RSI_series->setColor(Qt::black);
    RSI_series->setVisible(true);
    rsi->generateIndice();
    axisX = new QBarCategoryAxis;
    axisY= new QValueAxis;
    RSI_axisY = new QValueAxis;
    RSI_axisY->setRange(0,100);

    //binding sigals
    QObject::connect(scrollBar, SIGNAL(valueChanged(int)), this, SLOT(updateChart(int)));
    QObject::connect(this, SIGNAL(currentCours_changed()), this, SLOT(currentCoursChanged_react()));

    showChart(evolutionCours->begin()->getDate(), evolutionCours->begin()->getDate().addDays(maxDateShown));
}

void EvolutionViewer::showChart(QDate firstdate, QDate lastdate) {
    qDebug()<< "begin func";
    EvolutionCours::iterator cours = evolutionCours->searchCours(firstdate);
    //clear old data
    series->clear();
    EMA_series->clear();
    MACD_series->clear();
    RSI_series->clear();
    axisX->clear();
    chart->setTitle(evolutionCours->getPaireDevises()->toString() + " en " + cours->getDate().toString("yyyy"));
    chartRSI->setTitle("RSI " + evolutionCours->getPaireDevises()->toString() + " en " + cours->getDate().toString("yyyy"));
    QList<QAbstractSeries*> liste_series = chart->series();
    for (int i=0; i<liste_series.count(); i++) {
        chart->removeSeries(liste_series[i]);
    }
    if(chartRSI->series().count() == 1) {
            chartRSI->removeSeries(RSI_series);
    }
    //add new data
    Indicateur::iterator emaIterator, macdIterator, rsiIterator;
    QStringList dates;
    dates << firstdate.toString("dd/MM");
    int i = 0;
    double yMin = cours->getLow();
    double yMax = cours->getHigh();
    for (; cours->getDate() <= lastdate; cours++){
            if (cours->getHigh() > yMax) yMax = cours->getHigh();                           //mesure range of y axis
            if (cours->getLow() < yMin) yMin = cours->getLow();
            Bougie* bougie = new Bougie(cours->getOpen(), cours->getHigh(), cours->getLow(), cours->getClose(), cours);
            //QObject::connect(bougie, SIGNAL(clickBougie(Bougie*)), this, SLOT(showCoursOHLCV(Bougie*)));
            series->append(bougie);
            //Indicateur series
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
            rsiIterator = rsi->searchIndice(cours);
            if(!rsiIterator) {
                RSI_series->append(i, 0);
            }
            else {
                RSI_series->append(i, rsiIterator->getIndice());
            }
            i++;

            dates << cours->getDate().toString("dd/MM");
            if (cours == currentCours) break;       //only show up to current cours
    }
    dates << lastdate.toString("dd/MM");
    axisX->append(dates);
    axisY->setRange(yMin*0.9, yMax*1.1);
    chart->addSeries(series);
    if(EMA_series->isVisible()) chart->addSeries(EMA_series);
    if(MACD_series->isVisible()) chart->addSeries(MACD_series);
    chart->setAxisX(axisX,series);
    chart->setAxisY(axisY,series);
    qDebug() << "get here";
    chartRSI->addSeries(RSI_series);
    chartRSI->setAxisX(axisX,RSI_series);
    chartRSI->setAxisY(RSI_axisY,RSI_series);
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
/*
void EvolutionViewer::resizeEvent(QResizeEvent *event) {
    chartView->resize(this->width(), this->height()*7/10);
    //scrollBar->resize(this->width(), this->height()*1/10);
    chartViewRSI->resize(this->width(), this->height()*2/10);
}
*/
