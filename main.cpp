#include "mainwindow.h"
#include "experiment.h"
#include "variable.h"
#include "instrument.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Experiment* experiment = Experiment::getInstance();

    // Добавляем переменную с именем и значениями
    QList<double> values;
    values << 1.0 << 2.0 << 3.0;
    Variable var1(values, "Температура");
    experiment->getVariables().append(var1);

    // Добавляем инструменты
    Instrument inst1("Термометр", 0.5);
    QString errorType1 = "Абсолютная";
    inst1.set_error_type(errorType1);
    experiment->getInstruments().append(inst1);

    Instrument inst2("Вольтметр", 0.01);
    QString errorType2 = "Относительная";
    inst2.set_error_type(errorType2);
    experiment->getInstruments().append(inst2);

    MainWindow w;
    w.show();
    return a.exec();
}