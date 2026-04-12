#include "lingraph.h"
#include "lingraphsettings.h"
#include <QDebug>

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

    if (linesSettings.isEmpty())
    {
        LineSetting defaultLine;
        defaultLine.color = Qt::blue;
        defaultLine.lineType = "Сплошная";
        defaultLine.pointType = "Нет";
        linesSettings.append(defaultLine);
    }

    for (const LineSetting &line : linesSettings)
    {
        plot->addGraph();
        int graphIndex = plot->graphCount() - 1;

        QPen pen;
        pen.setColor(line.color);
        pen.setWidth(2);

        if (line.lineType == "Сплошная")
            pen.setStyle(Qt::SolidLine);
        else if (line.lineType == "Штрих")
            pen.setStyle(Qt::DashLine);
        else if (line.lineType == "Пунктир")
            pen.setStyle(Qt::DotLine);
        else if (line.lineType == "Штрих-пунктир")
            pen.setStyle(Qt::DashDotLine);
        else
            pen.setStyle(Qt::SolidLine);

        plot->graph(graphIndex)->setPen(pen);

        QCPScatterStyle scatterStyle;
        if (line.pointType == "Нет")
            scatterStyle.setShape(QCPScatterStyle::ssNone);
        else if (line.pointType == "Круг")
            scatterStyle.setShape(QCPScatterStyle::ssCircle);
        else if (line.pointType == "Квадрат")
            scatterStyle.setShape(QCPScatterStyle::ssSquare);
        else if (line.pointType == "Крест")
            scatterStyle.setShape(QCPScatterStyle::ssCross);
        else if (line.pointType == "Звезда")
            scatterStyle.setShape(QCPScatterStyle::ssStar);
        else
            scatterStyle.setShape(QCPScatterStyle::ssNone);

        scatterStyle.setSize(8);
        plot->graph(graphIndex)->setScatterStyle(scatterStyle);

        // example
        QVector<double> x = {0, 1, 2, 3, 4, 5};
        QVector<double> y = {0, 1, 4, 9, 16, 25};
        plot->graph(graphIndex)->setData(x, y);
    }

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