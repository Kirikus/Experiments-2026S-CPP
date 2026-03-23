#ifndef BARGRAPHSETTINGS_H
#define BARGRAPHSETTINGS_H

#include "graphsettings.h"

#include <QDialog>

namespace Ui {
class BarGraphSettings;
}

class BarGraphSettings : public GraphSettings
{
    Q_OBJECT

public:
    explicit BarGraphSettings(QWidget *parent = nullptr);
    ~BarGraphSettings();

    void applySettings() override;

private:
    Ui::BarGraphSettings *ui;

};

#endif // BARGRAPHSETTINGS_H
