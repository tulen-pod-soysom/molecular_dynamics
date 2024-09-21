#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtConcurrent/QtConcurrent>
#include <qcustomplot.h>
#include "evaporation.h"

QT_BEGIN_NAMESPACE
namespace Ui {
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
    void on_pushButton_toggled(bool checked);
    void on_pushButton_clicked(bool checked);
    void timer_event();

private:
    Ui::MainWindow *ui;

    Model m;

    void draw_particles(QCustomPlot* g, Model& m);
    void start_simulation();

    QTimer draw_timer;

};
#endif // MAINWINDOW_H
