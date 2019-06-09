#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include "Controller/simulation.h"
#include "UI/evolutionviewer.h"
#include "configuration.h"
#include "modemanuelwidget.h"
#include "modepaspaswidget.h"
#include "modeautowidget.h"
#include "addindicateurdialog.h"
#include "info.h"
#include <QWidget>
#include <QListWidgetItem>
namespace Ui {
    class MainInterface;
    class NoteItem;
}

class NoteItem: public QListWidgetItem {
    Note* note;
public:
    NoteItem (Note* note, QListWidget* parent=nullptr, int type=0) : QListWidgetItem(parent, type), note(note) {}
    Note* getNote() {return note;}
};



class MainInterface : public QWidget {
    Q_OBJECT
public:
    explicit MainInterface(QWidget *parent = nullptr);
    ~MainInterface();
signals:
    void giveName(QString nom);
private slots:
    void newSimulation();
    void showSimulation();
    void on_newSimulation_button_clicked();
    void endSimulationMessage();
    void updateGraph();
    void updateTransactionTable();
    void on_chargeSimulation_button_clicked();
    void on_save_clicked();
    void on_addNote_clicked();
    void on_listNote_itemDoubleClicked(QListWidgetItem *item);
    void on_nameEdit_editingFinished();
    void on_pushButton_2_clicked();
    void on_closeNote_clicked();
    void on_noteEdit_textChanged();
    void on_deleteSimulation_clicked();
    void on_ema_stateChanged(int arg1);

    void on_macd_stateChanged(int arg1);

    void on_rsi_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainInterface *ui;
    Simulation* simulation = nullptr;
    NoteItem* currentNote = nullptr;
    Configuration* configuration;
    QWidget* controlPanel;
    EvolutionViewer* evolutionViewer;
    VolumeViewer* volumeViewer;
    //QWidget* ROI_Viewer;
};

#endif // MAININTERFACE_H
