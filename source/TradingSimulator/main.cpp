#include "mainwindow.h"
#include "Core_Devises/trading.h"
#include "UI/evolutionviewer.h"
#include "configuration.h"
#include "maininterface.h"
#include <QApplication>
#include "UI/welcome.h"


int main(int argc, char *argv[])
{
    DevisesManager& deviseManager=DevisesManager::getManager();
    deviseManager.creationDevise("USD", "Dollar Américain","USA");
    deviseManager.creationDevise("BTC", "BitCoin","monnaie virtuelle");


    const PaireDevises& BTC_USD=deviseManager.getPaireDevises("BTC", "USD");

    QApplication mainApp(argc, argv);
    QScrollArea* scrollArea = new QScrollArea;

    MainWindow* mainWindow = new MainWindow();
    QObject::connect(mainWindow, SIGNAL(stop()), scrollArea, SLOT(close()));
    scrollArea->setWidget(mainWindow);
    scrollArea->show();

    return mainApp.exec();
}
