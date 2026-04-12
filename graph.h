#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <QPushButton>

class QCustomPlot;

namespace Ui
{
    class Graph;
}

class Graph : public QWidget
{
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = nullptr);
    virtual ~Graph();

    void set_axis_labels(const QString &xLabel, const QString &yLabel);
    void set_axis_ranges(double xMin, double xMax, double yMin, double yMax);

    virtual void drawGraph() = 0;
    virtual void openSettings() = 0;
    virtual void applySettings() = 0;

protected:
    QCustomPlot *getPlot() const;
    void updateAxesFromUI();

private slots:
    void onSettingsClicked();

private:
    QPushButton *m_settingsButton;
    Ui::Graph *ui;
};

#endif // GRAPH_H
