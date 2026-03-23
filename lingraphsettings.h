#ifndef LINGRAPHSETTINGS_H
#define LINGRAPHSETTINGS_H

#include "graphsettings.h"

#include <QDialog>

namespace Ui {
class LinGraphSettings;
}

class LinGraphSettings : public GraphSettings
{
    Q_OBJECT

public:
    explicit LinGraphSettings(QWidget *parent = nullptr);
    ~LinGraphSettings();

    void applySettings() override;

private:
    Ui::LinGraphSettings *ui;
};

#endif // LINGRAPHSETTINGS_H
