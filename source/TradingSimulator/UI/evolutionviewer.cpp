#include "evolutionviewer.h"

EvolutionViewer::EvolutionViewer(EvolutionCours& evolutionCours,QWidget *parent): QWidget(parent), evolutionCours(evolutionCours){
    //installer la serie
    series = new QCandlestickSeries(this);
    series->setName(evolutionCours.getPaireDevises()->toString());
    series->setIncreasingColor(QColor(Qt::green));
    series->setDecreasingColor(QColor(Qt::red));
    //ajouter des bougies
    QStringList categories;
    for (EvolutionCours::iterator coursIterator=evolutionCours.begin(); coursIterator!=evolutionCours.cend(); coursIterator++){
        Bougie* bougie = new Bougie(coursIterator->getOpen(), coursIterator->getHigh(), coursIterator->getLow(), coursIterator->getClose(), coursIterator);
        QObject::connect(bougie, SIGNAL(clickBougie(Bougie*)), this, SLOT(showCoursOHLCV(Bougie*)));
        series->append(bougie);
        categories << coursIterator->getDate().toString("yy.MM");
    }
    //installer chart
    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Cours OHLC");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->createDefaultAxes();
    QBarCategoryAxis *axisX = new QBarCategoryAxis;
    axisX->append(categories);
    chart->setAxisX(axisX,series);
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
