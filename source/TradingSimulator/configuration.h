#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QDialog>
#include <QFileDialog>
#include "adddevise_dialog.h"
#include "UI/evolutionviewer.h"
#include "Controller/simulation.h"
namespace Ui {
class Configuration;
}

class Configuration : public QDialog {
    Q_OBJECT
public:
    explicit Configuration(QWidget *parent = nullptr);
    ~Configuration();
    Simulation* getSimulation() const {return simulation;}

private slots:
    void on_addDevise_button_clicked();
    void on_browseButton_clicked();
    void on_ModeManule_button_clicked();
    void on_ModePas_Pas_button_clicked();
    void on_ModeAuto_buton_clicked();
    void on_listeStrategie_currentTextChanged(const QString &strategieNom);
    void on_creatSimul_button_clicked();
    void on_back_button_clicked();

private:
    Ui::Configuration *ui;
    AddDevise_Dialog* addDevise_dialog;             //child widget of Configuration
    EvolutionCours* evolutionCours = nullptr;
    Simulation* simulation = nullptr;
    StrategieFactory* strategieFactory = StrategieFactory::getStrategieFactory();
    QString modeSimulation;
    QString nomSimulation;
    QDate dateDebut;
    double pourcentage = 0.001;
    double montantBaseInitial = 0;
    double montantContrepartieInitial = 1000000;
    Strategie* strategie = nullptr;
    QMap<QString, QVariant> parameters;
    void setListesDevise();
    void setEvolutionCours();
    void finishConfigEvolutionCours();      //set evolutionCours and move to set parameters of simulation
    void refreshStrategieLayout(QString strategieNom);
    void createSimulation();
};

#endif // CONFIGURATION_H
