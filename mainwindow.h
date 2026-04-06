#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include "qcustomplot.h"
#include "constant_table_model.h"
#include "constant_delegate.h"
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
    //void openGraphSettings();
    void openPreview();
    void createLinGraph();
    void createBarGraph();
    void createColourGraph();
    void applyLinGraphSettings();
    void applyBarGraphSettings();
    void applyColourGraphSettings();

private:
    void setupCreateButton();

private:
    Ui::MainWindow *ui;
    QTabWidget *GraphTabWidget;

    ConstantTableModel *constantModel;
    ConstantDelegate *constantDelegate;
};

#endif // MAINWINDOW_H