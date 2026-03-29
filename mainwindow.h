#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openGraphSettings();
    void openPreview();
    void createLinGraph();
    void createBarGraph();
    void createColourGraph();
    void applyLinGraphSettings();
    void applyBarGraphSettings();
    void applyColourGraphSettings();

private:
    void setupCreateButton();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H