#ifndef MODEMANUELWIDGET_H
#define MODEMANUELWIDGET_H

/**
 * \file 	modeautowidget.h
 * \brief 	classe modeManuelWidget dans le namespace Ui
 * 	
 * 	Contient le QWidget du mode Manuel
 * 			
 */

#include <QWidget>
#include <QMessageBox>
#include "Controller/simulation.h"

//! Namespace Ui
/**
* classe : modeManuelWidget
*/
namespace Ui {
    class modeManuelWidget;
}

/**
* \class modeManuelWidget
* \brief hérite de QWidget
* attributs : ui, modeManuel, transactionManager, coursPicked
* méthode publique : modeManuelWidget, ~modeManuelWidget, updateData
* signal public : transactionChanged
* slots privés : on_pushButton_achat_clicked, on_pushButton_annulerTransaction_clicked, on_pushButton_vente_clicked
* slot public : setCoursPicked
*/
class modeManuelWidget : public QWidget {
    Q_OBJECT
    Ui::modeManuelWidget *ui; /**< ui :modeManuelWidget* instance de modeManuelWidget*/
    ModeManuel* modeManuel; /**< modeManuel :modeManuel* pointe sur la classe gérant le mode manuel*/
    TransactionManager* transactionManager; /**< transactionManager :TransactionManager* pointe sur la classe gérant les transactions*/
    CoursOHLCV* coursPicked; /**< coursPicked :coursOHLV* pointe sue le cours OHLCV choisi*/
public:
	//! Constructeur explicite
	/**
	* \param modeManuel :ModeManuel*
	* \param parent :QWidget*
	*/
    explicit modeManuelWidget(ModeManuel* modeManuel, QWidget *parent = nullptr);
    //! Destructeur
	~modeManuelWidget();
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
public slots:
	//! slot setCoursPicked
	/**
	* \param cours :CoursOHLCV*
	* \return void : pour le choix du cours OHLCV
	*/
    void setCoursPicked(CoursOHLCV* cours);

};

#endif // MODEMANUELWIDGET_H
