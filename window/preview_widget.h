#ifndef PREVIEW_WIDGET_H
#define PREVIEW_WIDGET_H

#include <QDialog>

namespace Ui {
class Preview_widget;
}

class Preview_widget : public QDialog
{
    Q_OBJECT

public:
    explicit Preview_widget(QWidget *parent = nullptr);
    ~Preview_widget();

private:
    Ui::Preview_widget *ui;
};

#endif // PREVIEW_WIDGET_H
