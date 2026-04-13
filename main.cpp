#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Experiment* experiment = Experiment::getInstance();

    // Добавляем инструменты
    Instrument inst1("Линейка", 0.5);
    QString errorType1 = "Absolute";
    inst1.set_error_type(errorType1);
    experiment->getInstruments().append(inst1);

    Instrument inst2("Вольтметр", 0.01);
    QString errorType2 = "Relative";
    inst2.set_error_type(errorType2);
    experiment->getInstruments().append(inst2);

    // Добавляем переменные
    QList<double> values1;
    Variable var1(values1, "Длина");
    values1 << 9 << 10 << 11 << 12;
    experiment->getVariables().append(var1);
    
    QList<double> values2;
    Variable var2(values2, "Напряжение");
    values2 << 219 << 220 << 221;
    experiment->getVariables().append(var2);

    MainWindow w;

    w.show();
    return a.exec();
}
