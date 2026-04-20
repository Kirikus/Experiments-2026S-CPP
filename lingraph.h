#ifndef LINGRAPH_H
#define LINGRAPH_H

#include <QDialog>
#include <QWidget>
#include "qcustomplot.h"
#include "graph.h"
#include "lingraphsettings.h"

class LinGraph : public Graph
{
    Q_OBJECT

public:
    explicit LinGraph(QWidget *parent = nullptr);
    ~LinGraph();

    void drawGraph() override;
    void openSettings() override;
    void applySettings() override;

private:
    void applyLinesSettings(const QList<LineSetting> &lines);
    
    QList<LineSetting> currentLines;
    QVector<double> m_xData;
    QVector<double> m_yData;
    QList<LineSetting> linesSettings;

};

#endif // LINGRAPH_H
