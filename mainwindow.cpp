#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "preview_widget.h"
#include "graphsettings.h"
#include "colourgraphsettings.h"
#include "lingraphsettings.h"
#include "bargraphsettings.h"
#include "preview_widget.h"
#include "qcustomplot.h"
#include "graph.h"
#include "lingraph.h"
#include "variable_delegate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->GraphTabWidget->setTabsClosable(true);

    connect(ui->GraphTabWidget, &QTabWidget::tabCloseRequested,
        this, &MainWindow::closeTab);

    setupCreateButton();

    // preview button from menubar
    connect(ui->ActionPreview, &QAction::triggered,
            this, &MainWindow::openPreview);

    // setup instrument table
    instrumentModel = new InstrumentTableModel(*Experiment::getInstance());
    instrumentDelegate = new InstrumentDelegate(this);
    ui->InstrumentsTable->setModel(instrumentModel);
    ui->InstrumentsTable->setItemDelegate(instrumentDelegate);

    variableModel = new VariableTableModel(*Experiment::getInstance());
    variableDelegate = new VariableDelegate(this);
    ui->VariablesTable->setModel(variableModel);
    ui->VariablesTable->setItemDelegate(variableDelegate);

    connectionsModel = new ConnectionsTableModel(*Experiment::getInstance());
    // connectionsDelegate = new VariableDelegate(this);
    ui->ConnectionsTable->setModel(connectionsModel);
    // ui->ConnectionsTable->setItemDelegate(variableDelegate);

    connect(ui->VarAddButton, &QPushButton::clicked, this, &MainWindow::addVariable);
    connect(ui->VarDelButton, &QPushButton::clicked, this, &MainWindow::removeVariable);
    connect(ui->InstAddButton, &QPushButton::clicked, this, &MainWindow::addInstrument);
    connect(ui->InstDelButton, &QPushButton::clicked, this, &MainWindow::removeInstrument);

    // setup constants table
    constantModel = new ConstantTableModel();
    constantDelegate = new ConstantDelegate(this);
    ui->ConstantsTable->setModel(constantModel);
    ui->ConstantsTable->setItemDelegate(constantDelegate);

    constantModel->addConstant();
    QModelIndex i0 = constantModel->index(0, 0);
    constantModel->setData(i0, "g");

    QModelIndex i1 = constantModel->index(0, 1);
    constantModel->setData(i1, 9.8);

    QModelIndex i2 = constantModel->index(0, 2);
    constantModel->setData(i2, 0.1);

    QModelIndex i3 = constantModel->index(0, 3);
    constantModel->setData(i3, "ускорение св. падения");
}

/*
void MainWindow::openGraphSettings()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (!action)
        return;

    QString graphType = action->text();

    if (graphType == "Line graph")
    {
        createLinGraph();
    }
    else if (graphType == "Bar graph")
    {
        createBarGraph();
    }
    else if (graphType == "Colour graph")
    {
        createColourGraph();
    }
}
*/

void MainWindow::createLinGraph()
{
    Graph *graph = new LinGraph(this);

    int index = ui->GraphTabWidget->addTab(graph,
                                           QString("График 1").arg(ui->GraphTabWidget->count() + 1));
    ui->GraphTabWidget->setCurrentIndex(index);
}
/*
void MainWindow::createBarGraph()
{
    Graph *graph = new Graph(this);
    graph->setGraphType(Graph::Bar);
    
    int index = ui->GraphTabWidget->addTab(graph, 
        QString("График 2").arg(ui->GraphTabWidget->count() + 1));
    ui->GraphTabWidget->setCurrentIndex(index);
}

void MainWindow::createColourGraph()
{
    qDebug() << "Colour graph";
}
*/

void MainWindow::applyLinGraphSettings()
{
    qDebug() << "Line graph settings";
    // graph update
}
*/

void MainWindow::applyLinGraphSettings()
{
    qDebug() << "Line graph settings";
    // graph update
}
/*
void MainWindow::applyBarGraphSettings()
{
    qDebug() << "Bar graph settings";
    // graph update
}

void MainWindow::applyColourGraphSettings()
{
    qDebug() << "Colour graph settings";
    // graph update
}
*/
void MainWindow::openPreview()
{
    // preview window
    Preview_widget *preview = new Preview_widget(this);
    preview->setAttribute(Qt::WA_DeleteOnClose);
    preview->show();
}

void MainWindow::addVariable() {
    // Создаем новую переменную
    QList<double> values;
    Variable newVar(values, "new variable", nullptr);
    
    // Добавляем в эксперимент
    Experiment::getInstance()->getVariables().append(newVar);
    
    // Уведомляем модель об изменении
    variableModel->resetModel();
    connectionsModel->resetModel();
}

void MainWindow::removeVariable() {
    QModelIndex currentIndex = ui->VariablesTable->currentIndex();
    if (currentIndex.isValid()) {
        int row = currentIndex.row();
        // Удаляем из эксперимента
        Experiment::getInstance()->getVariables().removeAt(row);
        
        // Уведомляем модель об изменении
        variableModel->resetModel();
        connectionsModel->resetModel();
    }
}

void MainWindow::addInstrument() {
    // Создаем новый инструмент
    Instrument newInst("new instrument", 0.0);
    QString errorType = "Абсолютная";
    newInst.set_error_type(errorType);
    
    // Добавляем в эксперимент
    Experiment::getInstance()->getInstruments().append(newInst);
    
    // Уведомляем модель об изменении
    instrumentModel->resetModel();
}

void MainWindow::removeInstrument() {
    QModelIndex currentIndex = ui->InstrumentsTable->currentIndex();
    if (currentIndex.isValid()) {
        int row = currentIndex.row();
        // Удаляем из эксперимента
        Experiment::getInstance()->getInstruments().removeAt(row);
        
        // Уведомляем модель об изменении
        instrumentModel->resetModel();
    }
}
// new graph button
void MainWindow::setupCreateButton()
{
    QMenu *menu = new QMenu(this);

    QAction *lineAction = menu->addAction("Line graph");
    //QAction *barAction = menu->addAction("Bar graph");
    //QAction *colourAction = menu->addAction("Colour graph");

    connect(lineAction, &QAction::triggered, this, &MainWindow::createLinGraph);
    //connect(barAction, &QAction::triggered, this, &MainWindow::createBarGraph);
    //connect(colourAction, &QAction::triggered, this, &MainWindow::createColourGraph);

    ui->NewGraphButton->setMenu(menu);
}

void MainWindow::closeTab(int index)
{
    QWidget *widget = ui->GraphTabWidget->widget(index);
    ui->GraphTabWidget->removeTab(index);
    delete widget;
}

MainWindow::~MainWindow()
{
    delete ui;

    delete constantModel;
    delete constantDelegate;
}
