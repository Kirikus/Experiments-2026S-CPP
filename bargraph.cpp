#include "bargraph.h"
#include "bargraphsettings.h"
#include <QDebug>

BarGraph::BarGraph(QWidget *parent)
    : Graph(parent)
{
    drawGraph();
}

BarGraph::~BarGraph() {}

void BarGraph::drawGraph()
{
    QCustomPlot *plot = getPlot();
    if (!plot) return;

    plot->clearPlottables;
    updateAxesFromUI();

    if (barsSettings.isEmpty())
    {
        BarSetting defaultBar;
        defaultBar.color = Qt::blue;
        defaultBar.fillPattern = "Сплошная";
        defaultBar.borderStyle = "Сплошная";
        barsSettings.append(defaultBar);
    }

    for (const BarSetting &bar : barsSettings)
    {
        QCPBars *bars = new QCPBars(plot->xAxis, plot->yAxis);
        plot->addPlottable(bars);

        // Граница столбца
        QPen pen;
        pen.setColor(bar.color);
        pen.setWidth(1);
        if (bar.borderStyle == "Штрих") pen.setStyle(Qt::DashLine);
        else if (bar.borderStyle == "Пунктир") pen.setStyle(Qt::DotLine);
        else pen.setStyle(Qt::SolidLine);
        bars->setPen(pen);

        // Заливка столбца
        QBrush brush;
        brush.setColor(bar.color);
        if (bar.fillPattern == "Штриховка") brush.setStyle(Qt::BDiagPattern);
        else if (bar.fillPattern == "Сетка") brush.setStyle(Qt::CrossPattern);
        else brush.setStyle(Qt::SolidPattern);
        bars->setBrush(brush);

        // Тестовые данные (потом подтянутся из таблиц)
        QVector<double> x = {1, 2, 3, 4, 5};
        QVector<double> y = {2, 4, 6, 3, 5};
        bars->setData(x, y);
    }

    plot->replot();
}

void BarGraph::openSettings()
{
    BarGraphSettings *settings = new BarGraphSettings(this);
    settings->setAttribute(Qt::WA_DeleteOnClose);
    settings->show();
}

void BarGraph::applySettings()
{
    updateAxesFromUI();
    drawGraph();
}