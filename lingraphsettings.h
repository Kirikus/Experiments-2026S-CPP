#ifndef LINGRAPHSETTINGS_H
#define LINGRAPHSETTINGS_H

#include <QDialog>
#include <QColor>
#include <QStringList>

namespace Ui
{
    class LinGraphSettings;
}

struct LineSetting
{
    QColor color;
    QString lineType;
    QString pointType;
    bool visible;
};

class LinGraphSettings : public QDialog
{
    Q_OBJECT

public:
    explicit LinGraphSettings(QWidget *parent = nullptr);
    ~LinGraphSettings();
    
    QList<LineSetting> getLines() const;
    void setLines(const QList<LineSetting> &lines);

signals:
    void settingsApplied(); 

private slots:
    void onSave();
    void onCancel();
    

private:
    void updateTable();
    void setColor(int row, const QColor &color);
    void setComboBox(int row, int column, const QStringList &items, const QString &current);

    Ui::LinGraphSettings *ui;
    QList<LineSetting> lines_e;
};

#endif // LINGRAPHSETTINGS_H
