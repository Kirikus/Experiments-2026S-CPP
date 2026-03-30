#ifndef COLOURGRAPHSETTINGS_H
#define COLOURGRAPHSETTINGS_H

#include "graphsettings.h"


#include <QDialog>

namespace Ui {
class ColourGraphSettings;
}

class ColourGraphSettings : public GraphSettings
{
    Q_OBJECT

public:
    explicit ColourGraphSettings(QWidget *parent = nullptr);
    ~ColourGraphSettings();

    void applySettings() override;

private:
    Ui::ColourGraphSettings *ui;

};

#endif // COLOURGRAPHSETTINGS_H
