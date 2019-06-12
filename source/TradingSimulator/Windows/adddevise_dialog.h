#ifndef ADDDEVISE_DIALOG_H
#define ADDDEVISE_DIALOG_H

/**
 * \file 	adddevise_dialog.h
 * \brief 	classe AddDevise_Dialog dans le namespace Ui
 * 	
 * 	Contient le QDialog pour ajouter une devise
 * 			
 */

#include <QDialog>
#include <QMessageBox>
#include "../Core_Devises/trading.h"

//! Namespace UI
/**
* classe : AddDevise_Dialog
*/
namespace Ui {
    class AddDevise_Dialog;
}

/**
* \class AddDevise_Dialog
* \brief QObject, hérite de QDialog, interface d'ajout de devises
* attributs : ui, newDevise
* méthodes publiques : AddDevise_Dialog, ~AddDevise_Dialog, getNewDevise
* slots privés : on_AddDevise_Dialog_accepted
*/
class AddDevise_Dialog : public QDialog {
    Q_OBJECT
public:
	//! Constructeur explicite
	/**
	* \param parent :QWidget*
	*/
    explicit AddDevise_Dialog(QWidget *parent = nullptr);
	//! Destructeur
    ~AddDevise_Dialog();
	//! méthode getNewDevise
	/**
	* \return const Devise* : renvoie la valeur de l'attribut newDevise
	*/
    const Devise* getNewDevise() const {return newDevise;}
private slots:
	//! slot on_AddDevise_Dialog_accepted
	/**
	* \return void : pour l'ajout d'une devise 
	*/
    void on_AddDevise_Dialog_accepted();
private:
    Ui::AddDevise_Dialog *ui; /**< ui :Ui::AddDevise_Dialog* instance de AddDevise_Dialog*/
    const Devise* newDevise = nullptr; /**< newDevise :const Devise* pointe sur la nouvelle devise*/
};

#endif // ADDDEVISE_DIALOG_H
