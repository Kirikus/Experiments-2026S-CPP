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
#include <iostream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //удаление лишних вкладок графика
    while (ui->GraphTabWidget->count() > 0) {
        QWidget *widget = ui->GraphTabWidget->widget(0);
        ui->GraphTabWidget->removeTab(0);
        delete widget;
    }

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
    connectionsDelegate = new ConnectionsDelegate(this);
    ui->ConnectionsTable->setModel(connectionsModel);
    ui->ConnectionsTable->setItemDelegate(connectionsDelegate);

    connect(ui->VarAddButton, &QPushButton::clicked, this, &MainWindow::addVariable);
    connect(ui->VarDelButton, &QPushButton::clicked, this, &MainWindow::removeVariable);
    connect(ui->InstAddButton, &QPushButton::clicked, this, &MainWindow::addInstrument);
    connect(ui->InstDelButton, &QPushButton::clicked, this, &MainWindow::removeInstrument);
    connect(ui->ConstAddButton, &QPushButton::clicked, this, &MainWindow::addConstant);
    connect(ui->ConstDelButton, &QPushButton::clicked, this, &MainWindow::removeConstant);
    connect(ui->ActionNewFile, &QAction::triggered, this, &MainWindow::newFile);
    connect(ui->ActionOpenFile, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->ActionSave, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->ActionSaveAs, &QAction::triggered, this, &MainWindow::saveAsFile);
    connect(ui->ActionUploadData, &QAction::triggered, this, &MainWindow::uploadFile);


    // setup constants table
    constantModel = new ConstantTableModel(*Experiment::getInstance());
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

    // сигналы об изменениях для обновления графиков
    connect(variableModel, &QAbstractTableModel::dataChanged, this, &MainWindow::updateAllGraphs);
    connect(variableModel, &QAbstractTableModel::rowsInserted, this, &MainWindow::updateAllGraphs);
    connect(variableModel, &QAbstractTableModel::rowsRemoved, this, &MainWindow::updateAllGraphs);
    connect(variableModel, &QAbstractTableModel::modelReset, this, &MainWindow::updateAllGraphs);

    connect(connectionsModel, &QAbstractTableModel::dataChanged, this, &MainWindow::updateAllGraphs);
    connect(connectionsModel, &QAbstractTableModel::modelReset, this, &MainWindow::updateAllGraphs);
}

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

void MainWindow::openPreview()
{
    // preview window
    Preview_widget *preview = new Preview_widget(this);
    preview->setAttribute(Qt::WA_DeleteOnClose);
    preview->show();
}

void MainWindow::addVariable()
{
    // Создаем новую переменную
    QList<double> values;
    Variable newVar(values, "New variable", nullptr);
    newVar.set_id(Experiment::getInstance()->getVariables().size());
    

    Experiment::getInstance()->addVariable(newVar);
    
    // Уведомляем модель об изменении
    variableModel->resetModel();
    connectionsModel->resetModel();
}

void MainWindow::removeVariable()
{
    QModelIndex currentIndex = ui->VariablesTable->currentIndex();
    if (currentIndex.isValid())
    {
        int row = currentIndex.row();
        // Удаляем из эксперимента
        Experiment::getInstance()->getVariables().removeAt(row);

        // Уведомляем модель об изменении
        variableModel->resetModel();
        connectionsModel->resetModel();
    }
}

void MainWindow::addInstrument()
{
    // Создаем новый инструмент
    Instrument newInst("New instrument", 0.0);
    QString errorType = "Абсолютная";
    newInst.set_error_type(errorType);

    // Добавляем в эксперимент
    Experiment::getInstance()->getInstruments().append(newInst);

    // Уведомляем модель об изменении
    instrumentModel->resetModel();
}

void MainWindow::removeInstrument() {
    Experiment* experiment = Experiment::getInstance();
    QModelIndex currentIndex = ui->InstrumentsTable->currentIndex();
    if (currentIndex.isValid()) {
        for (int i = 0; i < experiment->getVariables().size(); i++) {
            if (experiment->getVariables()[i].get_instrument() == &experiment->getInstruments()[currentIndex.row()]) {
                return;
            }
        }
        int row = currentIndex.row();
        // Удаляем из эксперимента
        Experiment::getInstance()->getInstruments().removeAt(row);

        // Уведомляем модель об изменении
        instrumentModel->resetModel();
    }
}

// перерисовка всех графиков при изменении данных
void MainWindow::updateAllGraphs()
{
    for (int i = 0; i < ui->GraphTabWidget->count(); ++i)
    {
        Graph *graph = qobject_cast<Graph *>(ui->GraphTabWidget->widget(i));
        if (graph)
        {
            graph->applySettings();
        }
    }
}

void MainWindow::addConstant() {
    Constant newConst("new constant", 0.0, 0.0, "meaning", false);
    Experiment::getInstance()->addConstant(newConst);

    constantModel->resetModel();
}

void MainWindow::removeConstant() {
QModelIndex currentIndex = ui->ConstantsTable->currentIndex();
    if (currentIndex.isValid()) {
        int row = currentIndex.row();
        
        Experiment::getInstance()->getConstants().removeAt(row);
        
        // Уведомляем модель об изменении
        constantModel->resetModel();
    }
}
// new graph button
void MainWindow::setupCreateButton()
{
    QMenu *menu = new QMenu(this);

    QAction *lineAction = menu->addAction("Line graph");
    // QAction *barAction = menu->addAction("Bar graph");
    // QAction *colourAction = menu->addAction("Colour graph");

    connect(lineAction, &QAction::triggered, this, &MainWindow::createLinGraph);
    // connect(barAction, &QAction::triggered, this, &MainWindow::createBarGraph);
    // connect(colourAction, &QAction::triggered, this, &MainWindow::createColourGraph);

    ui->NewGraphButton->setMenu(menu);
}

void MainWindow::closeTab(int index)
{
    QWidget *widget = ui->GraphTabWidget->widget(index);
    ui->GraphTabWidget->removeTab(index);
    delete widget;
}

void MainWindow::newFile(){
    std::cout << "New file" << std::endl;
}

void MainWindow::openFile(){
    std::cout << "Open file" << std::endl;
}

void MainWindow::saveFile(){
    std::cout << "Save file" << std::endl;
}

bool MainWindow::saveAsFile(){
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Сохранить файл"),
        QDir::homePath(),
        tr("JSON файлы (*.json);;Все файлы (*)"));

    if (fileName.isEmpty()) {
        return false;
    }

    QJsonObject mainObject;

    QJsonArray variables;

    for (int i = 0; i < Experiment::getInstance()->getVariables().size(); i++) {
        QJsonObject variable;
        QJsonArray values;
        variable["id"] = Experiment::getInstance()->getVariables()[i].get_id();
        if (Experiment::getInstance()->getVariables()[i].get_instrument() != nullptr) {
            variable["instrument_id"] = Experiment::getInstance()->getVariables()[i].get_instrument_id();
        } else {
            variable["instrument_id"] = -1;
        }
        variable["name"] = Experiment::getInstance()->getVariables()[i].get_name();
        for (int j = 0; j < Experiment::getInstance()->getVariables()[i].get_values().size(); j++) {
            values.append(Experiment::getInstance()->getVariables()[i].get_values()[j]);
        }
        if (values.size() > 0) {
            variable["values"] = values;
        }
        variables.append(variable);
    }
    mainObject["Variables"] = variables;

    QJsonDocument doc(mainObject);

    QFile file(fileName);
    
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(doc.toJson(QJsonDocument::Indented)); 

    file.close();
    return true;
}

void MainWindow::uploadFile(){
    std::cout << "Upload file" << std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;

    delete constantModel;
    delete constantDelegate;
    delete connectionsDelegate;
}
