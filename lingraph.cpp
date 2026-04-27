#include "lingraph.h"
#include "lingraphsettings.h"
#include <QDebug>
#include "experiment.h"
#include "variable.h"
#include <map>

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

    if (variables.size() < 2)
    {
        plot->replot();
        return;
    }

    if (selectedIndex < 0 || selectedIndex >= variables.size())
    {
        selectedIndex = 0;
    }

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

        if (linesSettings.contains(varName))
        {
            const LineSetting &line = linesSettings[varName];
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
            // чтобы сразу разными цветами рисовались по умолчанию
            pen.setColor(defaultColors[colorIndex % defaultColors.size()]);
            plot->graph(idx)->setPen(pen);
            colorIndex++;
        }
    }
    plot->rescaleAxes();
    if (hasXYRange())
    {
        plot->xAxis->setRange(getXMin(), getXMax());
        plot->yAxis->setRange(getYMin(), getYMax());
    }

    plot->legend->setVisible(true);
    plot->replot();
}

void LinGraph::openSettings()
{
    LinGraphSettings *settings = new LinGraphSettings(this);
    settings->setAttribute(Qt::WA_DeleteOnClose);

    Experiment *exp = Experiment::getInstance();
    QList<Variable> &variables = exp->getVariables();

    QComboBox *xCombo = settings->getXAxisCombo();

    //выбор икса из комбобокса
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

    QList<LineSetting> allSettings;
    for (int i = 0; i < variables.size(); ++i)
    {
        if (i == selectedIndex)
            continue;

        QString varName = variables[i].get_name();

        if (linesSettings.contains(varName))
        {
            allSettings.append(linesSettings[varName]);
        }
        else
        {
            LineSetting newLine;
            newLine.variableName = varName;
            newLine.color = Qt::blue;
            newLine.lineType = "Сплошная";
            newLine.pointType = "Нет";
            newLine.visible = true;
            allSettings.append(newLine);
        }
    }

    settings->setLines(allSettings);

    connect(settings, &LinGraphSettings::settingsApplied, [this, settings]()
            {
        QList<LineSetting> newSettings = settings->getLines();
        for (const LineSetting &line : newSettings) {
            linesSettings[line.variableName] = line;
        }
        
        drawGraph(); });

    settings->show();
}

void LinGraph::applySettings()
{
    updateAxesFromUI();
    drawGraph();
}