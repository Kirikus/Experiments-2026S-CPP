#include "lingraph.h"
#include "lingraphsettings.h"
#include <QDebug>
#include "experiment.h"
#include "variable.h"

LinGraph::LinGraph(QWidget *parent)
    : Graph(parent)
{
    drawGraph();
}

LinGraph::~LinGraph()
{
}

void LinGraph::drawGraph()
{
    QCustomPlot *plot = getPlot();
    if (!plot)
        return;

    plot->clearGraphs();
    updateAxesFromUI();

    Experiment *exp = Experiment::getInstance();
    QList<Variable> &variables = exp->getVariables();

    if (variables.isEmpty()) {
        plot->replot();
        return;
    }

    // Первая переменная будет по оси X
    QList<double> xValues = variables[0].get_values();
    
    // Рисуем каждую переменную
    for (int col = 0; col < variables.size(); ++col) {
        QList<double> yValues = variables[col].get_values();
        
        if (yValues.size() != xValues.size()) {
            qDebug() << "Size mismatch for variable" << col;
            continue;
        }
        
        QVector<double> xData, yData;
        for (int i = 0; i < xValues.size(); ++i) {
            xData.append(xValues[i]);
            yData.append(yValues[i]);
        }
        
        plot->addGraph();
        int idx = plot->graphCount() - 1;
        plot->graph(idx)->setData(xData, yData);
        
        QPen pen;
        // Цвета для разных переменных
        static QList<QColor> colors = {Qt::red, Qt::green, Qt::blue, Qt::magenta,
                                       Qt::cyan, Qt::darkYellow, Qt::darkCyan};
        pen.setColor(colors[col % colors.size()]);
        pen.setWidth(2);
        plot->graph(idx)->setPen(pen);
        plot->graph(idx)->setName(variables[col].get_name());
    }

    plot->legend->setVisible(true);
    plot->replot();
}

void LinGraph::openSettings()
{
    LinGraphSettings *settings = new LinGraphSettings(this);
    settings->setAttribute(Qt::WA_DeleteOnClose);

    settings->setLines(linesSettings);

    connect(settings, &LinGraphSettings::settingsApplied, [this, settings]()
            {
        linesSettings = settings->getLines();
        drawGraph(); });

    settings->show();
}

void LinGraph::applyLinesSettings(const QList<LineSetting> &lines)
{
    currentLines = lines;
    applySettings();
}

void LinGraph::applySettings()
{
    updateAxesFromUI();
    drawGraph();
}