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

    ui->widget->addGraph();


    draw_particles(ui->widget);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw_particles(QCustomPlot *p)
{
    std::random_device rd;
    std::uniform_real_distribution<double> dist(0,5);

    QVector<double> x(60);
    QVector<double> y(60);
    std::generate(x.begin(),x.end(),[&rd,&dist]{return dist(rd);});
    std::generate(y.begin(),y.end(),[&rd,&dist]{return dist(rd);});

    double w = p->xAxis->range().size();
    double h = p->yAxis->range().size();

    double scr_w = p->rect().width();
    double scr_h = p->rect().height();

    double particle_pixel_radius = 0.1 * scr_w / w;

    auto g = p->graph(0);
    g->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, particle_pixel_radius));
    g->setLineStyle(QCPGraph::lsNone);
    g->setData(x,y,true);

}
