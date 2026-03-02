#include "graph_settings.h"
#include "ui_graph_settings.h"

graph_settings::graph_settings(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::graph_settings)
{
    ui->setupUi(this);
}

graph_settings::~graph_settings()
{
    delete ui;
}
