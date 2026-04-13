#include "lingraphsettings.h"
#include "ui_lingraphsettings.h"
#include <QColorDialog>
#include <QTableWidgetItem>
#include <QDialogButtonBox>
#include <QComboBox>
#include <QVBoxLayout>
#include "delegate_color.h"

LinGraphSettings::LinGraphSettings(QWidget *parent)
    : QDialog(parent), ui(new Ui::LinGraphSettings)
{
    ui->setupUi(this);

    ColorDelegate *colorDelegate = new ColorDelegate(this);
    ui->LineTable->setItemDelegateForColumn(0, colorDelegate);

    ui->LineTable->setColumnWidth(0, 100);
    ui->LineTable->setColumnWidth(1, 120);
    ui->LineTable->setColumnWidth(2, 120);

    connect(ui->AddLineButton, &QPushButton::clicked, this, &LinGraphSettings::onAddLine);
    connect(ui->DelLineButton, &QPushButton::clicked, this, &LinGraphSettings::onDeleteLine);

    if (ui->buttonBox)
    {
        connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &LinGraphSettings::onSave);
        connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &LinGraphSettings::onCancel);
    }

    onAddLine();
}

LinGraphSettings::~LinGraphSettings()
{
    delete ui;
}

void LinGraphSettings::onAddLine()
{
    int row = ui->LineTable->rowCount();
    ui->LineTable->insertRow(row);

    ui->LineTable->setItem(row, 0, new QTableWidgetItem("Синий"));
    ui->LineTable->item(row, 0)->setData(Qt::EditRole, QColor(Qt::blue));

    QStringList lineTypes = {"Сплошная", "Штрих", "Пунктир", "Штрих-пунктир"};
    setComboBox(row, 1, lineTypes, "Сплошная");

    QStringList pointTypes = {"Нет", "Круг", "Квадрат", "Крест", "Звезда"};
    setComboBox(row, 2, pointTypes, "Нет");
}

void LinGraphSettings::onDeleteLine()
{
    int row = ui->LineTable->currentRow();
    if (row >= 0)
    {
        ui->LineTable->removeRow(row);
    }
}

void LinGraphSettings::setColor(int row, const QColor &color)
{
    QTableWidgetItem *item = ui->LineTable->item(row, 0);
    item->setText(color.name());
    item->setData(Qt::EditRole, color);
    item->setBackground(color);
}

void LinGraphSettings::updateTable()
{
    ui->LineTable->setRowCount(lines_e.size());

    for (int i = 0; i < lines_e.size(); ++i)
    {
        const LineSetting &line = lines_e[i];

        ui->LineTable->setItem(i, 0, new QTableWidgetItem(line.color.name()));
        ui->LineTable->item(i, 0)->setData(Qt::EditRole, line.color);
        ui->LineTable->item(i, 0)->setBackground(line.color);

        ui->LineTable->setItem(i, 1, new QTableWidgetItem(line.lineType));
        ui->LineTable->setItem(i, 2, new QTableWidgetItem(line.pointType));
    }
}

QList<LineSetting> LinGraphSettings::getLines() const
{
    QList<LineSetting> lines;

    for (int i = 0; i < ui->LineTable->rowCount(); ++i)
    {
        LineSetting line;
        line.color = ui->LineTable->item(i, 0)->data(Qt::EditRole).value<QColor>();

        QComboBox *lineCombo = qobject_cast<QComboBox *>(ui->LineTable->cellWidget(i, 1));
        line.lineType = lineCombo ? lineCombo->currentText() : ui->LineTable->item(i, 1)->text();

        QComboBox *pointCombo = qobject_cast<QComboBox *>(ui->LineTable->cellWidget(i, 2));
        line.pointType = pointCombo ? pointCombo->currentText() : ui->LineTable->item(i, 2)->text();

        lines.append(line);
    }

    return lines;
}

void LinGraphSettings::setLines(const QList<LineSetting> &lines)
{
    lines_e = lines;
    updateTable();
}

void LinGraphSettings::onSave()
{

    emit settingsApplied();

    accept();
}

void LinGraphSettings::onCancel()
{
    reject();
}

void LinGraphSettings::setComboBox(int row, int column, const QStringList &items, const QString &current)
{
    QComboBox *combo = new QComboBox();
    combo->addItems(items);
    combo->setCurrentText(current);
    ui->LineTable->setCellWidget(row, column, combo);

    connect(combo, &QComboBox::currentTextChanged, [this, row, column](const QString &text)
            {
        QTableWidgetItem *item = ui->LineTable->item(row, column);
        if (!item) {
            item = new QTableWidgetItem(text);
            ui->LineTable->setItem(row, column, item);
        }
        item->setText(text); });
}
