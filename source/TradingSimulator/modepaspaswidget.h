#ifndef MODEPASPASWIDGET_H
#define MODEPASPASWIDGET_H

/**
 * \file 	modepaspaswidget.h
 * \brief 	classe modeManuelWidget dans le namespace Ui
 * 	
 * 	Contient le QWidget du mode Manuel
 * 			
 */

#include "Controller/simulation.h"
#include <QWidget>
#include <QMessageBox>

//! Namespace Ui
/**
* classe : ModePasPaswidget
*/
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
	//! slot updateData
	/**
	* \return void : pour mettre à jour les données 
	*/
    void updateData();
signals:
	//! signal transactionChanged
	/**
	* \return void : signale le changement de transaction (précédente à la suivante)
	*/
    void transactionChanged();
private slots:
	//! slot updateCurrentCours
	/**
	* \return void : pour la mise à jour après le choix du cours OHLCV
	*/
    void updateCurrentCours();
	//! on_goBack_clicked
	/**
	* \return void : pour revenir en arrière
	*/
    void on_goBack_clicked();
	//! slot on_comboBox_timer_currentIndexChanged
	/**
	* \param index :int
	* \return void : pour le changement au niveau du timer (avancer, reculer...)
	*/
    void on_comboBox_timer_currentIndexChanged(const QString &arg1);
	//! slot on_pushButton_achat_clicked
	/**
	* \return void : pour la demande d'achat
	*/
    void on_pushButton_achat_clicked();
	//! slot on_pushButton_vente_clicked
	/**
	* \return void : pour la demande de vente
	*/
    void on_pushButton_vente_clicked();
	//! slot on_pushButton_annulerTransaction_clicked
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
