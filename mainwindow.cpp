#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "preview_widget.h"
#include "graphsettings.h"
#include "colourgraphsettings.h"
#include "lingraphsettings.h"
#include "bargraphsettings.h"
#include "preview_widget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // new graph
    setupCreateButton();

    // preview button from menubar
    connect(ui->ActionPreview, &QAction::triggered,
            this, &MainWindow::openPreview);

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

void MainWindow::createLinGraph()
{
    qDebug() << "Line graph";
}

void MainWindow::createBarGraph()
{
    qDebug() << "Bar graph";
}

void MainWindow::createColourGraph()
{
    qDebug() << "Colour graph";
}

void MainWindow::applyLinGraphSettings()
{
    qDebug() << "Line graph settings";
    // graph update
}

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

void MainWindow::openPreview()
{
    // preview window
    Preview_widget *preview = new Preview_widget(this);
    preview->setAttribute(Qt::WA_DeleteOnClose);
    preview->show();
}

// new graph button
void MainWindow::setupCreateButton()
{
    QMenu *menu = new QMenu(this);

    QAction *lineAction = menu->addAction("Line graph");
    QAction *barAction = menu->addAction("Bar graph");
    QAction *colourAction = menu->addAction("Colour graph");

    connect(lineAction, &QAction::triggered, this, &MainWindow::createLinGraph);
    connect(barAction, &QAction::triggered, this, &MainWindow::createBarGraph);
    connect(colourAction, &QAction::triggered, this, &MainWindow::createColourGraph);

    ui->NewGraphButton->setMenu(menu);
}

MainWindow::~MainWindow()
{
    delete ui;

    delete constantModel;
    delete constantDelegate;
}
