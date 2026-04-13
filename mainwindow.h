#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include "instrument_table_model.h"
#include "instrument_delegate.h"
#include "variable_table_model.h"
#include "variable_delegate.h"
#include "experiment.h"

QT_BEGIN_NAMESPACE
namespace Ui {
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
    void openGraphSettings();
    void openPreview();
    void applyLinGraphSettings();
    void applyBarGraphSettings();
    void applyColourGraphSettings();
    void addInstrument();
    void addVariable();
    void removeInstrument();
    void removeVariable();
    

private:
    Ui::MainWindow *ui;
    InstrumentTableModel *instrumentModel;
    InstrumentDelegate *instrumentDelegate;
    VariableTableModel *variableModel;
    VariableDelegate *variableDelegate;
};



#endif // MAINWINDOW_H