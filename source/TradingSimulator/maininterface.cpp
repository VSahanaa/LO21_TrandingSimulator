#include "maininterface.h"
#include "ui_maininterface.h"

MainInterface::MainInterface(QWidget *parent) : QWidget(parent), ui(new Ui::MainInterface) {
    ui->setupUi(this);
    ui->simulationGo->setVisible(false);
    SimulationManager* simulationManager = SimulationManager::getSimulationManager();
    QStringList listSavedSimulation = simulationManager->listSavedSimulation();
    ui->listSimulation->addItems(listSavedSimulation);
}

MainInterface::~MainInterface() {
    delete ui;
    SimulationManager* simulationManager = SimulationManager::getSimulationManager();
    simulationManager->removeSimulation(simulation);
}
/* --------------------------------------------------------- Create and show simulation ---------------------------------------------------------------------*/
void MainInterface::newSimulation() {
    SimulationManager* simulationManager = SimulationManager::getSimulationManager();
    simulationManager->removeSimulation(simulation);
    simulation = configuration->getSimulation();
    showSimulation();
}

void MainInterface::showSimulation() {
    ui->controlPanel->removeWidget(controlPanel);
    ui->chanderlierLayout->removeWidget(evolutionViewer);
    ui->volumeLayout->removeWidget(volumeViewer);
    ui->transactionTable->setRowCount(0);
    ui->simulationGo->setVisible(true);
    ui->stackedWidget->setCurrentWidget(ui->SimulationPage);
    if (simulation->getType() == "Manuel") {
        //Specific element for mode Manuel
        controlPanel = new modeManuelWidget(static_cast<ModeManuel*>(simulation), this);
        evolutionViewer = new EvolutionViewer(simulation->getEvolutionCours(), simulation->getEvolutionCours()->end()-1, this);
        volumeViewer = new VolumeViewer(simulation->getEvolutionCours(), simulation->getEvolutionCours()->end()-1, this);
        QObject::connect(evolutionViewer, SIGNAL(coursPicked(CoursOHLCV*)), static_cast<modeManuelWidget*>(controlPanel), SLOT(setCoursPicked(CoursOHLCV*)));
        QObject::connect(static_cast<modeManuelWidget*>(controlPanel), SIGNAL(transactionChanged()), this, SLOT(updateTransactionTable()));
    }
    else if (simulation->getType() == "Pas_Pas") {
        //Specific element for mode Pas à pas
        controlPanel = new ModePasPaswidget(static_cast<ModePas_Pas*>(simulation), this);
        evolutionViewer = new EvolutionViewer(simulation->getEvolutionCours(), simulation->getCurrentCours(), this);
        volumeViewer = new VolumeViewer(simulation->getEvolutionCours(), simulation->getCurrentCours(), this);
        QObject::connect(static_cast<ModePas_Pas*>(simulation), SIGNAL(endSimulation()), this, SLOT(endSimulationMessage()));
        QObject::connect(static_cast<ModePas_Pas*>(simulation), SIGNAL(coursChanged()), this, SLOT(updateGraph()));
        QObject::connect(static_cast<ModePasPaswidget*>(controlPanel), SIGNAL(transactionChanged()), this, SLOT(updateTransactionTable()));
    }
    else if (simulation->getType() == "Automatique") {
        //Specific element for mode Automatique
        controlPanel = new ModeAutowidget(static_cast<ModeAutomatique*>(simulation), this);
        evolutionViewer = new EvolutionViewer(simulation->getEvolutionCours(), simulation->getCurrentCours(), this);
        volumeViewer = new VolumeViewer(simulation->getEvolutionCours(), simulation->getCurrentCours(), this);
        QObject::connect(static_cast<ModeAutomatique*>(simulation), SIGNAL(endSimulation()), this, SLOT(endSimulationMessage()));
        QObject::connect(static_cast<ModeAutomatique*>(simulation), SIGNAL(coursChanged()), this, SLOT(updateGraph()));
        QObject::connect(static_cast<ModeAutowidget*>(controlPanel), SIGNAL(transactionChanged()), this, SLOT(updateTransactionTable()));
    }
    else {
        throw TradingException("type simulation invalid");
    }
    ui->controlPanel->addWidget(controlPanel);
    ui->chanderlierLayout->addWidget(evolutionViewer);
    ui->volumeLayout->addWidget(volumeViewer); 
    ui->tabWidget->setCurrentWidget(evolutionViewer);

    ui->transactionTable->setColumnCount(3);
    ui->transactionTable->setHorizontalHeaderLabels({ "Date", "Contre partie", "Base" });
    updateTransactionTable();
    if(!currentNote) {
        ui->noteEdit->clear();
        ui->nameEdit->clear();
        ui->noteEdit->setEnabled(false);
        ui->nameEdit->setEnabled(false);
    }

    //load Note
    Simulation::NoteManager noteManager = simulation->getNoteManager();
    for (int i=0; i<noteManager.count(); i++) {
        NoteItem* newNoteItem = new NoteItem(noteManager[i]);
        newNoteItem->setText(noteManager[i]->getNom());
        ui->listNote->addItem(newNoteItem);
    }
}

void MainInterface::endSimulationMessage() {
    QMessageBox::information(this, "Message", "Fin de la simulation");
}

void MainInterface::updateGraph() {
    evolutionViewer->setCurrentCours(simulation->getCurrentCours());      //don't show the current cours
    volumeViewer->setCurrentCours(simulation->getCurrentCours());
}

void MainInterface::on_pushButton_sauvegarder_clicked() {
    simulation->saveSimulation();
    QMessageBox::information(this, "Save Simulation", "Saved");
}

void MainInterface::on_newSimulation_button_clicked() {
    configuration = new Configuration(this);
    QObject::connect(configuration, SIGNAL(accepted()), this, SLOT(newSimulation()));
    configuration->setModal(true);
    configuration->exec();
    delete configuration;
}

void MainInterface::updateTransactionTable() {
    ui->transactionTable->setRowCount(0);        //clear all data
    TransactionManager::iterator transactionIterator = simulation->getTransactionManager()->head();
    int i = 0;
    while(transactionIterator != nullptr) {
        ui->transactionTable->setRowCount(++i);
        QTableWidgetItem *date, *diffContrepartie, *diffBase;
        date = new QTableWidgetItem(transactionIterator->getCours()->getDate().toString("dd.MM.yy"), 0);
        if(transactionIterator->differenceBase() > 0) {
            diffBase = new QTableWidgetItem(QIcon(":/TradingSimulator/evolutionCours/icons/up.jpeg"), QString::number(transactionIterator->differenceBase()), 0);
        }
        else {
            diffBase = new QTableWidgetItem(QIcon(":/TradingSimulator/evolutionCours/icons/down.jpeg"), QString::number(-transactionIterator->differenceBase()), 0);
        }

        if(transactionIterator->differenceContrepartie() > 0) {
            diffContrepartie = new QTableWidgetItem(QIcon(":/TradingSimulator/evolutionCours/icons/up.jpeg"), QString::number(transactionIterator->differenceContrepartie()), 0);
        }
        else {
            diffContrepartie = new QTableWidgetItem(QIcon(":/TradingSimulator/evolutionCours/icons/down.jpeg"), QString::number(-transactionIterator->differenceContrepartie()), 0);
        }
        ui->transactionTable->setItem(i-1, 0, date);
        ui->transactionTable->setItem(i-1, 1, diffContrepartie);
        ui->transactionTable->setItem(i-1, 2, diffBase);
        transactionIterator = transactionIterator->next();
        qDebug() << i;
    }
}

void MainInterface::on_back_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->LandingPage);
}

void MainInterface::on_simulationGo_clicked() {
    if(simulation)  ui->stackedWidget->setCurrentWidget(ui->SimulationPage);
}

void MainInterface::on_chargeSimulation_button_clicked() {
    //charge simulation
    QString nomSimulation = ui->listSimulation->currentItem()->text();
    qDebug()<< nomSimulation;
    SimulationManager* simulationManager = SimulationManager::getSimulationManager();
    simulationManager->removeSimulation(simulation);
    qDebug("Removed old simulation");
    simulation = simulationManager->chargeSimulation(nomSimulation);
    showSimulation();
}

void MainInterface::on_save_clicked() {
    simulation->saveSimulation();
}



/* ------------------------------------------------------Text Editor ----------------------------------------------------------------------------*/



void MainInterface::on_addNote_clicked() {
    Note* newNote = simulation->addNote();
    NoteItem* newNoteItem = new NoteItem(newNote);
    newNoteItem->setText(newNote->getNom());
    currentNote = newNoteItem;
    ui->listNote->addItem(newNoteItem);
    ui->noteEdit->setEnabled(true);
    ui->nameEdit->setEnabled(true);
    ui->noteEdit->setPlainText(newNote->getNote());
    ui->nameEdit->setText(newNote->getNom());
}

void MainInterface::on_listNote_itemDoubleClicked(QListWidgetItem *item) {
     Note* note = static_cast<NoteItem*>(item)->getNote();
    qDebug()<<note->getNote();
    qDebug()<< note->getNom();
     currentNote = static_cast<NoteItem*>(item);
     ui->noteEdit->setEnabled(true);
     ui->nameEdit->setEnabled(true);
     ui->noteEdit->setPlainText(note->getNote());
     ui->nameEdit->setText(note->getNom());
}

void MainInterface::on_nameEdit_editingFinished() {
    if(currentNote) {
        currentNote->getNote()->setNom(ui->nameEdit->text());
        currentNote->setText(ui->nameEdit->text());
    }
}

void MainInterface::on_pushButton_2_clicked() {
    NoteItem* item = static_cast<NoteItem*>(ui->listNote->takeItem(ui->listNote->currentRow()));
    if(item==currentNote) {
        currentNote=nullptr;
        ui->noteEdit->clear();
        ui->nameEdit->clear();
        ui->noteEdit->setEnabled(false);
        ui->nameEdit->setEnabled(false);
    }
}

void MainInterface::on_closeNote_clicked() {
    currentNote=nullptr;
    ui->noteEdit->clear();
    ui->nameEdit->clear();
    ui->noteEdit->setEnabled(false);
    ui->nameEdit->setEnabled(false);
}

void MainInterface::on_noteEdit_textChanged() {
    if(currentNote) currentNote->getNote()->setNote(ui->noteEdit->toPlainText());
}
