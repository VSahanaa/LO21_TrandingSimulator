#ifndef MAININTERFACE_H
#define MAININTERFACE_H

/**
 * \file 	maininterface.h
 * \brief 	classes NoteItem, MainInterface
 * 	
 * 	Contient le QListWidgetItem pour la prise de note et le QWidget pour l'interface prinicpal
 * 			
 */
#include "../Controller/simulation.h"
#include "../Chart/evolutionviewer.h"
#include "configuration.h"
#include "modemanuelwidget.h"
#include "modepaspaswidget.h"
#include "modeautowidget.h"
#include "addindicateurdialog.h"
#include "info.h"
#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
    class MainInterface;
    class NoteItem;
}

/**
* \class NoteItem
* \brief hérite de QListWidgetItem, interface représentant les informations lors du lancement de l'application
* attributs : note
* méthodes publiques : NoteItem, getNote
*/
class NoteItem: public QListWidgetItem {
    Note* note; /**< note :Note* pour prendre des notes via la classe Note*/
public:
    //! Constructeur
    /**
    * \param note :Note*
    * \param parent :QListWidget*
    * \param type :int
    */
    NoteItem (Note* note, QListWidget* parent=nullptr, int type=0) : QListWidgetItem(parent, type), note(note) {}
    //! méthode getNote
    /**
    * \return Note* : renvoie la valeur de l'attribut note
    */
    Note* getNote() {return note;}
};

/**
* \class MainInterface
* \brief QObject, hérite de QWidget, interface principal pour les simulations
* attributs : note
* méthodes publiques : NoteItem, getNote
*/
class MainInterface : public QWidget {
    Q_OBJECT
public:
    //! Constructeur explicite
    /**
    * \param parent :QWidget*
    */
    explicit MainInterface(QWidget *parent = nullptr);
    //! Destructeur
    ~MainInterface();
signals:
    //! Signal giveName
    /**
    * \param nom :QString
    * \return void : quand un nom est donné
    */
    void giveName(QString nom);
private slots:
    //! slot newSimulation
    /**
    * \return void : pour dréer une nouvelle simulation
    */
    void newSimulation();
    //! slot showSimulation
    /**
    * \return void : pour montrer la simulation
    */
    void showSimulation();
    //! slot on_newSimulation_button_clicked
    /**
    * \return void : pour la demande d'une nouvelle simulation
    */
    void on_newSimulation_button_clicked();
    //! slot endSimulationMessage
    /**
    * \return void : pour afficher un message en fin de simulation
    */
    void endSimulationMessage();
    //! slot updateGraph
    /**
    * \return void : pour mettre à jour les graphiques
    */
    void updateGraph();
    //! slot updateTransactionTable
    /**
    * \return void : pour mettre à jour le tableau de transactions
    */
    void updateTransactionTable();
    //! slot on_chargeSimulation_button_clicked
    /**
    * \return void : pour la demande de charger une simulation
    */
    void on_chargeSimulation_button_clicked();
    //! slot on_save_clicked
    /**
    * \return void : pour la demande de sauvegarder
    */
    void on_save_clicked();
    //! slot on_addNote_clicked
    /**
    * \return void : pour la demande d'ajout de notes
    */
    void on_addNote_clicked();
    //! slot on_listNote_itemDoubleClicked
    /**
    * \param item :QListWidgetItem
    * \return void : pour la demande d'afficher la liste de notes
    */
    void on_listNote_itemDoubleClicked(QListWidgetItem *item);
    //! slot on_nameEdit_editingFinished
    /**
    * \return void : pour la fin de l'édition du nom
    */
    void on_nameEdit_editingFinished();
    //! slot on_pushButton_2_clicked
    /**
    * \return void : pour la prise de notes
    */
    void on_pushButton_2_clicked();
    //! slot on_closeNote_clicked
    /**
    * \return void : pour la demander de fermer la prise de notes
    */
    void on_closeNote_clicked();
    //! slot on_noteEdit_textChanged
    /**
    * \return void : pour la modification de la note choisie
    */
    void on_noteEdit_textChanged();
    //! slot on_deleteSimulation_clicked
    /**
    * \return void : pour la demande de supprimer la simulation
    */
    void on_deleteSimulation_clicked();
    //! slot on_ema_stateChanged
    /**
    * \return void : pour l'affichage ou non de l'EMA
    */
    void on_ema_stateChanged(int arg1);
    //! slot on_macd_stateChanged
    /**
    * \return void : pour l'affichage ou non du MACD
    */
    void on_macd_stateChanged(int arg1);
    //! slot on_rsi_clicked
    /**
    * \return void : pour l'affichage ou non du RSI
    */
    void on_rsi_clicked();
    //! slot on_pushButton_clicked
    /**
    * \return void : pour la fenetre d'informations
    */
    void on_pushButton_clicked();

private:
    Ui::MainInterface *ui; /**< ui :MainInterface* instance de MainInterface*/
    Simulation* simulation = nullptr; /**< simulation :Simulation* pointe sur la simulation en cours*/
    NoteItem* currentNote = nullptr; /**< currentNote :NoteItem* pointe sur les notes prises/qui vont être prises*/
    Configuration* configuration; /**< configuration :Configuration* pointe sur le menu principal avant lancement de la simulation */
    QWidget* controlPanel; /**< controlPanel :QWidget* pointe sur un panneau de contrôle*/
    EvolutionViewer* evolutionViewer; /**< evolutionViewer :EvolutionViewer* pointe sur l'object EvolutionViewer qui permet de représenter une série de cours sous forme de graphe*/
    VolumeViewer* volumeViewer; /**< evolutionViewer :EvolutionViewer* pointe sur l'object VolumeViewer qui permet de représenter une série de volume sous forme de graphe*/
    //QWidget* ROI_Viewer;
};

#endif // MAININTERFACE_H
