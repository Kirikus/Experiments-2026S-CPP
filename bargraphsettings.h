#ifndef BARGRAPHSETTINGS_H
#define BARGRAPHSETTINGS_H

#include <QDialog>
#include <QColor>
#include <QStringList>
#include <QComboBox>

namespace Ui
{
    class BarGraphSettings;
}

struct BarSetting
{
    QString variableName;
    QColor color;
    int binCount;
    double barWidth;
    bool visible;
};

class BarGraphSettings : public QDialog
{
    Q_OBJECT

public:
    explicit BarGraphSettings(QWidget *parent = nullptr);
    ~BarGraphSettings();

    QList<BarSetting> getBars() const;
    void setBars(const QList<BarSetting> &bars);
    int getSelectedXIndex() const;
    QComboBox* getXAxisCombo() const;

signals:
    void settingsApplied();

private slots:
    void onSave();
    void onCancel();

private:
    void updateTable();
    void setComboBox(int row, int column, const QStringList &items, const QString &current);

    Ui::BarGraphSettings *ui;
    QList<BarSetting> bars_e;
};

#endif // BARGRAPHSETTINGS_H