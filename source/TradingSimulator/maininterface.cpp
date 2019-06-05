#include "maininterface.h"
#include "ui_maininterface.h"

MainInterface::MainInterface(Simulation* simulation, QWidget *parent) : QWidget(parent), ui(new Ui::MainInterface), simulation(simulation) {
    ui->setupUi(this);
    if (simulation->getType() == "Manuel") {
        //Specific element for mode Manuel
        controlPanel = new modeManuelWidget(static_cast<ModeManuel*>(simulation), this);
        evolutionViewer = new EvolutionViewer(simulation->getEvolutionCours(), simulation->getEvolutionCours()->end()-1, this);
        volumeViewer = new VolumeViewer(simulation->getEvolutionCours(), simulation->getEvolutionCours()->end()-1, this);
    }
    else if (simulation->getType() == "Pas_Pas") {
        //Specific element for mode Pas à pas
        controlPanel = new ModePasPaswidget(static_cast<ModePas_Pas*>(simulation), this);
        evolutionViewer = new EvolutionViewer(simulation->getEvolutionCours(), simulation->getCurrentCours(), this);
        volumeViewer = new VolumeViewer(simulation->getEvolutionCours(), simulation->getCurrentCours(), this);
    }
    else if (simulation->getType() == "Automatique") {
        //Specific element for mode Automatique
        controlPanel = new ModeAutowidget(static_cast<ModeAutomatique*>(simulation), this);
        evolutionViewer = new EvolutionViewer(simulation->getEvolutionCours(), simulation->getCurrentCours(), this);
        volumeViewer = new VolumeViewer(simulation->getEvolutionCours(), simulation->getCurrentCours(), this);
    }
    else {
        throw TradingException("type simulation invalid");
    }
    ui->controlPanel->addWidget(controlPanel);
    ui->Chanderlier->


}

MainInterface::~MainInterface() {
    delete ui;
}
