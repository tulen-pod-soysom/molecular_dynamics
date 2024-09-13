#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVector<double> arr(512);
    QVector<double> ind(512); std::iota(ind.begin(),ind.end(),0);

    std::transform(arr.begin(),arr.end(),arr.begin(),[](double){return (double)rand()/RAND_MAX;});

    ui->widget_2->yAxis->setLabel("Кинетическая энергия");
    ui->widget_2->yAxis->setLabelFont(QFont("Arial",8));
    ui->widget_2->addGraph();
    ui->widget_2->graph(0)->setData(ind,arr);
    ui->widget_2->rescaleAxes();
    ui->widget_2->replot();

    std::transform(arr.begin(),arr.end(),arr.begin(),[](double){return (double)rand()/RAND_MAX;});
    ui->widget_3->yAxis->setLabel("Потенциальная\n энергия");
    ui->widget_3->yAxis->setLabelFont(QFont("Arial",8));
    ui->widget_3->addGraph();
    ui->widget_3->graph(0)->setData(ind,arr);
    ui->widget_3->rescaleAxes();
    ui->widget_3->replot();

    std::transform(arr.begin(),arr.end(),arr.begin(),[](double){return (double)rand()/RAND_MAX;});
    ui->widget_4->yAxis->setLabel("Полная энергия");
    ui->widget_4->yAxis->setLabelFont(QFont("Arial",8));
    ui->widget_4->addGraph();
    ui->widget_4->graph(0)->setData(ind,arr);
    ui->widget_4->rescaleAxes();
    ui->widget_4->replot();

}

MainWindow::~MainWindow()
{
    delete ui;
}
