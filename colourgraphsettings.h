#ifndef COLOURGRAPHSETTINGS_H
#define COLOURGRAPHSETTINGS_H

#include <QDialog>

namespace Ui {
class ColourGraphSettings;
}

class ColourGraphSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ColourGraphSettings(QWidget *parent = nullptr);
    ~ColourGraphSettings();

signals:
    void settingsApplied();

private slots:
    void onSave();
    void onCancel();

private:
    Ui::ColourGraphSettings *ui;
};

#endif // COLOURGRAPHSETTINGS_H