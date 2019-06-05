#include "mainwindow.h"
#include "Core_Devises/trading.h"
#include "UI/evolutionviewer.h"
#include "configuration.h"

#include <QApplication>
#include "UI/welcome.h"


int main(int argc, char *argv[])
{

    DevisesManager& deviseManager=DevisesManager::getManager();
    deviseManager.creationDevise("USD", "Dollar Américain","USA");
    deviseManager.creationDevise("BTC", "BitCoin","monnaie virtuelle");
    const PaireDevises& BTC_USD=deviseManager.getPaireDevises("BTC", "USD");
    EvolutionCours evolution(BTC_USD, ":/TradingSimulator/evolutionCours/fichier_OHLCV/BTC-USD.csv");
    //Indicateur* macd = evolution.getCollection()->getIndicateur("MACD");
    //macd->generateIndice();

    QApplication mainApp(argc, argv);

    VolumeViewer volumeView(&evolution, evolution.end()-1);
    volumeView.show();
    /*
    Configuration* config = new Configuration();
    config->show();
    */
    return mainApp.exec();
}
