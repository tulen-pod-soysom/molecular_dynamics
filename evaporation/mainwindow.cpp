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

    m.SetInitialConditions(4,4,ui->DoubleSpinBox->value()* m.GetEquilibriumDistance());
    m.EvaluateTimeStep();

    draw_particles(ui->widget,m);

    draw_timer.setInterval(1000/24);

    // draw_timer.connect(SIGNAL(timeout()),SLOT(timer_event()));
    connect(&draw_timer,SIGNAL(timeout()),this,SLOT(timer_event()));

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw_particles(QCustomPlot *p, Model& m)
{    
    p->xAxis->setRange(0,30);
    p->yAxis->setRange(0,30);

    p->xAxis->setLabel(QString("iteration: " + QString::number(m.GetIteration())));

    auto part = m.GetParticles();

    QVector<double> x(part.size());
    QVector<double> y(part.size());

    for (auto i = 0; i < part.size(); ++i)
    {
        x[i] = part[i].m_x / m.GetEquilibriumDistance();
        y[i] = part[i].m_y / m.GetEquilibriumDistance();
    }

    double w = p->xAxis->range().size();
    double h = p->yAxis->range().size();

    double scr_w = p->rect().width();
    double scr_h = p->rect().height();

    double particle_pixel_radius = 1 * scr_w / w;
    auto g = p->graph(0);
    g->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, particle_pixel_radius));
    g->setLineStyle(QCPGraph::lsNone);
    g->setData(x,y,true);

    p->replot();
}

void MainWindow::start_simulation()
{
    while (true) {
        m.Process(20);

        // Qt can't draw from another thread, REMEMBER IT
        // draw_particles(ui->widget,m);
    }
}

void MainWindow::on_pushButton_toggled(bool checked)
{

}


void MainWindow::on_pushButton_clicked(bool checked)
{
    static QFuture<void> future;

    if (!checked)
    {
        m.SetInitialConditions(4,4,ui->DoubleSpinBox->value()* m.GetEquilibriumDistance());


        ui->pushButton->setText("Стоп");
        future = QtConcurrent::run([&]{start_simulation();});
        // start_simulation();
        draw_timer.start();
    }
    else
    {
        ui->pushButton->setText("Старт");
        future.cancel();
        future.waitForFinished();
        draw_timer.stop();
    }
}

void MainWindow::timer_event()
{
    draw_particles(ui->widget,m);
}

