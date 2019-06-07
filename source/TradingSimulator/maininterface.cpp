#include "maininterface.h"
#include "ui_maininterface.h"

MainInterface::MainInterface(QWidget *parent) : QWidget(parent), ui(new Ui::MainInterface) {
    ui->setupUi(this);
}

MainInterface::~MainInterface() {
    delete ui;
    SimulationManager* simulationManager = SimulationManager::getSimulationManager();
    simulationManager->removeSimulation(simulation);
}

void MainInterface::showSimulation() {
    delete simulation;
    simulation = configuration->getSimulation();
    ui->stackedWidget->setCurrentWidget(ui->SimulationPage);
    if (simulation->getType() == "Manuel") {
        //Specific element for mode Manuel
        controlPanel = new modeManuelWidget(static_cast<ModeManuel*>(simulation), this);
        evolutionViewer = new EvolutionViewer(simulation->getEvolutionCours(), simulation->getEvolutionCours()->end()-1, this);
        volumeViewer = new VolumeViewer(simulation->getEvolutionCours(), simulation->getEvolutionCours()->end()-1, this);
        QObject::connect(evolutionViewer, SIGNAL(coursPicked(CoursOHLCV*)), static_cast<modeManuelWidget*>(controlPanel), SLOT(setCoursPicked(CoursOHLCV*)));
    }
    else if (simulation->getType() == "Pas_Pas") {
        //Specific element for mode Pas à pas
        controlPanel = new ModePasPaswidget(static_cast<ModePas_Pas*>(simulation), this);
        evolutionViewer = new EvolutionViewer(simulation->getEvolutionCours(), simulation->getCurrentCours(), this);
        volumeViewer = new VolumeViewer(simulation->getEvolutionCours(), simulation->getCurrentCours(), this);
        QObject::connect(static_cast<ModePas_Pas*>(simulation), SIGNAL(endSimulation()), this, SLOT(endSimulationMessage()));
        QObject::connect(static_cast<ModePas_Pas*>(simulation), SIGNAL(coursChanged()), this, SLOT(updateGraph()));
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
    ui->chanderlierLayout->addWidget(evolutionViewer);
    ui->volumeLayout->addWidget(volumeViewer);
}

void MainInterface::endSimulationMessage() {
    QDialog* endMessage = new QDialog(this);
    QHBoxLayout* layout = new QHBoxLayout();
    QLabel* message = new QLabel(endMessage);
    message->setText("Fin de la Simulation.");
    layout->addWidget(message);
    endMessage->setLayout(layout);
    endMessage->exec();
}

void MainInterface::updateGraph() {
    evolutionViewer->setCurrentCours(simulation->getCurrentCours());      //don't show the current cours
}

void MainInterface::on_pushButton_sauvegarder_clicked() {
    simulation->saveSimulation();
}

void MainInterface::on_newSimulation_button_clicked() {
    configuration = new Configuration(this);
    QObject::connect(configuration, SIGNAL(accepted()), this, SLOT(showSimulation()));
    configuration->setModal(true);
    configuration->exec();
    delete configuration;
}
