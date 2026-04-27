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
    ui->LineTable->setItemDelegateForColumn(1, colorDelegate);

    ui->LineTable->setColumnWidth(0, 100);
    ui->LineTable->setColumnWidth(1, 120);
    ui->LineTable->setColumnWidth(2, 120);
    ui->LineTable->setColumnWidth(3, 120);
    ui->LineTable->setColumnWidth(4, 120);

    if (ui->buttonBox)
    {
        connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &LinGraphSettings::onSave);
        connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &LinGraphSettings::onCancel);
    }
}

LinGraphSettings::~LinGraphSettings()
{
    delete ui;
}

void LinGraphSettings::updateTable()
{
    ui->LineTable->setRowCount(lines_e.size());

    for (int i = 0; i < lines_e.size(); ++i)
    {
        const LineSetting &line = lines_e[i];

        // имя переменной (только для чтения) - 0 колонка
        QTableWidgetItem *nameItem = new QTableWidgetItem(line.variableName);
        nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
        ui->LineTable->setItem(i, 0, nameItem);

        // цвет - 1 колонка
        ui->LineTable->setItem(i, 1, new QTableWidgetItem(line.color.name()));
        ui->LineTable->item(i, 1)->setData(Qt::EditRole, line.color);
        ui->LineTable->item(i, 1)->setBackground(line.color);

        // тип линии - 2 колонка
        QStringList lineTypes = {"Сплошная", "Штрих", "Пунктир", "Штрих-пунктир"};
        setComboBox(i, 2, lineTypes, line.lineType);

        // тип точек - 3 колонка
        QStringList pointTypes = {"Нет", "Круг", "Квадрат", "Крест", "Звезда"};
        setComboBox(i, 3, pointTypes, line.pointType);

        // отображение линии - 4 колонка
        QTableWidgetItem *checkItem = new QTableWidgetItem();
        checkItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        checkItem->setCheckState(line.visible ? Qt::Checked : Qt::Unchecked);
        ui->LineTable->setItem(i, 4, checkItem);
    }
}

QList<LineSetting> LinGraphSettings::getLines() const
{
    QList<LineSetting> lines;

    for (int i = 0; i < ui->LineTable->rowCount(); ++i)
    {
        LineSetting line;

        line.variableName = ui->LineTable->item(i, 0)->text(); // имя

        line.color = ui->LineTable->item(i, 1)->data(Qt::EditRole).value<QColor>(); // цвет

        // тип линии
        QComboBox *lineCombo = qobject_cast<QComboBox *>(ui->LineTable->cellWidget(i, 2));
        line.lineType = lineCombo ? lineCombo->currentText() : ui->LineTable->item(i, 2)->text();

        // тип точки
        QComboBox *pointCombo = qobject_cast<QComboBox *>(ui->LineTable->cellWidget(i, 3));
        line.pointType = pointCombo ? pointCombo->currentText() : ui->LineTable->item(i, 3)->text();

        // отображение
        QTableWidgetItem *checkItem = ui->LineTable->item(i, 4);
        line.visible = checkItem ? (checkItem->checkState() == Qt::Checked) : true;

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

int LinGraphSettings::getSelectedXIndex() const
{
    return ui->comboXAxis->currentIndex();
}

QComboBox *LinGraphSettings::getXAxisCombo() const
{
    return ui->comboXAxis;
}
