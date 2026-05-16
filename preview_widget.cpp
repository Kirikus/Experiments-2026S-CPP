#include "preview_widget.h"
#include "ui_preview_widget.h"
#include "graphblock.h"
#include "tableblock.h"
#include "textblock.h"
#include "mainwindow.h"
#include "experiment.h"
#include <QMenu>
#include <QScrollArea>

Preview_widget::Preview_widget(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Preview_widget)
{
    ui->setupUi(this);

    QMenu *tableMenu = new QMenu(this);
    //tableMenu->addAction("Experiment", this, &Preview_widget::addExperimentTable);
    tableMenu->addAction("Constant", this, &Preview_widget::addConstantTable);
    tableMenu->addAction("Variable", this, &Preview_widget::addVariableTable);
    tableMenu->addAction("Instrument", this, &Preview_widget::addInstrumentTable);  

    ui->AddTableButton->setMenu(tableMenu);

    connect(ui->AddGraphButton, &QPushButton::clicked, this, &Preview_widget::addGraphBlock);
    connect(ui->AddTextButton, &QPushButton::clicked, this, &Preview_widget::addTextBlock);

    //scroll area
    QWidget *container = new QWidget();
    m_blocksLayout = new QVBoxLayout(container);
    m_blocksLayout->setAlignment(Qt::AlignTop);
    ui->scrollArea->setWidget(container);
    ui->scrollArea->setWidgetResizable(true);

    connect(ui->SaveButton, &QPushButton::clicked, this, &Preview_widget::SaveReport);
}

Preview_widget::~Preview_widget()
{
    delete ui;
}

void Preview_widget::addGraphBlock()
{
    GraphBlock *block = new GraphBlock();
    //получить текущий график из MainWindow:
    MainWindow *mw = qobject_cast<MainWindow*>(parent());
    if (mw) {
        QCustomPlot *plot = mw->getCurrentPlot();
        if (plot) {
            block->setPlot(plot);
        }
    }
    m_blocksLayout->addWidget(block);
    setupBlockConnections(block);
}

void Preview_widget::addTextBlock()
{
    TextBlock *block = new TextBlock();
    m_blocksLayout->addWidget(block);
    setupBlockConnections(block);
}

/*
void Preview_widget::addExperimentTable()
{
    TableBlock *block = new TableBlock();
    
    Experiment *exp = Experiment::getInstance();
    ExperimentTableModel *model = new ExperimentTableModel(*exp);
    block->setModel(model);
    
    setupBlockConnections(block);
    m_blocksLayout->addWidget(block);
}
*/
void Preview_widget::addConstantTable()
{
    TableBlock *block = new TableBlock();
    
    Experiment *exp = Experiment::getInstance();
    ConstantTableModel *model = new ConstantTableModel(*exp);
    block->setModel(model);
    
    setupBlockConnections(block);
    m_blocksLayout->addWidget(block);
}

void Preview_widget::addVariableTable()
{
    TableBlock *block = new TableBlock();
    
    Experiment *exp = Experiment::getInstance();
    VariableTableModel *model = new VariableTableModel(*exp);
    block->setModel(model);

    setupBlockConnections(block);
    m_blocksLayout->addWidget(block);
}

void Preview_widget::addInstrumentTable()
{
    TableBlock *block = new TableBlock();
    
    Experiment *exp = Experiment::getInstance();
    InstrumentTableModel *model = new InstrumentTableModel(*exp);
    block->setModel(model);

    setupBlockConnections(block);
    m_blocksLayout->addWidget(block);
}

//подключение сигналов

void Preview_widget::setupBlockConnections(Block *block)
{
    connect(block, &Block::deleteButton, [this, block]() {
        m_blocksLayout->removeWidget(block);
        block->deleteLater();
    });
    
    connect(block, &Block::moveUpButton, [this, block]() {
        int idx = m_blocksLayout->indexOf(block);
        if (idx > 0) {
            m_blocksLayout->insertWidget(idx - 1, block);
        }
    });
    
    connect(block, &Block::moveDownButton, [this, block]() {
        int idx = m_blocksLayout->indexOf(block);
        if (idx < m_blocksLayout->count() - 1) {
            m_blocksLayout->insertWidget(idx + 1, block);
        }
    });
}

void Preview_widget::SaveReport()
{
    
}
