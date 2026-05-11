#include "colourgraph.h"
#include "experiment.h"
#include "variable.h"

ColourGraph::ColourGraph(QWidget *parent)
    : Graph(parent)
{
    drawGraph();
}

ColourGraph::~ColourGraph() {}

void ColourGraph::drawGraph()
{
    QCustomPlot *plot = getPlot();
    if (!plot) return;

    plot->clearPlottables();
    updateAxesFromUI();

    Experiment *exp = Experiment::getInstance();
    QList<Variable> &variables = exp->getVariables();

    if (variables.size() < 2)
    {
        plot->replot();
        return;
    }

    QList<double> xValues = variables[selectedXIndex].get_values();
    QList<double> yValues = variables[selectedYIndex].get_values();

    if (xValues.isEmpty() || yValues.isEmpty() || xValues.size() != yValues.size())
    {
        plot->replot();
        return;
    }

    int size = xValues.size();
    double minX = *std::min_element(xValues.constBegin(), xValues.constEnd());
    double maxX = *std::max_element(xValues.constBegin(), xValues.constEnd());
    double minY = *std::min_element(yValues.constBegin(), yValues.constEnd());
    double maxY = *std::max_element(yValues.constBegin(), yValues.constEnd());

    int resolution = qMin(size, 50);
    double stepX = (maxX - minX) / resolution;
    double stepY = (maxY - minY) / resolution;

    QCPColorMap *colorMap = new QCPColorMap(plot->xAxis, plot->yAxis);
    colorMap->data()->setSize(resolution, resolution);
    colorMap->data()->setRange(QCPRange(minX, maxX), QCPRange(minY, maxY));

    for (int i = 0; i < resolution; ++i)
    {
        for (int j = 0; j < resolution; ++j)
        {
            double x = minX + (i + 0.5) * stepX;
            double y = minY + (j + 0.5) * stepY;

            int count = 0;
            for (int k = 0; k < size; ++k)
            {
                double dx = (xValues[k] - x) / stepX;
                double dy = (yValues[k] - y) / stepY;
                if (qAbs(dx) < 0.5 && qAbs(dy) < 0.5) count++;
            }
            colorMap->data()->setCell(i, j, count);
        }
    }

    QCPColorGradient gradient;
    gradient.setColorStopAt(0.0, gradientColors.value(0, Qt::darkBlue));
    gradient.setColorStopAt(0.5, gradientColors.value(1, Qt::yellow));
    gradient.setColorStopAt(1.0, gradientColors.value(2, Qt::red));
    colorMap->setGradient(gradient);

    colorMap->rescaleDataRange();
    colorMap->setInterpolate(true);

    QCPColorScale *colorScale = new QCPColorScale(plot);
    colorScale->setDataRange(colorMap->dataRange());
    colorScale->setGradient(gradient);
    plot->plotLayout()->addElement(0, 1, colorScale);

    if (hasXYRange())
    {
        plot->xAxis->setRange(getXMin(), getXMax());
        plot->yAxis->setRange(getYMin(), getYMax());
    }

    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    plot->replot();
}

void ColourGraph::openSettings()
{
    ColourGraphSettings *settings = new ColourGraphSettings(this);
    settings->setAttribute(Qt::WA_DeleteOnClose);
    settings->show();
}

void ColourGraph::applySettings()
{
    updateAxesFromUI();
    drawGraph();
}