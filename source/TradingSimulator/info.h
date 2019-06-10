#ifndef INFO_H
#define INFO_H

/**
 * \file 	info.h
 * \brief 	classe Info dans le namespace Ui
 * 	
 * 	Contient le QDialog pour la fenêtre d'explication (lors du lancement de l'application)
 * 			
 */


#include <QDialog>
#include "ui_info.h"

//! Namespace Ui
/**
* classe : Info
*/
namespace Ui {
    class Info;
}

/**
* \class Info
* \brief QObject, hérite de QDialog, interface représentant les informations lors du lancement de l'application
* attributs : ui
* méthodes publiques : Info, ~Info
*/
class Info : public QDialog {
    Q_OBJECT
public:
	//! Constructeur explicite
	/**
	*\param parent :QWidget*
	*/
    explicit Info(QWidget *parent = nullptr) : QDialog(parent), ui(new Ui::Info) {
        ui->setupUi(this);
        this->setWindowTitle("About");
    }
	//! Destructeur
    ~Info() {
        delete ui;
    }
private:
    Ui::Info *ui; /**< ui :Info* instance de Configuration*/
};

#endif // INFO_H
