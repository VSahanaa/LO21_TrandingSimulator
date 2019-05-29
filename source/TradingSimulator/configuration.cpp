#include "configuration.h"
#include "ui_configuration.h"

Configuration::Configuration(QWidget *parent) : QDialog(parent), ui(new Ui::Configuration) {
    setListesDevise();
    ui->setupUi(this);
    ui->strategie_widget->hide();            //hide strategieParameters widget by default, show only if Mode Automatique is chosen
}

Configuration::~Configuration() {
    delete ui;
}

void Configuration::setListesDevise() {
    DevisesManager& deviseManager = DevisesManager::getManager();
    QStringList listeDeviseCodes = deviseManager.getDeviseCodes();
    ui->listeBase->insertItems(0, listeDeviseCodes);
    ui->listeContrepartie->insertItems(0, listeDeviseCodes);
}

void Configuration::on_addDevise_button_clicked() {
    addDevise_dialog = new AddDevise_Dialog(this);
    addDevise_dialog->setModal(true);
    addDevise_dialog->exec();
    //add new Devise to the Combo boxes
    if(addDevise_dialog->getNewDevise()) {
        ui->listeContrepartie->addItem(addDevise_dialog->getNewDevise()->getCode(), addDevise_dialog->getNewDevise()->getCode());
        ui->listeBase->addItem(addDevise_dialog->getNewDevise()->getCode(), addDevise_dialog->getNewDevise()->getCode());
    }
}

void Configuration::on_browseButton_clicked() {
    QFileDialog fdlg;
    ui->browseFile->setText(fdlg.getOpenFileName(this, tr("Choose csv file"), ":/", "Document files (*.csv)"));
}

void Configuration::setEvolutionCours() {
    DevisesManager& deviseManager = DevisesManager::getManager();
    const PaireDevises& paire = deviseManager.getPaireDevises(ui->listeContrepartie->currentText(),ui->listeBase->currentText());
    QString fPath = ui->browseFile->text();
    evolutionCours =  new EvolutionCours(paire, fPath);
}

void Configuration::finishConfigEvolutionCours() {
    nomSimulation = ui->nameSimulation->text();
    setEvolutionCours();
    ui->mainWidget->setCurrentWidget(ui->config_page);
    qDebug() << (evolutionCours->begin())->getDate().toString("yyyy-MM-dd");
    qDebug() << (evolutionCours->end()-1)->getDate().toString("yyyy-MM-dd");
    ui->pickStartDate->setMinimumDate(evolutionCours->begin()->getDate());             //date debut du EvolutionCours
    ui->pickStartDate->setMaximumDate((evolutionCours->end()-1)->getDate());            //date fini du evolutionCours
    ui->pickStartDate->setDate(evolutionCours->begin()->getDate());                    //valeur par défault
    ui->pickPourcentage->setSuffix("%");
    ui->pickPourcentage->setMaximum(100);
    ui->pickPourcentage->setMinimum(0);
    ui->pickPourcentage->setValue(0.1);
    ui->pickBase->setMaximum(100000000000000);
    ui->pickBase->setValue(0);
    ui->pickContrepartie->setMaximum(100000000000000);
    ui->pickContrepartie->setValue(1000000);
}

void Configuration::on_ModeManule_button_clicked() {
    modeSimulation = "Manuel";
    finishConfigEvolutionCours();
}

void Configuration::on_ModePas_Pas_button_clicked() {
    modeSimulation = "Pas_Pas";
    finishConfigEvolutionCours();
}

void Configuration::on_ModeAuto_buton_clicked() {
    modeSimulation = "Automatique";
    finishConfigEvolutionCours();
    ui->strategie_widget->show();
    QStringList nomStrategies = strategieFactory->listeStrategie();
    ui->listeStrategie->insertItems(0, nomStrategies);
    refreshStrategieLayout(ui->listeStrategie->currentText());
}

void Configuration::refreshStrategieLayout(QString strategieNom) {
    // clear old data
    parameters.clear();
    foreach(QLineEdit* lineEdit, parametersEdit.values()) {
        delete lineEdit;
    }
    parametersEdit.clear();
    if (strategie) delete strategie;

    strategie = strategieFactory->getStrategie(strategieNom, evolutionCours);
    parameters = strategie->getParameters();
    if(ui->parameters_widget->layout()) delete ui->parameters_widget->layout();     //delete old layout
    QFormLayout* formLayout = new QFormLayout;
    foreach(QString parameter, parameters.keys()) {
        parametersEdit.insert(parameter, new QLineEdit);            //QLineEdit allocated and added dynamically into new form layout
        formLayout->addRow(parameter, parametersEdit[parameter]);
    }
    ui->parameters_widget->setLayout(formLayout);
}

void Configuration::on_listeStrategie_currentTextChanged(const QString &strategieNom) {
    refreshStrategieLayout(strategieNom);
}
