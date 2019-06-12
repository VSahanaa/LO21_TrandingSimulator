#include "maininterface.h"
#include "ui_maininterface.h"

MainInterface::MainInterface(QWidget *parent) : QWidget(parent), ui(new Ui::MainInterface) {
    ui->setupUi(this);
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
    emit giveName(simulation->getNom());

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
        QMessageBox::information(this, "Info", "Platforme ne supporte pas ce mode de simulation.");
    }
    ui->controlPanel->addWidget(controlPanel);
    ui->chanderlierLayout->addWidget(evolutionViewer);
    ui->volumeLayout->addWidget(volumeViewer); 
    ui->tabWidget->setCurrentIndex(0);

    ui->transactionTable->setColumnCount(4);
    const PaireDevises* paire = simulation->getEvolutionCours()->getPaireDevises();
    QStringList labels;
    labels<<"Date" << paire->getContrepartie().getCode() <<paire->getBase().getCode() << "ROI";
    ui->transactionTable->setHorizontalHeaderLabels(labels);
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
    evolutionViewer->setCurrentCours(simulation->getCurrentCours());
    volumeViewer->setCurrentCours(simulation->getCurrentCours());
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
    double montantTotalInit = simulation->getTransactionManager()->getMontantTotalInitial();
    int i = 0;
    while(transactionIterator != nullptr) {
        ui->transactionTable->setRowCount(++i);
        QTableWidgetItem *date, *diffContrepartie, *diffBase, *roi;
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
        roi = new QTableWidgetItem(QString::number(transactionIterator->roi(montantTotalInit)), 0);
        ui->transactionTable->setItem(i-1, 0, date);
        ui->transactionTable->setItem(i-1, 1, diffContrepartie);
        ui->transactionTable->setItem(i-1, 2, diffBase);
        ui->transactionTable->setItem(i-1, 3, roi);
        transactionIterator = transactionIterator->next();
    }
}

void MainInterface::on_chargeSimulation_button_clicked() {
    //charge simulation
    if(ui->listSimulation->currentItem()) {
        QString nomSimulation = ui->listSimulation->currentItem()->text();
        SimulationManager* simulationManager = SimulationManager::getSimulationManager();
        try {
            simulationManager->removeSimulation(simulation);
            simulation = simulationManager->chargeSimulation(nomSimulation);
            showSimulation();
        } catch (TradingException exception) {
            QMessageBox::warning(this, "Warning", exception.getInfo());
        }
    }

}

void MainInterface::on_deleteSimulation_clicked() {
    if(ui->listSimulation->currentItem()){
        QString nomSimulation = ui->listSimulation->currentItem()->text();
        SimulationManager* simulationManager = SimulationManager::getSimulationManager();
        try {
            simulationManager->deleteSavedSimulation(nomSimulation);
            ui->listSimulation->takeItem(ui->listSimulation->currentRow());
        } catch (TradingException exception) {
            QMessageBox::warning(this, "Warning", exception.getInfo());
        }
    }

}

void MainInterface::on_save_clicked() {
    try {
        simulation->saveSimulation();
        QMessageBox::information(this, "Save Simulation", "Saved");
    } catch (TradingException exception) {
        QMessageBox::warning(this, "Warning", exception.getInfo());
    }

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

/* -------------------------------------------------------Parametres de simulation --------------------------------------------------------------------------------*/

void MainInterface::on_ema_stateChanged(int arg1) {
    if(arg1 == 0) {
        evolutionViewer->activateEMA(false);
    }
    else {
        //set parameters for EMA
        AddIndicateurDialog* addIndicateurDialog = new AddIndicateurDialog("EMA", simulation->getEvolutionCours(), this);
        addIndicateurDialog->exec();
        evolutionViewer->activateEMA(true);
        delete addIndicateurDialog;
    }

}

void MainInterface::on_macd_stateChanged(int arg1) {
    if(arg1 == 0) {
        evolutionViewer->activateMACD(false);
    }
    else {
        //set parameters for MACD
        AddIndicateurDialog* addIndicateurDialog = new AddIndicateurDialog("MACD", simulation->getEvolutionCours(), this);
        addIndicateurDialog->exec();
        evolutionViewer->activateMACD(true);
        delete addIndicateurDialog;
    }
}

void MainInterface::on_rsi_clicked() {
    //set parameters for RSI
    AddIndicateurDialog* addIndicateurDialog = new AddIndicateurDialog("RSI", simulation->getEvolutionCours(), this);
    addIndicateurDialog->exec();
    delete addIndicateurDialog;
    if(simulation->getType() == "Manuel") {
        volumeViewer->setCurrentCours(simulation->getEvolutionCours()->end()-1);
    }
    else {
        volumeViewer->setCurrentCours(simulation->getCurrentCours());
    }
}

void MainInterface::on_pushButton_clicked() {
    Info* infoDialog = new Info(this);
    infoDialog->exec();
    delete infoDialog;
}
