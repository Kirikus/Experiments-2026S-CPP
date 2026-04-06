#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "preview_widget.h"
#include "graphsettings.h"
#include "colourgraphsettings.h"
#include "lingraphsettings.h"
#include "bargraphsettings.h"
#include "preview_widget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //graph settings button
    connect(ui->GraphSetButton, &QPushButton::clicked, 
            this, &MainWindow::openGraphSettings);

    //preview button from menubar      
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
}

void MainWindow::openGraphSettings()
{
    int index = ui->GraphTypeBox->currentIndex();
    QString graphType = ui->GraphTypeBox->currentText();

        if (graphType == "Line graph" || index == 0)
    {
        LinGraphSettings *settings = new LinGraphSettings(this);
        settings->setAttribute(Qt::WA_DeleteOnClose);

        connect(settings, &LinGraphSettings::applySettings, 
                this, &MainWindow::applyLinGraphSettings);
        
        settings->show();
    }

    else if (graphType == "Bar graph" || index == 1)
    {
        BarGraphSettings *settings = new BarGraphSettings(this);
        settings->setAttribute(Qt::WA_DeleteOnClose);
        
        connect(settings, &BarGraphSettings::applySettings, 
                this, &MainWindow::applyBarGraphSettings);
        
        settings->show();
    }
    else if (graphType == "Color graph" || index == 2)
    {
        ColourGraphSettings *settings = new ColourGraphSettings(this);
        settings->setAttribute(Qt::WA_DeleteOnClose);
        
        connect(settings, &ColourGraphSettings::applySettings, 
                this, &MainWindow::applyColourGraphSettings);
        
        settings->show();
    }
}

void MainWindow::applyLinGraphSettings()
{   
    qDebug() << "Line graph settings";
    //graph update

}

void MainWindow::applyBarGraphSettings()
{
    qDebug() << "Bar graph settings";
    //graph update
}

void MainWindow::applyColourGraphSettings()
{
    qDebug() << "Colour graph settings";
    // graph update
}

void MainWindow::openPreview()
{
    // preview window
    Preview_widget *preview = new Preview_widget(this);
    preview->setAttribute(Qt::WA_DeleteOnClose);
    preview->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

