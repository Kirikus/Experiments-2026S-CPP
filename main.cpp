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
    Instrument inst1("Линейка", 0.5);
    QString errorType1 = "Абсолютная";
    inst1.set_error_type(errorType1);
    experiment->addInstrument(inst1);

    Instrument inst2("Вольтметр", 0.01);
    QString errorType2 = "Относительная";
    inst2.set_error_type(errorType2);
    experiment->addInstrument(inst2);

    Instrument* ruler_ptr = &experiment->getInstruments()[0];
    Instrument* voltmeter_ptr = &experiment->getInstruments()[1];

    // Добавляем переменные
    QList<double> values1;
    values1 << 20 << 21 << 22 << 23;
    Variable var1(values1, "Длина", ruler_ptr);
    experiment->addVariable(var1);

    QList<double> values2;
    values2 << 9 << 10 << 11 << 12;
    Variable var2(values2, "Ширина", ruler_ptr);
    experiment->addVariable(var2);

    QList<double> values3;
    values3 << 5 << 6 << 7 << 8;
    Variable var3(values3, "Высота", ruler_ptr);
    experiment->addVariable(var3);
    
    QList<double> values4;
    values4 << 219 << 220 << 221 << 222;
    Variable var4(values4, "Напряжение", voltmeter_ptr);
    experiment->addVariable(var4);

    Constant const1("Ускорение", 9.8, 0.1, "g", false);
    experiment->getConstants().append(const1);

    MainWindow w;
    w.show();
    return a.exec();
}