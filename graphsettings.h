#ifndef GRAPHSETTINGS_H
#define GRAPHSETTINGS_H

#include <QDialog>

class GraphSettings : public QDialog
{
    Q_OBJECT

public:
    explicit GraphSettings(QWidget *parent = nullptr);
    virtual ~GraphSettings();

    virtual void applySettings() = 0;  
};

#endif // GRAPHSETTINGS_H