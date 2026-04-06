#include "mainwindow.h"
#include "experiment.h"
#include "variable.h"
#include "instrument.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Experiment* experiment = Experiment::getInstance();

    // Добавляем инструменты
    Instrument inst1("test inst1", 0.5);
    QString errorType1 = "Абсолютная";
    inst1.set_error_type(errorType1);
    experiment->getInstruments().append(inst1);

    Instrument inst2("test inst2", 0.01);
    QString errorType2 = "Относительная";
    inst2.set_error_type(errorType2);
    experiment->getInstruments().append(inst2);

    // Добавляем переменные
    QList<double> values1;
    Variable var1(values1, "test var1");
    experiment->getVariables().append(var1);
    
    QList<double> values2;
    Variable var2(values2, "test var2");
    experiment->getVariables().append(var2);

    MainWindow w;
    w.show();
    return a.exec();
}