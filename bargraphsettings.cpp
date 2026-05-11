#include "bargraphsettings.h"
#include "ui_bargraphsettings.h"
#include <QColorDialog>
#include <QTableWidgetItem>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QVBoxLayout>
#include "delegate_color.h"

BarGraphSettings::BarGraphSettings(QWidget *parent)
    : QDialog(parent), ui(new Ui::BarGraphSettings)
{
    ui->setupUi(this);

    ColorDelegate *colorDelegate = new ColorDelegate(this);
    ui->BarTable->setItemDelegateForColumn(1, colorDelegate);

    ui->BarTable->setColumnWidth(0, 120);
    ui->BarTable->setColumnWidth(1, 100);
    ui->BarTable->setColumnWidth(2, 80);
    ui->BarTable->setColumnWidth(3, 80);
    ui->BarTable->setColumnWidth(4, 80);

    if (ui->buttonBox)
    {
        connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &BarGraphSettings::onSave);
        connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &BarGraphSettings::onCancel);
    }
}

BarGraphSettings::~BarGraphSettings()
{
    delete ui;
}

void BarGraphSettings::updateTable()
{
    ui->BarTable->setRowCount(bars_e.size());

    for (int i = 0; i < bars_e.size(); ++i)
    {
        const BarSetting &bar = bars_e[i];

        // Variable Name (0)
        QTableWidgetItem *nameItem = new QTableWidgetItem(bar.variableName);
        nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
        ui->BarTable->setItem(i, 0, nameItem);

        // Color (1)
        if (!ui->BarTable->item(i, 1))
        {
            ui->BarTable->setItem(i, 1, new QTableWidgetItem());
        }
        ui->BarTable->item(i, 1)->setData(Qt::EditRole, bar.color);
        ui->BarTable->item(i, 1)->setBackground(bar.color);
        ui->BarTable->item(i, 1)->setText(bar.color.name());

        // Bin Count (2)
        if (!ui->BarTable->item(i, 2))
        {
            ui->BarTable->setItem(i, 2, new QTableWidgetItem());
        }
        ui->BarTable->item(i, 2)->setData(Qt::EditRole, bar.binCount);
        ui->BarTable->item(i, 2)->setText(QString::number(bar.binCount));

        // Bar Width (3)
        if (!ui->BarTable->item(i, 3))
        {
            ui->BarTable->setItem(i, 3, new QTableWidgetItem());
        }
        ui->BarTable->item(i, 3)->setData(Qt::EditRole, bar.barWidth);
        ui->BarTable->item(i, 3)->setText(QString::number(bar.barWidth));

        // Visible (4)
        QTableWidgetItem *checkItem = new QTableWidgetItem();
        checkItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        checkItem->setCheckState(bar.visible ? Qt::Checked : Qt::Unchecked);
        ui->BarTable->setItem(i, 4, checkItem);
    }
}

QList<BarSetting> BarGraphSettings::getBars() const
{
    QList<BarSetting> bars;

    for (int i = 0; i < ui->BarTable->rowCount(); ++i)
    {
        BarSetting bar;

        bar.variableName = ui->BarTable->item(i, 0)->text();
        bar.color = ui->BarTable->item(i, 1)->data(Qt::EditRole).value<QColor>();
        bar.binCount = ui->BarTable->item(i, 2)->text().toInt();
        bar.barWidth = ui->BarTable->item(i, 3)->text().toDouble();
        
        QTableWidgetItem *checkItem = ui->BarTable->item(i, 4);
        bar.visible = checkItem ? (checkItem->checkState() == Qt::Checked) : true;

        bars.append(bar);
    }

    return bars;
}

void BarGraphSettings::setBars(const QList<BarSetting> &bars)
{
    bars_e = bars;
    updateTable();
}

void BarGraphSettings::onSave()
{
    emit settingsApplied();
    accept();
}

void BarGraphSettings::onCancel()
{
    reject();
}

int BarGraphSettings::getSelectedXIndex() const
{
    return ui->comboXAxis->currentIndex();
}

QComboBox *BarGraphSettings::getXAxisCombo() const
{
    return ui->comboXAxis;
}