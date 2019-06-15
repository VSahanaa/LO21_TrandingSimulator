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
    //! Note référencé
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
    //! Envoyer le nom de la simulation à la tab de Fenetre principale
    /**
    * \param nom :QString
    * \return void : Donner le nom de simulation
    */
    void giveName(QString nom);
private slots:
    //! Charger la simulation
    /**
    * \return void : charger la nouvelle simulation
    */
    void newSimulation();
    //! Afficher la simulation sur l'interface
    /**
    * \return void : pour montrer la simulation
    */
    void showSimulation();
    //! Redaction quand le bouton New Simulation est appuyé
    /**
    * \return void : pour la demande d'une nouvelle simulation
    */
    void on_newSimulation_button_clicked();
    //! Redaction quand la simulation finit
    /**
    * \return void : pour afficher un message en fin de simulation
    */
    void endSimulationMessage();
    //! Mettre à jour les graphiques
    /**
    * \return void : pour mettre à jour les graphiques
    */
    void updateGraph();
    //! Mettre à jour le tableau de Transaction
    /**
    * \return void : pour mettre à jour le tableau de transactions
    */
    void updateTransactionTable();
    //! Redaction quand le bouton Charge Simulation est appuyé
    /**
    * \return void : pour la demande de charger une simulation
    */
    void on_chargeSimulation_button_clicked();
    //! Redaction quand le bouton Sauvegarder est appuyé
    /**
    * \return void : pour la demande de sauvegarder
    */
    void on_save_clicked();
    //! Redaction quand le bouton New note est appuyé
    /**
    * \return void : pour la demande d'ajout de notes
    */
    void on_addNote_clicked();
    //! Choisir un note à afficher
    /**
    * \param item :QListWidgetItem
    * \return void : pour la demande d'afficher la liste de notes
    */
    void on_listNote_itemDoubleClicked(QListWidgetItem *item);
    //! Redaction quand le nom de note est chargé
    /**
    * \return void : pour la fin de l'édition du nom
    */
    void on_nameEdit_editingFinished();
    //! Supprimer un note
    /**
    * \return void : supprimer un note
    */
    void on_pushButton_2_clicked();
    //! Fermer un note
    /**
    * \return void : pour la demander de fermer la prise de notes
    */
    void on_closeNote_clicked();
    //! Redaction quand le note est chargé
    /**
    * \return void : pour la modification de la note choisie
    */
    void on_noteEdit_textChanged();
    //! Redaction quand le bouton Delete Simulation est appuyé
    /**
    * \return void : pour la demande de supprimer la simulation
    */
    void on_deleteSimulation_clicked();
    //! Activer ou désactiver indicateur EMA
    /**
    * \return void : pour l'affichage ou non de l'EMA
    */
    void on_ema_stateChanged(int arg1);
    //! Activer ou désactiver indicateur MACD
    /**
    * \return void : pour l'affichage ou non du MACD
    */
    void on_macd_stateChanged(int arg1);
    //! Changer les paramètres de RSI
    /**
    * \return void : pour l'affichage ou non du RSI
    */
    void on_rsi_clicked();
    //! Afficher le dialog Info
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
};

#endif // MAININTERFACE_H
