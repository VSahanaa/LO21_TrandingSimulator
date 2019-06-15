#ifndef CONFIGURATION_H
#define CONFIGURATION_H

/**
 * \file 	configuration.h
 * \brief 	classe Configuration
 * 	
 * 	Contient le QDialog pour le menu principal (lors du lancement de l'application)
 * 			
 */

#include <QDialog>
#include <QFileDialog>
#include "adddevise_dialog.h"
#include "../Chart/evolutionviewer.h"
#include "../Controller/simulation.h"

namespace Ui {
    class Configuration;
}

/**
* \class Configuration
* \brief QObject, hérite de QDialog, interface représentant le menu principal pour la simulation lors du lancement de l'application
* attributs : ui, newDevise, addDevise_dialog, evolutionCours, simulation, strategieFactory, modeSimulation, nomSimulation,
dateDebut, pourcentage, montantBaseInitial, montantContrepartieInitial, parameters
* méthodes publiques : Configuration, ~Configuration, getSimulation
* méthodes privées : setListesDevise, setEvolutionCours, refreshStrategieLayout, createSimulation
* slots privés : on_ModeAuto_buton_clicked, on_ModeManule_button_clicked, on_ModePas_Pas_button_clicked, on_addDevise_button_clicked, on_back_button_clicked, on_browseButton_clicked, on_creatSimul_button_clicked, on_listeStrategie_currentTextChanged
*/
class Configuration : public QDialog {
    Q_OBJECT
public:
    //! Constructeur explicite
    /**
    *\param parent :QWidget*
    */
    explicit Configuration(QWidget *parent = nullptr);
    //! Destructeur
    ~Configuration();
    //! méthode getSimulation
    /**
    * \return Simulation* : renvoie la simulation créée, la valeur de l'attrinbut simulation
    */
    Simulation* getSimulation() const {return simulation;}
private slots:
    //! slot on_addDevise_button_clicked
    /**
    * \return void : pour le clique du bouton pour ajouter une devise
    */
    void on_addDevise_button_clicked();
    //! slot on_browseButton_clicked
    /**
    * \return void : pour le clique du bouton de choix de fichier
    */
    void on_browseButton_clicked();
    //! slot on_ModeManule_button_clicked
    /**
    * \return void : pour le choix du mode manuel en cliquant sur le bouton correspondant
    */
    void on_ModeManule_button_clicked();
    //! slot on_ModePas_Pas_button_clicked
    /**
    * \return void : pour le choix du mode pas à pas en cliquant sur le bouton correspondant
    */
    void on_ModePas_Pas_button_clicked();
    //! slot on_ModeAuto_buton_clicked
    /**
    * \return void : pour le choix du mode automatique en cliquant sur le bouton correspondant
    */
    void on_ModeAuto_buton_clicked();
    //! slot on_listeStrategie_currentTextChanged
    /**
    * \param strategieNom :const QString&
    * \return void : pour le choix de la strategie
    */
    void on_listeStrategie_currentTextChanged(const QString &strategieNom);
    //! slot on_creatSimul_button_clicked
    /**
    * \return void : pour la création de la simulation
    */
    void on_creatSimul_button_clicked();
    //! slot on_creatSimul_button_clicked
    /**
    * \return void : pour revenir en arrière
    */
    void on_back_button_clicked();

private:
    Ui::Configuration *ui; /**< ui :Configuration* instance de Configuration*/
    AddDevise_Dialog* addDevise_dialog; /**< addDevise_dialog :AddDevise_Dialog* instance de AddDevise_Dialog, fenêtre QDialog pour ajouter une devise*/          //child widget of Configuration
    EvolutionCours* evolutionCours = nullptr; /**< evolutionCours :EvolutionCours* pointe sur la série de cours associée à la simulation */
    Simulation* simulation = nullptr; /**<simulation :Simulation* pointe sur la simulation choisie*/
    StrategieFactory* strategieFactory = StrategieFactory::getStrategieFactory(); /**< strategieFactory :StrategieFactory* pointe dur l'instance StrategieFactory pour avoir les stratégies*/
    QString modeSimulation; /**< modeSimulation :QString contient le mode de simulation choisie*/
    QString nomSimulation; /**< nomSimulation :QString contient le nom de simulation fourni*/
    QDate dateDebut; /**< dateDebut :QDate contient la date à laquelle commencera la simulation*/
    double pourcentage = 0.001; /**< pourcentage :double représente le broker*/
    double montantBaseInitial = 0; /**< montantBaseInitial :double représente le montant de base initial pour la simulation*/
    double montantContrepartieInitial = 1000000; /**< montantContrepartieInitial :double représente le montant de contrepartie initial pour la simulation*/
    Strategie* strategie = nullptr; /**< strategie : Strategie* pointe sur la stratégie choisie ou créée*/
    QMap<QString, QVariant> parameters; /**< parameters :QMap<QString,QVariant> pour les paramètres de la simulation*/
    //! méthode setListesDevise
    /**
    * \return void : permet de montrer la liste de devises disponibles
    */
    void setListesDevise();
    //! méthode setListesDevise
    /**
    * \return void : permet de montrer la liste de cours disponibles
    */
    void setEvolutionCours();
    //! méthode setListesDevise
    /**
    * \return void : permet de finir la selection de la serie de cours et de passer à la configuration des paramètres
    */
    void finishConfigEvolutionCours();      //set evolutionCours and move to set parameters of simulation
    //! méthode refreshStrategieLayout
    /**
    * \param strategieNom :QString
    * \return void : permet mettre à jour le choix de stratégie
    */
    void refreshStrategieLayout(QString strategieNom);
    //! méthode createSimulation
    /**
    * \return void : permet créer la simulation
    */
    void createSimulation();
};

#endif // CONFIGURATION_H
