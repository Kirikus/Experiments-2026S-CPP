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
    ~Graph();

    enum GraphType
    {
        Line,
        Bar,
        Colour
    };

    void setGraphType(GraphType type);

private:
    QCustomPlot *m_plot;
    QPushButton *m_settingsButton;
    GraphType m_type;

    Ui::Graph *ui;
};

#endif // GRAPH_H
