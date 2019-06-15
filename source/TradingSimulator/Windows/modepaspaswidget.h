#ifndef MODEPASPASWIDGET_H
#define MODEPASPASWIDGET_H

/**
 * \file 	modepaspaswidget.h
 * \brief 	classe modeManuelWidget
 * 	
 * 	Contient le QWidget du mode Manuel
 * 			
 */

#include "../Controller/simulation.h"
#include <QWidget>
#include <QMessageBox>

namespace Ui {
    class ModePasPaswidget;
}

/**
* \class ModePasPaswidget
* \brief hérite de QWidget
* attributs : ui, modeManuel, transactionManager
* méthode publique : modePas_Pas, ~ModePas_Pas, updateData
* signal public : transactionChanged
* slots privés : on_comboBox_timer_currentIndexChanged, on_goBack_clicked, updateCurrentCours, on_pushButton_achat_clicked, on_pushButton_annulerTransaction_clicked, on_pushButton_vente_clicked
*/
class ModePasPaswidget : public QWidget {
    Q_OBJECT
public:
	//! Constructeur explicite
	/**
	* \param modePas_Pas :ModePas_Pas**
	* \param parent :QWidget*
	*/
    explicit ModePasPaswidget(ModePas_Pas* modePas_Pas, QWidget *parent = nullptr);
    //! Destructeur
	~ModePasPaswidget();
    //! Mettre à jour les données sur le panneau
	/**
	* \return void : pour mettre à jour les données 
	*/
    void updateData();
signals:
	//! signal transactionChanged
	/**
    * \return void : signale l'ajout ou annule d'une transaction
	*/
    void transactionChanged();
private slots:
    //! Mettre à jour le cours actuel
	/**
    * \return void : pour la mise à jour après le cours changé apres une itération
	*/
    void updateCurrentCours();
    //! Roll back à un jour dans le passé
	/**
	* \return void : pour revenir en arrière
	*/
    void on_goBack_clicked();
    //! Changer l'interval de temps
	/**
	* \param index :int
	* \return void : pour le changement au niveau du timer (avancer, reculer...)
	*/
    void on_comboBox_timer_currentIndexChanged(const QString &arg1);
    //! Redaction quand le bouton achat est appuyé
	/**
	* \return void : pour la demande d'achat
	*/
    void on_pushButton_achat_clicked();
    //! Redaction quand le bouton vente est appuyé
	/**
	* \return void : pour la demande de vente
	*/
    void on_pushButton_vente_clicked();
    //! Redaction quand le bouton annuler est appuyé
	/**
	* \return void : pour la demande d'annuler la transaction
	*/
    void on_pushButton_annulerTransaction_clicked();

private:
    Ui::ModePasPaswidget *ui; /**< ui :ModePasPaswidget* instance de ModePasPaswidget*/
    ModePas_Pas* modePas_Pas; /**< modePas_Pas :ModePas_Pas instance de la classe gérant le mode pas à pas*/
    TransactionManager* transactionManager; /**< transactionManager :TransactionManager* pour gérer les transactions */
};

#endif // MODEPASPASWIDGET_H
