#include "evolutionviewer.h"

bool Bougie::isBigBlackCandle() const {
    /*
    Big Black Candle Has an unusually long black body with a wide range between high and low. Prices open near the high and close near the low.
    */
    if ((open() - close()) >= 0.8*(high() - low())) return true;
        return false;
}

bool Bougie::isBigWhiteCandle() const {
    /*
     * Big White Candle Has an unusually long white body with a wide range between high and low of the day. Prices open near the low and close near the high.
    */
    if ((close() - open()) >= 0.8*(high() - low())) return true;
        return false;
}

bool Bougie::isSpinningTop() const {
    if(abs(open() - close()) <= 0.75*abs(high() - low())) return true;
        return false;

}

bool Bougie::isDoji() const {
    if(isSpinningTop() && abs(close() - open()) <= 0.1 ) return true;
        return false;
}

bool Bougie::isDragonflyDoji() const {
    /*
     * Dragonfly Doji Formed when the opening and the closing prices are at the highest of the day.
     * If it has a longer lower shadow it signals a more bullish trend. When appearing at market bottoms it is considered to be a reversal signal.
     */
    if(isDoji() && open() > high()) return true;
        return false;
}

bool Bougie::isGraveStoneDoji() const {
    /*
     * Gravestone Doji Formed when the opening and closing prices are at the lowest of the day.
     * If it has a longer upper shadow it signals a bearish trend. When it appears at market top it is considered a reversal signal.
     */
    if (isDoji() && open() < low()) return true;
        return false;
}

bool Bougie::isHanngingMan() const {
    /*
     * Hanging Man A black or a white candlestick that consists of a small body near the high with a little or no upper shadow and a long lower tail.
     * The lower tail should be two or three times the height of the body. Considered a bearish pattern during an uptrend.
     */
    if ( ((high() - open()) < 0.1*(high() - low()) || (high() - close()) < 0.1*(high() - low())) && abs(open() - close()) < (1/3)*(high() - low())) return true;
        return false;
}

bool Bougie::isHammer() const {
    /*
     * Hammer A black or a white candlestick that consists of a small body near the high with a little or no upper shadow and a long lower tail.
     * Considered a bullish pattern during a downtrend.
     */
    if ( ((high() - open()) < 0.2*(high() - low()) || (high() - close()) < 0.2*(high() - low())) &&  abs(open() - close()) < (1/2)*(high() - low())) return true;
        return false;
}

bool Bougie::isInvertedHammer() const {
    /*
     * Inverted Hammer A black or a white candlestick in an upside-down hammer position.
     */
    if ( ((open() - low()) < 0.2*(high() - low()) || (close() - low()) < 0.2*(high() - low())) &&  abs(open() - close()) < (1/2)*(high() - low())) return true;
        return false;
}

bool Bougie::isInvertedBlackHammer() const {
    /*
     * Inverted Black Hammer A black body in an upside-down hammer position. Usually considered a bottom reversal signal.
     */
    if (isInvertedHammer() && (open() > close())) return true;
        return false;
}

bool Bougie::isLongLowerShadow() const {
    /*
     * Long Lower Shadow A black or a white candlestick is formed with a lower tail that has a length of 2/3 or more of the total range of the candlestick.
     * Normally considered a bullish signal when it appears around price support levels.
     */
    if(open() > close()) {
        if(close() - low() > (2/3)*(high() - low())) return true;
            return false;
    }
    else {
        if(open() - low() > (2/3)*(high() - low())) return true;
            return false;
    }
}

bool Bougie::isLongUpperShadow() const {
    /*
     * Long Upper Shadow A black or a white candlestick with an upper shadow that has a length of 2/3 or more of the total range of the candlestick.
     * Normally considered a bearish signal when it appears around price resistance levels.
     */
    if(open() > close()) {
        if(high() - open() > (2/3)*(high() - low())) return true;
            return false;
    }
    else {
        if(high() - close() > (2/3)*(high() - low())) return true;
            return false;
    }
}

bool Bougie::isMarubozu() const {
    /*
     * Marubozu A long or a normal candlestick (black or white) with no shadow or tail.
     * The high and the lows represent the opening and the closing prices. Considered a continuation pattern.
     */
    if(abs(open() - close()) == abs(high() - abs(low()))) return true;
        return false;
}

bool Bougie::isShootingStar() const {
    /*
     * Shooting Star A black or a white candlestick that has a small body, a long upper shadow and a little or no lower tail. Considered a bearish pattern in an uptrend
     */
    double delta;
    if ( open() > close()) {
        delta = close() - low();
    }
    else {
        delta = open() - low();
    }
    if (isSpinningTop() && delta <= 0.05*abs(open() - close()) ) return true;
        return false;
}

bool Bougie::isShavenBottom() const {
    /*
     * Shaven Bottom A black or a white candlestick with no lower tail. [Compare with Inverted Hammer.]
     */
    if (open() == low() || close() == low()) return true;
        return false;
}

bool Bougie::isShavenHead() const {
    /*
     * Shaven Head A black or a white candlestick with no upper shadow. [Compared with hammer.]
     */
    if (open() == high() || close() == high()) return true;
        return false;
}

QString Bougie::forme() const {
    QString formeBougie = "";
    if (isBigBlackCandle())  formeBougie += "Big Black Candle \n";
    if (isBigWhiteCandle())  formeBougie += "Big White Candle \n";
    if (isSpinningTop()) formeBougie += "Spinning Top \n";
    if (isDoji()) {
        if (isDragonflyDoji()) {
            formeBougie += "Dragonfly Doji \n";
        }
        else if (isGraveStoneDoji()){
            formeBougie += "Grave Stone Doji \n";
        }
        else {
            formeBougie += "Doji \n";
        }
    }
    if (isHanngingMan()) formeBougie += "Hannging Man \n";
    if (isHammer()) {
        if (isInvertedHammer()) {
            if (isInvertedBlackHammer()) {
                formeBougie += "Inverted Black Hammer \n";
            }
            else {
                formeBougie += "Inverted Hammer \n";
            }
        }
        else {
            formeBougie += "Hammer \n";
        }
     }
    if (isLongLowerShadow()) formeBougie += "Long Lower Shadow \n";
    if (isLongUpperShadow()) formeBougie += "Long Upper Shadow \n";
    if (isMarubozu()) formeBougie += "Marubozu \n";
    if (isShootingStar()) formeBougie += "Shooting Star \n";
    if (isShavenBottom()) formeBougie += "Shaven Bottom \n";
    if (isShavenHead()) formeBougie += "Shaven Head \n";
    return formeBougie;
}






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
