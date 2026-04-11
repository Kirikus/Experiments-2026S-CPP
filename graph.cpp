#include "graph.h"
#include "qcustomplot.h"
#include "ui_graph.h"
#include <QVBoxLayout>
#include <QPushButton>

Graph::Graph(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Graph)
    , m_type(Line)
{
    ui->setupUi(this);
}

void Graph::setGraphType(GraphType type)
{
    m_type = type;

     QCustomPlot *plot = ui->customPlot;

    if (type == Line) {
        plot->addGraph();
        plot->graph(0)->setPen(QPen(Qt::blue));
        plot->replot();
    } else if (type == Bar) {

    } else if (type == Colour) {

    }
}


Graph::~Graph()
{
    delete ui;
}
