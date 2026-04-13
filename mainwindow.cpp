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

void MainWindow::addVariable() {
    // Создаем новую переменную
    QList<double> values;
    Variable newVar(values, "new variable");
    
    // Добавляем в эксперимент
    Experiment::getInstance()->getVariables().append(newVar);
    
    // Уведомляем модель об изменении
    variableModel->resetModel();
}

void MainWindow::removeVariable() {
    QModelIndex currentIndex = ui->VariablesTable->currentIndex();
    if (currentIndex.isValid()) {
        int row = currentIndex.row();
        // Удаляем из эксперимента
        Experiment::getInstance()->getVariables().removeAt(row);
        
        // Уведомляем модель об изменении
        variableModel->resetModel();
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

MainWindow::~MainWindow()
{
    delete ui;
}

