#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include "Controller/simulation.h"
#include "UI/evolutionviewer.h"
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
    explicit MainInterface(Simulation* simulation, QWidget *parent = nullptr);
    ~MainInterface();
private:
    Ui::MainInterface *ui;
    Simulation* simulation;
    QWidget* controlPanel;
    QWidget* evolutionViewer;
    QWidget* volumeViewer;
    //QWidget* textEditor;
    //QWidget* listeNote;
    //QWidget* transactionViewer;
    //QWidget* ROI_Viewer;
};

#endif // MAININTERFACE_H
