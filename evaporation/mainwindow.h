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

    const int iterStep        = 20;
          int numOfLoss       = 0;

    const int numOfPlotPoints = 512;
    int curIdPlot = 0;
    bool isStarted = false;
    bool isScaled  = false;

    void draw_particles(QCustomPlot* g, Model& m);
    void draw_energy(QCustomPlot* kEPlot, QCustomPlot* pEPlot, QCustomPlot* ePlot, Model& m);
    void start_simulation(bool& running);

    QTimer draw_timer;

    QVector<double> pE;
    QVector<double> kE;
    QVector<double> e;
    QVector<double> ind;

    double peVal      = 0;
    double keVal      = 0;
    double eVal       = 0;
    double temprature = 0;
};
#endif // MAINWINDOW_H
