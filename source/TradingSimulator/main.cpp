#include "mainwindow.h"
#include "trading.h"
#include "evolutionviewer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    DevisesManager& deviseManager=DevisesManager::getManager();
    deviseManager.creationDevise("USD", "Dollar Américain","USA");
    deviseManager.creationDevise("BTC", "BitCoin","monnaie virtuelle");
    const PaireDevises& BTC_USD=deviseManager.getPaireDevises("BTC", "USD");
    //EvolutionCours evolution(BTC_USD);
    // Une bougie = Un mois pour bitcoin entre janvier 2017 et août 2018
    /*evolution.addCours(4261.48000000, 4745.42000000, 3400.00000000, 4724.89000000, 100000, QDate(2017,1,1));
    evolution.addCours(4689.89000000, 4939.19000000, 2817.00000000, 4378.51000000, 102000, QDate(2017,2,1));
    evolution.addCours(4378.49000000, 6498.01000000, 4110.00000000, 6463.00000000, 95200, QDate(2017,3,1));
    evolution.addCours(6463.00000000, 11300.03000000, 5325.01000000, 9838.96000000, 132021, QDate(2017,4,1));
    evolution.addCours(9837.00000000, 19798.68000000, 9380.00000000, 13716.36000000, 132050, QDate(2017,5,1));
    evolution.addCours(13715.65000000, 17176.24000000, 9035.00000000, 10285.10000000, 132212, QDate(2017,6,1));
    evolution.addCours(10285.10000000, 11786.01000000, 6000.01000000, 10326.76000000, 132021, QDate(2017,7,1));
    evolution.addCours(10325.64000000, 11710.00000000, 6600.10000000, 6923.91000000, 132521, QDate(2017,8,1));
    evolution.addCours(6922.00000000, 9759.82000000, 6430.00000000, 9246.01000000, 202021, QDate(2017,9,1));
    evolution.addCours(9246.01000000, 10020.00000000, 7032.95000000, 7485.01000000, 101021, QDate(2017,10,1));
    evolution.addCours(7485.01000000, 7786.69000000, 5750.00000000, 6390.07000000, 132521, QDate(2017,11,1));
    evolution.addCours(6391.08000000, 8491.77000000, 6070.00000000, 7730.93000000, 123123, QDate(2017,12,1));
    evolution.addCours(7735.67000000, 7750.00000000, 5880.00000000, 7011.21000000, 4564621, QDate(2018,1,1));
    evolution.addCours(7011.21000000, 7410.00000000, 6111.00000000, 6626.57000000, 153212, QDate(2018,2,1));
    evolution.addCours(6626.57000000, 7680.00000000, 6205.00000000, 6371.93000000, 132135, QDate(2018,3,1));
    evolution.addCours(6369.52000000, 6615.15000000, 3652.66000000, 4041.32000000, 234654, QDate(2018,4,1));
    evolution.addCours(4041.27000000, 4312.99000000, 3156.26000000, 3702.90000000, 654612, QDate(2018,5,1));
    evolution.addCours(3701.23000000, 4069.80000000, 3349.92000000, 3434.10000000, 202123, QDate(2018,6,1));
    evolution.addCours(3434.10000000, 4198.00000000, 3373.10000000, 3813.69000000, 321202, QDate(2018,7,1));
    evolution.addCours(3814.26000000, 4140.00000000, 3670.69000000, 4106.65000000, 212313, QDate(2018,8,1));
    */
    EvolutionCours evolution(BTC_USD, ":/TradingSimulator/evolutionCours/fichier_OHLCV/BTC-USD.csv");
    QApplication app(argc, argv);
    EvolutionViewer view(evolution);
    view.show();

    return app.exec();
}
