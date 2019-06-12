#ifndef ADDINDICATEURDIALOG_H
#define ADDINDICATEURDIALOG_H

/**
 * \file 	addindicateur_dialog.h
 * \brief 	classe AddIndicateurDialog dans le namespace Ui
 * 	
 * 	Contient le QDialog pour ajouter un indicateur (choix parmi ceux implémentés)
 * 			
 */

#include <QDialog>
#include <QMessageBox>
#include "../Core_Devises/trading.h"

//! Namespace Ui
/**
* classe : AddIndicateurDialog
*/
namespace Ui {
    class AddIndicateurDialog;
}

/**
* \class AddIndicateurDialog
* \brief QObject, hérite de QDialog, interface d'ajout d'indicateur
* attributs : ui, indicateur, evolutionCours
* méthodes publiques : AddIndicateurDialog, ~AddIndicateurDialog
* slots privés : on_AddIndicateurDialog_accepted
*/
class AddIndicateurDialog : public QDialog
{
    Q_OBJECT

public:
	//! Constructeur explicite
	/**
	* \param indicateur :QString
	* \param evolutionCours :EvolutionCours*
	* \param parent :QWidget*
	*/
    explicit AddIndicateurDialog(QString indicateur, EvolutionCours* evolutionCours, QWidget *parent = nullptr);
    //! Destructeur
	~AddIndicateurDialog();

private slots:
	//! slot on_AddIndicateurDialog_accepted
	/**
	* \return void : pour le choix d'un indicateur
	*/
    void on_AddIndicateurDialog_accepted();
private:
    Ui::AddIndicateurDialog *ui; /**< ui :Ui::AddDevise_Dialog* instance de AddDevise_Dialog*/
    QString indicateur; /**< indicateur :QString : nom de l'indicateur choisi*/
    EvolutionCours* evolutionCours; /**< evolutionCours :EvolutionCours* pointe sur la série de cours associés*/
};

#endif // ADDINDICATEURDIALOG_H
