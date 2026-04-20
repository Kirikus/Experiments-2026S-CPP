#include "lingraph.h"
#include "lingraphsettings.h"
#include <QDebug>
#include "experiment.h"
#include "variable.h"
#include <map>

LinGraph::LinGraph(QWidget *parent)
    : Graph(parent)
{
    if (linesSettings.isEmpty())
    {
        LineSetting defaultLine;
        defaultLine.color = Qt::blue;
        defaultLine.lineType = "Сплошная";
        defaultLine.pointType = "Нет";
        defaultLine.visible = true;
        linesSettings.append(defaultLine);
    }

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

    if (variables.size() < 2)
    {
        plot->replot();
        return;
    }

    QList<double> xValues = variables[0].get_values();

    if (xValues.isEmpty())
    {
        plot->replot();
        return;
    }

    for (int col = 1; col < variables.size(); ++col)
    {
        QList<double> yValues = variables[col].get_values();

        if (yValues.size() != xValues.size())
            continue;

        QVector<double> xData, yData;
        for (int i = 0; i < xValues.size(); ++i)
        {
            xData.append(xValues[i]);
            yData.append(yValues[i]);
        }

        plot->addGraph();
        int idx = plot->graphCount() - 1;
        plot->graph(idx)->setData(xData, yData);
        plot->graph(idx)->setName(variables[col].get_name());

        QPen pen;
        pen.setWidth(2);

        if (col < linesSettings.size())
        {
            const LineSetting &line = linesSettings[col];
            pen.setColor(line.color);

            std::map<QString, Qt::PenStyle> lineStyleMap = {
                {"Сплошная", Qt::SolidLine},
                {"Штрих", Qt::DashLine},
                {"Пунктир", Qt::DotLine},
                {"Штрих-пунктир", Qt::DashDotLine}};

            std::map<QString, QCPScatterStyle::ScatterShape> pointStyleMap = {
                {"Нет", QCPScatterStyle::ssNone},
                {"Круг", QCPScatterStyle::ssCircle},
                {"Квадрат", QCPScatterStyle::ssSquare},
                {"Крест", QCPScatterStyle::ssCross},
                {"Звезда", QCPScatterStyle::ssStar}};

            if (lineStyleMap.find(line.lineType) != lineStyleMap.end())
            {
                pen.setStyle(lineStyleMap[line.lineType]);
            }
            else
            {
                pen.setStyle(Qt::SolidLine);
            }
            plot->graph(idx)->setPen(pen);

            QCPScatterStyle scatterStyle;
            scatterStyle.setSize(8);
            if (pointStyleMap.find(line.pointType) != pointStyleMap.end())
            {
                scatterStyle.setShape(pointStyleMap[line.pointType]);
            }
            else
            {
                scatterStyle.setShape(QCPScatterStyle::ssNone);
            }

            plot->graph(idx)->setScatterStyle(scatterStyle);

            plot->graph(idx)->setVisible(line.visible);
        }
        else
        {
            pen.setColor(Qt::blue);
            plot->graph(idx)->setPen(pen);
        }
    }

    plot->rescaleAxes();

    plot->legend->setVisible(true);
    plot->replot();
}

void LinGraph::openSettings()
{
    LinGraphSettings *settings = new LinGraphSettings(this);
    settings->setAttribute(Qt::WA_DeleteOnClose);

    Experiment *exp = Experiment::getInstance();
    QList<Variable> &variables = exp->getVariables();

    QList<LineSetting> allSettings;

    for (int col = 1; col < variables.size(); ++col)
    {
        LineSetting line;

        if (col < linesSettings.size())
        {
            line = linesSettings[col];
        }
        else
        {
            line.color = Qt::blue;
            line.lineType = "Сплошная";
            line.pointType = "Нет";
            line.visible = true;
        }

        allSettings.append(line);
    }

    settings->setLines(allSettings);

    connect(settings, &LinGraphSettings::settingsApplied, [this, settings]()
            {
        QList<LineSetting> newSettings = settings->getLines();
        

        for (int i = 0; i < newSettings.size(); ++i) {
            int col = i + 1;
            if (col < linesSettings.size()) {
                linesSettings[col] = newSettings[i];
            } else {
                linesSettings.append(newSettings[i]);
            }
        }
        
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