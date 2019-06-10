#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/**
 * \file 	mainiwindow.h
 * \brief 	classes MainWindow, SimulationTab dans le namespace Ui
 * 	
 * 	Contient le QTabWidget des simulations et le QMainWindow pour la fenetre prinicpale
 * 			
 */
#include <QMainWindow>
#include "maininterface.h"

//! Namespace Ui
/**
* classe : MainWindow, SimulationTab
*/
namespace Ui {
    class MainWindow;
    class SimulationTab;
}

/**
* \class SimulationTab
* \brief hérite de QTabWidget, tableau de choix de simulation
* méthode publique : SimulationTab
* signal public : closeWindow_request, 
* slots privés : newTab, closeTab, setTabName
*/
class SimulationTab: public QTabWidget{
    Q_OBJECT
public:
	//! Constructeur
	/**
	* \param parent :QWidget*
	*/
    SimulationTab(QWidget* parent);
signals:
	//! signal closeWindow_request
	/**
	* \return void : signal de fermeture de la fenêtre
	*/
    void closeWindow_request();
private slots:
	//! slot newTab
	/**
	* \return void : pour créer le tableau
	*/
    void newTab();
	//! slot closeTab
	/**
	* \param index :int
	* \return void : pour fermer le tableau
	*/
    void closeTab(int index);
	//! slot setTabName
	/**
	* \param nom :QString
	* \return void : pour donner un nom au tableau
	*/
    void setTabName(QString nom) {
        qDebug() << nom;
        setTabText(currentIndex(), nom);}
};

/**
* \class MainWindow
* \brief hérite de QMainWindow, fenêtre principale
* attributs : ui, simulationTabs
* méthode publique : MainWindow, ~MainWindow
* signal public : stop
* slot privé : send_stop
*/
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
	//! Constructeur
	/**
	* \param parent :QWidget*
	*/
    explicit MainWindow(QWidget *parent = nullptr);
	//! Destructeur
    ~MainWindow();
signals:
	//! Signal stop
	/**
	* \return void : signal pour arrêter la simulation
	*/
    void stop();
private slots:
	//! Slot send_stop
	/**
	* \return void : pour demander d'arrêter 
	*/
    void send_stop() {emit stop();}
private:
    Ui::MainWindow *ui; /**< */
    SimulationTab* simulationTabs; /**< */
};

#endif // MAINWINDOW_H
