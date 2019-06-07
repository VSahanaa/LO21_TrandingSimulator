#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include "Controller/simulation.h"
#include "UI/evolutionviewer.h"
#include "configuration.h"
#include "modemanuelwidget.h"
#include "modepaspaswidget.h"
#include "modeautowidget.h"
#include <QWidget>

namespace Ui {
    class MainInterface;
}

class MainInterface : public QWidget {
    Q_OBJECT
public:
    explicit MainInterface(QWidget *parent = nullptr);
    ~MainInterface();
private slots:
    void showSimulation();
    void on_pushButton_sauvegarder_clicked();
    void on_newSimulation_button_clicked();
    void endSimulationMessage();
    void updateGraph();
private:
    Ui::MainInterface *ui;
    Simulation* simulation = nullptr;
    Configuration* configuration;
    QWidget* controlPanel;
    EvolutionViewer* evolutionViewer;
    VolumeViewer* volumeViewer;
    //QWidget* textEditor;
    //QWidget* listeNote;
    //QWidget* transactionViewer;
    //QWidget* ROI_Viewer;
};

#endif // MAININTERFACE_H
