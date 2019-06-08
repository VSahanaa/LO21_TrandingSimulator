#include "maininterface.h"
#include "ui_maininterface.h"

MainInterface::MainInterface(QWidget *parent) : QWidget(parent), ui(new Ui::MainInterface) {
    ui->setupUi(this);
    ui->simulationGo->setVisible(false);
}

MainInterface::~MainInterface() {
    delete ui;
    SimulationManager* simulationManager = SimulationManager::getSimulationManager();
    simulationManager->removeSimulation(simulation);
}

void MainInterface::showSimulation() {
    simulation = configuration->getSimulation();
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
    ui->transactionTable->setColumnCount(3);
    ui->transactionTable->setHorizontalHeaderLabels({ "Date", "Contre partie", "Base" });
    updateTransactionTable();

    //load Note
    Simulation::NoteManager noteManager = simulation->getNoteManager();
    for(Simulation::NoteManager::iterator noteIterator = noteManager.begin(); noteIterator != noteManager.end(); noteIterator++) {
        ui->listNote->addItem(noteIterator->getNom() + "\t" + noteIterator->getDernierAcces().toString("dd.MM.yy"));
    }
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
    volumeViewer->setCurrentCours(simulation->getCurrentCours());
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

void MainInterface::on_nameEdit_editingFinished() {
    QString nom = ui->nameEdit->text();
    if(simulation->searchNote(nom) != -1) {
        nom = "";
        QListWidgetItem* item = ui->listNote->currentItem();
        for (int i=0; i<item->text().length(); i++) {
            if(item->text()[i] == "\t") break;
            nom += item->text()[i];
        }
        ui->nameEdit->setText(nom);
        throw TradingException("Ce nom est déjà existe");
    }

}

void MainInterface::on_saveNote_clicked() {
    QString nom = "";
    QListWidgetItem* item = ui->listNote->currentItem();
    for (int i=0; i<item->text().length(); i++) {
        if(item->text()[i] == "\t") break;
        nom += item->text()[i];
    }
    Simulation::NoteManager noteManager = simulation->getNoteManager();
    int index = simulation->searchNote(nom);
    if (index == -1) throw TradingException("Note n'existe pas");
    Note note = noteManager[index];
    note.setNom(ui->nameEdit->text());
    note.setNote(ui->noteEdit->text());
    item->setText(note.getNom() + "\t" + note.getDernierAcces().toString("dd.MM.yy"));
}

void MainInterface::on_listNote_itemDoubleClicked(QListWidgetItem *item){
    //display note
    QString nom = "";
    for (int i=0; i<item->text().length(); i++) {
        if(item->text()[i] == "\t") break;
        nom += item->text()[i];
    }
    Simulation::NoteManager noteManager = simulation->getNoteManager();
    int index = simulation->searchNote(nom);
    if (index == -1) throw TradingException("Note n'existe pas");
    Note note = noteManager[index];
    ui->noteEdit->setText(note.getNote());
    ui->nameEdit->setText(note.getNom());
}

void MainInterface::on_pushButton_2_clicked() {
    QString nom = "";
    QListWidgetItem* item = ui->listNote->currentItem();
    for (int i=0; i<item->text().length(); i++) {
        if(item->text()[i] == "\t") break;
        nom += item->text()[i];
    }
    Simulation::NoteManager noteManager = simulation->getNoteManager();
    int index = simulation->searchNote(nom);
    if (index == -1) throw TradingException("Note n'existe pas");
    noteManager.removeAt(index);
    ui->listNote->removeItemWidget(item);
}

void MainInterface::on_addNote_clicked() {
    Simulation::NoteManager noteManager = simulation->getNoteManager();
    Note& newNote = simulation->addNote();
    ui->listNote->addItem(newNote.getNom() + "\t" + newNote.getDernierAcces().toString("dd.MM.yy"));
    ui->noteEdit->setText(newNote.getNote());
    ui->nameEdit->setText(newNote.getNom());
}
