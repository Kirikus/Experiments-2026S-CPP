#ifndef GRAPH_SETTINGS_H
#define GRAPH_SETTINGS_H

#include <QWidget>

namespace Ui {
class graph_settings;
}

class graph_settings : public QWidget
{
    Q_OBJECT

public:
    explicit graph_settings(QWidget *parent = nullptr);
    ~graph_settings();

private:
    Ui::graph_settings *ui;
};

#endif // GRAPH_SETTINGS_H
