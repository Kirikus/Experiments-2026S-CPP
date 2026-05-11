#include "bargraph.h"
#include "bargraphsettings.h"
#include <QDebug>
#include "experiment.h"
#include "variable.h"
#include <algorithm>
#include <QMessageBox>

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

    plot->clearPlottables();
    updateAxesFromUI();

    Experiment *exp = Experiment::getInstance();
    QList<Variable> &variables = exp->getVariables();

    if (variables.isEmpty())
    {
        plot->replot();
        return;
    }

    if (selectedIndex < 0 || selectedIndex >= variables.size())
        selectedIndex = 0;

    QList<double> xValues = variables[selectedIndex].get_values();
    if (xValues.isEmpty())
    {
        plot->replot();
        return;
    }

    QList<QColor> defaultColors = {Qt::red, Qt::green, Qt::blue, Qt::magenta, Qt::cyan, Qt::darkYellow};
    int colorIndex = 0;

    for (int col = 0; col < variables.size(); ++col)
    {
        if (col == selectedIndex)
            continue;

        QString varName = variables[col].get_name();
        QList<double> yValues = variables[col].get_values();

        if (yValues.size() != xValues.size()) continue;

        // значения по умолчанию или из настроек
        int binCount = 10;
        double barWidth = 1.0;
        bool visible = true;
        QColor barColor = defaultColors[colorIndex % defaultColors.size()];

        if (barsSettings.contains(varName))
        {
            const BarSetting &bar = barsSettings[varName];
            binCount = bar.binCount;
            barWidth = bar.barWidth;
            visible = bar.visible;
            if (bar.color.isValid()) barColor = bar.color;
        }

        if (!visible) continue;

        // Рассчитываем границы бинов
        double minVal = *std::min_element(yValues.constBegin(), yValues.constEnd());
        double maxVal = *std::max_element(yValues.constBegin(), yValues.constEnd());
        
        if (qFuzzyCompare(minVal, maxVal))
        {
            maxVal = minVal + 1.0; // на случай, если все значения одинаковы
        }

        double binWidth = (maxVal - minVal) / binCount;

        QVector<double> counts(binCount, 0);
        QVector<double> borders(binCount);

        for (int i = 0; i < binCount; ++i)
        {
            borders[i] = minVal + i * binWidth;
        }

        for (double val : yValues)
        {
            int idx = static_cast<int>((val - minVal) / binWidth);
            if (idx >= binCount) idx = binCount - 1;
            if (idx < 0) idx = 0;
            counts[idx]++;
        }

        QCPBars *bars = new QCPBars(plot->xAxis, plot->yAxis);
        plot->addPlottable(bars);

        bars->setWidth(barWidth);
        bars->setData(borders, counts);
        bars->setName(varName);

        QPen pen;
        pen.setColor(barColor);
        bars->setPen(pen);

        QBrush brush;
        brush.setColor(barColor);
        brush.setStyle(Qt::SolidPattern);
        bars->setBrush(brush);

        colorIndex++;
    }

    plot->legend->setVisible(true);
    plot->rescaleAxes();

    if (hasXYRange())
    {
        plot->xAxis->setRange(getXMin(), getXMax());
        plot->yAxis->setRange(getYMin(), getYMax());
    }

    plot->replot();
}

void BarGraph::openSettings()
{
    BarGraphSettings *settings = new BarGraphSettings(this);
    settings->setAttribute(Qt::WA_DeleteOnClose);

    Experiment *exp = Experiment::getInstance();
    QList<Variable> &variables = exp->getVariables();

    QComboBox *xCombo = settings->getXAxisCombo();
    if (xCombo)
    {
        xCombo->clear();
        for (Variable &var : variables)
        {
            xCombo->addItem(var.get_name());
        }
        xCombo->setCurrentIndex(selectedIndex);

        connect(xCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, [this](int index)
                {
                    selectedIndex = index;
                    drawGraph(); });
    }

    QList<BarSetting> allSettings;
    for (int i = 0; i < variables.size(); ++i)
    {
        if (i == selectedIndex) continue;
        QString varName = variables[i].get_name();

        if (barsSettings.contains(varName))
        {
            allSettings.append(barsSettings[varName]);
        }
        else
        {
            BarSetting newBar;
            newBar.variableName = varName;
            newBar.color = Qt::blue;
            newBar.binCount = 10;
            newBar.barWidth = 1.0;
            newBar.visible = true;
            allSettings.append(newBar);
        }
    }

    settings->setBars(allSettings);

    connect(settings, &BarGraphSettings::settingsApplied, [this, settings]()
            {
        QList<BarSetting> newSettings = settings->getBars();
        for (const BarSetting &bar : newSettings)
        {
            barsSettings[bar.variableName] = bar;
        }
        drawGraph(); });

    settings->show();
}

void BarGraph::applySettings()
{
    updateAxesFromUI();
    drawGraph();
}