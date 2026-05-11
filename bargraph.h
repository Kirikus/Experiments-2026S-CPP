#ifndef BARGRAPH_H
#define BARGRAPH_H

#include <QWidget>
#include "qcustomplot.h"
#include "graph.h"
#include "bargraphsettings.h"
#include <QMap>

class BarGraph : public Graph
{
    Q_OBJECT

public:
    explicit BarGraph(QWidget *parent = nullptr);
    ~BarGraph();

    void drawGraph() override;
    void openSettings() override;
    void applySettings() override;

private:
    QMap<QString, BarSetting> barsSettings;
    int selectedIndex = 0;
};

#endif // BARGRAPH_H