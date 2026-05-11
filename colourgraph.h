#ifndef COLOURGRAPH_H
#define COLOURGRAPH_H

#include <QWidget>
#include "qcustomplot.h"
#include "graph.h"
#include "colourgraphsettings.h"

class ColourGraph : public Graph
{
    Q_OBJECT

public:
    explicit ColourGraph(QWidget *parent = nullptr);
    ~ColourGraph();

    void drawGraph() override;
    void openSettings() override;
    void applySettings() override;

private:
    QList<QColor> gradientColors = {Qt::blue, Qt::green, Qt::yellow, Qt::red};
    int selectedXIndex = 0;
    int selectedYIndex = 1;
};

#endif // COLOURGRAPH_H