#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include "instrument_table_model.h"
#include "instrument_delegate.h"
#include "variable_table_model.h"
#include "variable_delegate.h"
#include "connections_table_model.h"
#include "experiment.h"
#include <QTabWidget>
#include "qcustomplot.h"
#include "constant_table_model.h"
#include "constant_delegate.h"
#include "connections_delegate.h"
#include "graph.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openPreview();
    void createLinGraph();
    //void createBarGraph();
    //void createColourGraph();
    void addInstrument();
    void addVariable();
    bool removeInstrument();
    void removeVariable();
    void addConstant();
    void removeConstant();
    //void applyBarGraphSettings();
    //void applyColourGraphSettings();
    void closeTab(int index);
    void updateAllGraphs();


    void newFile();
    void openFile();
    bool saveFile();
    bool saveAsFile();
    void uploadFile();
    

private:
    void setupCreateButton();

private:
    Ui::MainWindow *ui;
    InstrumentTableModel *instrumentModel;
    InstrumentDelegate *instrumentDelegate;
    VariableTableModel *variableModel;
    VariableDelegate *variableDelegate;
    QTabWidget *GraphTabWidget;

    ConstantTableModel *constantModel;
    ConstantDelegate *constantDelegate;

    ConnectionsTableModel *connectionsModel;
    ConnectionsDelegate *connectionsDelegate;
};

#endif // MAINWINDOW_H