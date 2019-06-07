#include "evolutionviewer.h"

EvolutionViewer::EvolutionViewer(EvolutionCours* evolutionCours, EvolutionCours::iterator currentCours, QWidget* parent) : QWidget (parent), evolutionCours(evolutionCours), currentCours(currentCours) {
    setMouseTracking(true);
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
    chartRSI->legend()->setVisible(true);
    chartRSI->legend()->setAlignment(Qt::AlignBottom);
    chartRSI->createDefaultAxes();
    chartViewRSI = new  QChartView(chartRSI, this);

    scrollBar = new QScrollBar(Qt::Horizontal, this);
    scrollBar->setMinimum(0);
    int i = 0;
    EvolutionCours::iterator cours = currentCours;
    while(i < maxDateShown) {
        if(cours == evolutionCours->begin()) break;
        i++;
        cours --;
    }
    scrollBar->setMaximum(evolutionCours->begin()->getDate().daysTo(cours->getDate()));      //sync scroll bar with time range

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

    RSI_overbought = new QLineSeries();
    RSI_overbought->setName("over bought");
    RSI_overbought->setColor(Qt::green);
    RSI_overbought->setVisible(true);

    RSI_oversold = new QLineSeries();
    RSI_oversold->setName("over sold");
    RSI_oversold->setColor(Qt::red);
    RSI_oversold->setVisible(true);

    rsi->generateIndice();
    axisX = new QBarCategoryAxis;
    axisY= new QValueAxis;
    RSI_axisX = new QBarCategoryAxis;
    RSI_axisY = new QValueAxis;
    RSI_axisY->setRange(0,100);
    //binding sigals
    QObject::connect(scrollBar, SIGNAL(valueChanged(int)), this, SLOT(updateChart(int)));
    QObject::connect(this, SIGNAL(currentCours_changed()), this, SLOT(currentCoursChanged_react()));

    if(scrollBar->maximum() == 0) {updateChart(0);}
    scrollBar->setValue(scrollBar->maximum());
}

EvolutionViewer::~EvolutionViewer() {
    clearCharts();
    delete EMA_series;
    delete MACD_series;
    delete RSI_series;
    delete RSI_overbought;
    delete RSI_oversold;
    delete axisX;
    delete RSI_axisX;
    delete axisY;
    delete RSI_axisY;
    delete chart;
    delete chartView;
    delete chartRSI;
    delete scrollBar;
    delete layout;
}

void EvolutionViewer::clearCharts(){
    //clear old data
    series->clear();
    EMA_series->clear();
    MACD_series->clear();
    RSI_series->clear();
    RSI_oversold->clear();
    RSI_overbought->clear();
    axisX->clear();
    RSI_axisX->clear();
    QList<QAbstractSeries*> liste_series = chart->series();
    for (int i=0; i<liste_series.count(); i++) {
        chart->removeSeries(liste_series[i]);
    }
    if(chartRSI->series().count() == 3) {
            chartRSI->removeSeries(RSI_series);
            chartRSI->removeSeries(RSI_overbought);
            chartRSI->removeSeries(RSI_oversold);
    }
}

void EvolutionViewer::showChart(QDate firstdate, QDate lastdate) {
    clearCharts();
    EvolutionCours::iterator cours = evolutionCours->searchCours(firstdate);
    qDebug() << firstdate.toString("yyyy");
    chart->setTitle(evolutionCours->getPaireDevises()->toString() + " en " + cours->getDate().toString("yyyy"));
    chartRSI->setTitle("RSI " + evolutionCours->getPaireDevises()->toString() + " en " + cours->getDate().toString("yyyy"));

    //add new data
    Indicateur::iterator emaIterator, macdIterator, rsiIterator;
    QStringList dates;
    dates << firstdate.toString("dd/MM");
    int i = 0;
    double yMin = cours->getLow();
    double yMax = cours->getHigh();
    QMap<QString, QVariant> RSI_parameters = rsi->getParameters();
    for (; cours->getDate() <= lastdate; cours++){
        if (cours->getHigh() > yMax) yMax = cours->getHigh();                           //mesure range of y axis
        if (cours->getLow() < yMin) yMin = cours->getLow();
        Bougie* bougie = new Bougie(cours->getOpen(), cours->getHigh(), cours->getLow(), cours->getClose(), cours);
        QObject::connect(bougie, SIGNAL(clickBougie(CoursOHLCV*)), this, SLOT(pickCours(CoursOHLCV*)));
        QObject::connect(bougie, SIGNAL(hoverBougie(QString)), this, SLOT(analyseForm(QString)));
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
        RSI_overbought->append(i, 80/* RSI_parameters["overboughtBound"].toDouble()*/);
        RSI_oversold->append(i, 20 /*RSI_parameters["oversoldBound"].toDouble()*/);
        i++;
        dates << cours->getDate().toString("dd/MM");
        if (cours == currentCours) break;       //only show up to current cours
    }
    axisX->append(dates);
    RSI_axisX->append(dates);
    axisY->setRange(yMin*0.98, yMax*1.02);
    chart->addSeries(series);
    if(EMA_series->isVisible()) chart->addSeries(EMA_series);
    if(MACD_series->isVisible()) chart->addSeries(MACD_series);
    chart->setAxisX(axisX,series);
    chart->setAxisY(axisY,series);
    chartRSI->addSeries(RSI_series);
    chartRSI->addSeries(RSI_overbought);
    chartRSI->addSeries(RSI_oversold);
    chartRSI->setAxisX(RSI_axisX,RSI_series);
    chartRSI->setAxisY(RSI_axisY,RSI_series);
}

void EvolutionViewer::updateChart(int value) {
    QDate firstDateShowed = evolutionCours->begin()->getDate().addDays(value);
    qDebug() << firstDateShowed.toString("yy.MM.dd")<<endl;
    showChart(firstDateShowed, firstDateShowed.addDays(maxDateShown));
}

void EvolutionViewer::currentCoursChanged_react() {
    int old_maximum = scrollBar->maximum();
    int i = 0;
    EvolutionCours::iterator cours = currentCours;
    while(i < maxDateShown) {
        if(cours == evolutionCours->begin()) break;
        i++;
        cours --;
    }
    scrollBar->setMaximum(evolutionCours->begin()->getDate().daysTo(cours->getDate()));
    if(scrollBar->value() == old_maximum) {
        //if user is navigating  => don't update viewport
        if(scrollBar->maximum() == 0) {updateChart(0);}
        scrollBar->setValue(scrollBar->maximum());      //trigger updateChart()
    }
}

void EvolutionViewer::analyseForm(QString form) {
     QToolTip::showText(mapFromGlobal(QCursor::pos()), form, nullptr, QRect(), 50000);
}

/*
void EvolutionViewer::resizeEvent(QResizeEvent *event) {
    chartView->resize(this->width(), this->height()*7/10);
    //scrollBar->resize(this->width(), this->height()*1/10);
    chartViewRSI->resize(this->width(), this->height()*2/10);
}
*/

/* -------------------------------------------------- Methodes de VolumeViewer -------------------------------------------------------------------------------*/
VolumeViewer::VolumeViewer(EvolutionCours* evolutionCours, EvolutionCours::iterator currentCours, QWidget* parent): QWidget(parent), evolutionCours(evolutionCours), currentCours(currentCours) {
    chart = new QChart();
    //chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->createDefaultAxes();
    chartView = new QChartView(chart, this);


    scrollBar = new QScrollBar(Qt::Horizontal, this);
    scrollBar->setMinimum(0);
    int i=0;
    EvolutionCours::iterator cours = currentCours;
    while(i < maxDateShown) {
        if(cours == evolutionCours->begin()) break;
        i++;
        cours --;
    }
    scrollBar->setMaximum(evolutionCours->begin()->getDate().daysTo((cours)->getDate()));      //sync scroll bar with time range

    layout = new QVBoxLayout;
    layout->addWidget(chartView);
    layout->addWidget(scrollBar);
    this->setLayout(layout);

    //set up series
    series =  new QBarSeries();

    axisX = new QBarCategoryAxis;
    axisY= new QValueAxis;
    axisY->setMin(0);
    //binding sigals
    QObject::connect(scrollBar, SIGNAL(valueChanged(int)), this, SLOT(updateChart(int)));
    QObject::connect(this, SIGNAL(currentCours_changed()), this, SLOT(currentCoursChanged_react()));
    if(scrollBar->maximum() == 0) {updateChart(0);}
    scrollBar->setValue(scrollBar->maximum());
}

VolumeViewer::~VolumeViewer() {
    clearCharts();
    delete axisX;
    delete axisY;
    delete chart;
    delete chartView;
    delete scrollBar;
    delete layout;
}


void VolumeViewer::clearCharts(){
    //clear old data
    series->clear();
    axisX->clear();
    if(chart->series().count() == 1) {
        chart->removeSeries(series);
    }
}


void VolumeViewer::showChart(QDate firstdate, QDate lastdate) {
    clearCharts();
    EvolutionCours::iterator cours = evolutionCours->searchCours(firstdate);
    chart->setTitle(evolutionCours->getPaireDevises()->toString() + " en " + cours->getDate().toString("yyyy"));
    unsigned int max = 0;
    QStringList dates;
    QBarSet *volumeSet = new QBarSet("Volume");
    dates << firstdate.toString("dd/MM");
    for (; cours->getDate() <= lastdate; cours++){
        if(max < cours->getVolume()) {
            max = cours->getVolume();
        }
        *volumeSet<<cours->getVolume();
        dates << cours->getDate().toString("dd/MM");
        if (cours == currentCours) break;       //only show up to current cours
    }
    series->append(volumeSet);
    axisX->append(dates);
    axisY->setMax(max*1.01);
    chart->addSeries(series);
    chart->setAxisX(axisX,series);
    chart->setAxisY(axisY,series);
}

void VolumeViewer::updateChart(int value) {
    QDate firstDateShowed = evolutionCours->begin()->getDate().addDays(value);
    qDebug() << firstDateShowed.toString("yy.MM.dd")<<endl;
    showChart(firstDateShowed, firstDateShowed.addDays(maxDateShown));
}

void VolumeViewer::currentCoursChanged_react() {
    int old_maximum = scrollBar->maximum();
    int i=0;
    EvolutionCours::iterator cours = currentCours;
    while(i < maxDateShown) {
        if(cours == evolutionCours->begin()) break;
        i++;
        cours --;
    }
    scrollBar->setMaximum(evolutionCours->begin()->getDate().daysTo(cours->getDate()));
    if(scrollBar->value() == old_maximum) {
        //if user is navigating  => don't update viewport
        if(scrollBar->maximum() == 0) {updateChart(0);}
        scrollBar->setValue(scrollBar->maximum());      //trigger updateChart()
    }
}
