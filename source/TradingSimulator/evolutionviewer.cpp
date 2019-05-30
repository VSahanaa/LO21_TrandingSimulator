#include "evolutionviewer.h"

EvolutionViewer::EvolutionViewer(EvolutionCours& evolutionCours,QWidget *parent): QWidget(parent), evolutionCours(evolutionCours){
    //series->setName(evolutionCours.getPaireDevises().toString());
    int i = 0;
    for (EvolutionCours::iterator coursIterator=evolutionCours.begin(); coursIterator!=evolutionCours.cend(); coursIterator++){
        if(!series) {
            series = new csSeriesBrowser(coursIterator->getDate(), i++);
            series->setCurrent(new QCandlestickSeries(this));
            series->getCurrent()->setIncreasingColor(QColor(Qt::green));
            series->getCurrent()->setDecreasingColor(QColor(Qt::red));
            labels.append(series->getName());
            series->getCurrent()->setName(evolutionCours.getName());
        } // premiere serie
        else if(!series->isSameMonth(coursIterator->getDate().year(), coursIterator->getDate().month())){
            csSeriesBrowser *newBser = new csSeriesBrowser(coursIterator->getDate(), i++);
            newBser->setCurrent(new QCandlestickSeries(this));
            newBser->getCurrent()->setIncreasingColor(QColor(Qt::green));
            newBser->getCurrent()->setDecreasingColor(QColor(Qt::red));
            newBser->setLast(series);
            series->setNext(newBser);
            series = newBser;
            labels.append(series->getName());
            series->getCurrent()->setName(evolutionCours.getName());
        } // passer a serie suivante
        Bougie* bougie = new Bougie(coursIterator->getOpen(), coursIterator->getHigh(), coursIterator->getLow(), coursIterator->getClose(), coursIterator);
        QObject::connect(bougie, SIGNAL(clickBougie(Bougie*)), this, SLOT(showCoursOHLCV(Bougie*)));
        series->getCurrent()->append(bougie);
        series->appendCatego(coursIterator->getDate().toString("dd"));
    }
    setNbSeries(i-1);
    //installer chart
    chart = new QChart();
    chart->addSeries(series->getCurrent());
    chart->setTitle(series->getName());
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->createDefaultAxes();
    QBarCategoryAxis *axisX = new QBarCategoryAxis;
    axisX->append(series->getAxis());
    chart->setAxisX(axisX,series->getCurrent());
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    //installer chartView
    chartView = new QChartView(chart, this);
    chartView->setFixedSize(1000, 600);

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

    coucheCours = new QVBoxLayout;
    coucheCours->addLayout(formLayout);
    coucheCours->addWidget(saveButton);
    fenetre = new QHBoxLayout;
    fenetre->addWidget(chartView);
    fenetre->addLayout(coucheCours);
    this->setLayout(fenetre);
}

void EvolutionViewer::changeChart(int i){
    if((i>=0)&&(i<=nb_series))
    {
        chart->removeSeries(series->getCurrent());
        while(series->getIndex()>i){
            series = series->getLast();
        }
        while(series->getIndex()<i){
            series = series->getNext();
        }
        chart->addSeries(series->getCurrent());
        chart->setTitle(series->getName());
        chart->createDefaultAxes();
        QBarCategoryAxis *axisX = new QBarCategoryAxis;
        axisX->append(series->getAxis());
        chart->setAxisX(axisX,series->getCurrent());
    }
}

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
    if(last_bougie_clicked){
        last_bougie_clicked->getCoursOHLCV().setCours(o,h,l,c);
        last_bougie_clicked->setOpen(o);
        last_bougie_clicked->setHigh(h);
        last_bougie_clicked->setLow(l);
        last_bougie_clicked->setClose(c);
    }
    evolutionCours.saveFile();
}
