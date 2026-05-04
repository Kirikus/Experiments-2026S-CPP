#ifndef BARGRAPHSETTINGS_H
#define BARGRAPHSETTINGS_H

#include "graphsettings.h"
#include <QDialog>
#include <QList>
#include <QColor>

struct BarSetting
{
    QColor color = Qt::blue;
    QString fillPattern = "Сплошная";
    QString borderStyle = "Сплошная";
};

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

    void setBars(const QList<BarSetting> &bars);
    QList<BarSetting> getBars() const;

signals:
    void settingsApplied();

private slots:
    void onAddBar();
    void onDeleteBar();

private:
    void updateTableFromBars();
    void updateBarsFromTable();

    Ui::BarGraphSettings *ui;
    QList<BarSetting> m_bars;
};

#endif // BARGRAPHSETTINGS_H