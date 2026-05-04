#include "graph.h"
#include "qcustomplot.h"
#include "ui_graph.h"
#include <QVBoxLayout>
#include <QPushButton>
#include "experiment.h"
#include "variable.h"

Graph::Graph(QWidget *parent)
    : QWidget(parent), ui(new Ui::Graph)
{
    ui->setupUi(this);

    if (ui->GraphSetButton)
    {
        connect(ui->GraphSetButton, &QPushButton::clicked,
                this, &Graph::onSettingsClicked);
    }

    connect(ui->XBox, &QDoubleSpinBox::valueChanged, this, &Graph::applySettings);
    connect(ui->XToBox, &QDoubleSpinBox::valueChanged, this, &Graph::applySettings);
    connect(ui->YBox, &QDoubleSpinBox::valueChanged, this, &Graph::applySettings);
    connect(ui->YToBox, &QDoubleSpinBox::valueChanged, this, &Graph::applySettings);
    connect(ui->AbsLine, &QLineEdit::textChanged, this, &Graph::applySettings);
    connect(ui->OrdLine, &QLineEdit::textChanged, this, &Graph::applySettings);
}

void Graph::set_axis_labels(const QString &xLabel, const QString &yLabel)
{
    QCustomPlot *plot = ui->customPlot;
    if (plot)
    {
        plot->xAxis->setLabel(xLabel);
        plot->yAxis->setLabel(yLabel);
        plot->replot();
    }
}

void Graph::updateAxesFromUI()
{
    QCustomPlot *plot = ui->customPlot;
    if (!plot)
        return;

    double xMin = ui->XBox->value();
    double xMax = ui->XToBox->value();
    double yMin = ui->YBox->value();
    double yMax = ui->YToBox->value();

    plot->xAxis->setRange(xMin, xMax);
    plot->yAxis->setRange(yMin, yMax);

    plot->xAxis->setLabel(ui->AbsLine->text());
    plot->yAxis->setLabel(ui->OrdLine->text());

    plot->replot();
}

void Graph::onSettingsClicked()
{
    openSettings();
}

QCustomPlot *Graph::getPlot() const
{
    return ui->customPlot;
}

//настройка осей
double Graph::getXMin() const
{
    return ui->XBox->value();
}

double Graph::getXMax() const
{
    return ui->XToBox->value();
}

double Graph::getYMin() const
{
    return ui->YBox->value();
}

double Graph::getYMax() const
{
    return ui->YToBox->value();
}

bool Graph::hasXYRange() const
{
    return ui->XBox->value() != 0 || ui->XToBox->value() != 0 ||
           ui->YBox->value() != 0 || ui->YToBox->value() != 0;
}



Graph::~Graph()
{
    delete ui;
}
