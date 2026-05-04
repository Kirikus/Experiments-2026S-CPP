#ifndef LINGRAPH_H
#define LINGRAPH_H

#include <QDialog>
#include <QWidget>
#include "qcustomplot.h"
#include "graph.h"
#include "lingraphsettings.h"
#include <QMap>

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
    QMap<QString, LineSetting> linesSettings;
    int selectedIndex = 0;

};

#endif // LINGRAPH_H
