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
    Variable newVar(values, "New variable");
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
    Experiment::getInstance()->addInstrument(newInst);
    
    // Уведомляем модель об изменении
    instrumentModel->resetModel();
}

bool MainWindow::removeInstrument() {
    Experiment* experiment = Experiment::getInstance();
    QModelIndex currentIndex = ui->InstrumentsTable->currentIndex();
    if (currentIndex.isValid()) {
        
        QHash <int, Instrument>& insts = experiment->getInstruments();
        QList<int> keys = insts.keys();
        std::sort(keys.begin(), keys.end());

        int row = currentIndex.row();

        for (int i = 0; i < experiment->getVariables().size(); i++) {
            if (experiment->getVariables()[i].get_instrument_id() == insts[keys[row]].get_id()) {
                std::cout << "Нельзя удалить инструмент, который используется в эксперименте" << std::endl;
                return false;
            }
        }

        
        // Удаляем из эксперимента
        insts.remove(keys[row]);
        
        // Уведомляем модель об изменении
        instrumentModel->resetModel();

        return true;
    }

    return false;
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

bool MainWindow::saveFile(){
    if (Experiment::getInstance()->get_file_name().isEmpty()) {
        return saveAsFile();
    }

    Experiment* experiment = Experiment::getInstance();

    QString& fileName = Experiment::getInstance()->get_file_name();

    QJsonObject mainObject;

    QJsonArray variables;

    QJsonArray constants;

    QJsonArray instruments;

    for (int i = 0; i < experiment->getVariables().size(); i++) {
        QJsonObject variable;
        QJsonArray values;
        variable["id"] = experiment->getVariables()[i].get_id();
        if (experiment->getVariables()[i].get_instrument_id() != -1) {
            variable["instrument_id"] = experiment->getVariables()[i].get_instrument_id();
        } else {
            variable["instrument_id"] = -1;
        }
        variable["name"] = experiment->getVariables()[i].get_name();
        for (int j = 0; j < experiment->getVariables()[i].get_values().size(); j++) {
            values.append(experiment->getVariables()[i].get_values()[j]);
        }
        if (values.size() > 0) {
            variable["values"] = values;
        }
        variables.append(variable);
    }

    mainObject["Variables"] = variables;

    for (int i = 0; i < experiment->getConstants().size(); i++) {
        QJsonObject constant;
        constant["id"] = experiment->getConstants()[i].get_id();
        constant["name"] = experiment->getConstants()[i].get_name();
        constant["value"] = experiment->getConstants()[i].get_value();
        constant["meaning"] = experiment->getConstants()[i].get_meaning();
        constant["readonly"] = experiment->getConstants()[i].get_readonly();
        constants.append(constant);
    }

    mainObject["Constants"] = constants;


    QList<int> keys = experiment->getInstruments().keys();
    std::sort(keys.begin(), keys.end());

    for (int key : keys) {

        QJsonObject instrument;
        instrument["id"] = experiment->getInstruments()[key].get_id();
        instrument["error_type"] = experiment->getInstruments()[key].get_error_type();
        instrument["name"] = experiment->getInstruments()[key].get_name();
        instrument["error_value"] = experiment->getInstruments()[key].get_error_value();
        instruments.append(instrument);
    }

    mainObject["Instruments"] = instruments;

    QJsonDocument doc(mainObject);

    QFile file(fileName);
    
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    file.write(doc.toJson(QJsonDocument::Indented)); 

    file.close();

    experiment->set_file_name(fileName);

    return true;
}

bool MainWindow::saveAsFile(){
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Сохранить файл"),
        QDir::homePath(),
        tr("JSON файлы (*.json);;Все файлы (*)"));

    if (fileName.isEmpty()) {
        return false;
    }

    Experiment::getInstance()->set_file_name(fileName);

    return saveFile();
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

    delete instrumentModel;
    delete instrumentDelegate;
    delete variableModel;
    delete variableDelegate;
    delete connectionsModel;
}
