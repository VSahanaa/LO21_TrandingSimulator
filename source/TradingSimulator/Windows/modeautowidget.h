#ifndef MODEAUTOWIDGET_H
#define MODEAUTOWIDGET_H

/**
 * \file 	modeautowidget.h
 * \brief 	classe ModeAutowidget
 * 	
 * 	Contient le QWidget du mode automatique
 * 			
 */

#include "../Controller/simulation.h"
#include <QWidget>

namespace Ui {
    class ModeAutowidget;
}

/**
* \class ModeAutowidget
* \brief hérite de QWidget
* attributs : ui, modeAutomatique, transactionManager
* méthode publique : ModeAutomatique, ~ModeAutomatique
* signal public : transactionChanged
* slots privés : updateData, on_comboBox_timer_currentIndexChanged
*/
class ModeAutowidget : public QWidget {
    Q_OBJECT
public:
	//! Constructeur explicite
	/**
	* \param modeAutomatique :ModeAutomatique*
	* \param parent :QWidget*
	*/
    explicit ModeAutowidget(ModeAutomatique* modeAutomatique, QWidget *parent = nullptr);
    //! Destructeur
	~ModeAutowidget();
signals:
	//! signal transactionChanged
	/**
	* \return void : signale le changement de transaction (précédente à la suivante)
	*/
    void transactionChanged();
private slots:
	//! slot updateData
	/**
	* \return void : pour mettre à jour les données 
	*/
    void updateData();
	//! slot on_comboBox_timer_currentIndexChanged
	/**
	* \param index :int
	* \return void : pour le changement au niveau du timer (avancer, reculer...)
	*/
    void on_comboBox_timer_currentIndexChanged(int index);

    void on_pause_clicked();

    void on_next_clicked();

private:
    Ui::ModeAutowidget *ui; /**< ui :ModeAutowidget* instance de ModeAutowidget*/
    ModeAutomatique* modeAutomatique; /**< modeAutomatique :ModeAutomatique* pointe sur la classe gérant le mode automatique */
    TransactionManager* transactionManager; /**< transactionManager :TransactionManager* pointe sur le manager des transactions */
};

#endif // MODEAUTOWIDGET_H
