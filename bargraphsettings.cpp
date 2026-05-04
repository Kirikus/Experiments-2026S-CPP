#include "bargraphsettings.h"
#include "ui_bargraphsettings.h"
#include <QPushButton>

BarGraphSettings::BarGraphSettings(QWidget *parent)
    : GraphSettings(parent)
    , ui(new Ui::BarGraphSettings)
{
    ui->setupUi(this);
    
    // Кнопки Save и Cancel
    connect(ui->SaveButton, &QPushButton::clicked, this, &BarGraphSettings::applySettings);
    connect(ui->CancelButton, &QPushButton::clicked, this, &BarGraphSettings::reject);
    
    // Кнопки добавления/удаления столбцов
    connect(ui->AddLineButton, &QPushButton::clicked, this, &BarGraphSettings::onAddBar);
    connect(ui->DelLineButton, &QPushButton::clicked, this, &BarGraphSettings::onDeleteBar);
}

BarGraphSettings::~BarGraphSettings()
{
    delete ui;
}

void BarGraphSettings::setBars(const QList<BarSetting> &bars)
{
    m_bars = bars;
    updateTableFromBars();
}

QList<BarSetting> BarGraphSettings::getBars() const
{
    return m_bars;
}

void BarGraphSettings::applySettings()
{
    updateBarsFromTable();
    emit settingsApplied();
    accept();
}

// Добавить новый столбец
void BarGraphSettings::onAddBar()
{
    BarSetting newBar;
    newBar.color = Qt::blue;
    newBar.fillPattern = "Сплошная";
    newBar.borderStyle = "Сплошная";
    m_bars.append(newBar);
    updateTableFromBars();
}

// Удалить выделенный столбец
void BarGraphSettings::onDeleteBar()
{
    int row = ui->BarTable->currentRow();
    if (row >= 0 && row < m_bars.size())
    {
        m_bars.removeAt(row);
        updateTableFromBars();
    }
}

// Заполнить таблицу из m_bars
void BarGraphSettings::updateTableFromBars()
{
    ui->BarTable->setRowCount(m_bars.size());
    for (int i = 0; i < m_bars.size(); ++i)
    {
        // Имя столбца в вертикальном заголовке
        QTableWidgetItem *nameItem = new QTableWidgetItem(QString("Bar %1").arg(i + 1));
        ui->BarTable->setVerticalHeaderItem(i, nameItem);
        
        // Цвет
        QTableWidgetItem *colorItem = new QTableWidgetItem(m_bars[i].color.name());
        ui->BarTable->setItem(i, 0, colorItem);
        
        // Тип заливки
        QTableWidgetItem *typeItem = new QTableWidgetItem(m_bars[i].fillPattern);
        ui->BarTable->setItem(i, 1, typeItem);
    }
}

// Сохранить данные из таблицы в m_bars
void BarGraphSettings::updateBarsFromTable()
{
    for (int i = 0; i < m_bars.size() && i < ui->BarTable->rowCount(); ++i)
    {
        QTableWidgetItem *colorItem = ui->BarTable->item(i, 0);
        if (colorItem)
            m_bars[i].color.setNamedColor(colorItem->text());
        
        QTableWidgetItem *typeItem = ui->BarTable->item(i, 1);
        if (typeItem)
            m_bars[i].fillPattern = typeItem->text();
    }
}