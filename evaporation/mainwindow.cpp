#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <thread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pE.resize(numOfPlotPoints);
    kE.resize(numOfPlotPoints);
    e.resize(numOfPlotPoints);
    ind.resize(numOfPlotPoints);

    std::iota(ind.begin(), ind.end(), 0);

    draw_energy(ui->widget_2, ui->widget_3, ui->widget_4, m);

    ui->widget->addGraph();

    m.SetInitialConditions(5, 5, ui->DoubleSpinBox->value() * m.GetEquilibriumDistance());
    m.EvaluateTimeStep();

    draw_particles(ui->widget, m);

    draw_timer.setInterval(1000 / 30);
    connect(&draw_timer, SIGNAL(timeout()), this, SLOT(timer_event()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw_particles(QCustomPlot* p, Model& m)
{
    p->xAxis->setRange(0, 30);
    p->yAxis->setRange(0, 30);

    p->xAxis->setLabel(QString("iteration: " + QString::number(m.GetIteration())));

    auto [x_, y_] = m.GetParticlePositions();

    QVector<double> x(x_.begin(), x_.end());
    QVector<double> y(y_.begin(), y_.end());

    for (auto i = 0; i < x.size(); ++i)
    {
        x[i] /= m.GetEquilibriumDistance();
        y[i] /= m.GetEquilibriumDistance();
    }

    // auto part = m.GetParticles();
    // QVector<double> x(part.size());
    // QVector<double> y(part.size());

    // for (auto i = 0; i < part.size(); ++i)
    // {
    //     x[i] = part[i].m_x / m.GetEquilibriumDistance();
    //     y[i] = part[i].m_y / m.GetEquilibriumDistance();
    // }

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

void MainWindow::start_simulation(bool& running)
{
    while (running)
    {
        m.Process(iterStep);

        if ( !isStarted )
           isStarted = true;

        peVal = m.GetPotentialEnergySum() / iterStep / 1.6E-19;
        keVal = m.GetKineticEnergySum() / iterStep / 1.6E-19;
        eVal  = peVal + keVal;

        // Qt can't draw from another thread, REMEMBER IT
        // QTimer::singleShot(0,this,SLOT(timer_event()));
        // draw_particles(ui->widget,m);
        // std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void MainWindow::on_pushButton_toggled(bool checked)
{

}

void MainWindow::draw_energy(QCustomPlot* kEPlot, QCustomPlot* pEPlot,
                             QCustomPlot* ePlot, Model& m)
{
    if (isStarted && !isScaled)
    {
        pE = QVector<double>(numOfPlotPoints, peVal);
        kE = QVector<double>(numOfPlotPoints, keVal);
        e  = QVector<double>(numOfPlotPoints, eVal);

        isScaled = true;
    }

    if (curIdPlot < numOfPlotPoints)
    {
        pE[curIdPlot] = peVal;
        kE[curIdPlot] = keVal;
        e[curIdPlot]  = eVal;

        ++curIdPlot;
    }
    else
    {
        pE = QVector<double>(numOfPlotPoints, 0);
        kE = QVector<double>(numOfPlotPoints, 0);
        e  = QVector<double>(numOfPlotPoints, 0);
        curIdPlot = 0;

        pE[curIdPlot] = peVal;
        kE[curIdPlot] = keVal;
        e[curIdPlot]  = eVal;
        ++curIdPlot;
        isScaled = false;
    }

    kEPlot->yAxis->setLabel("Кинетическая энергия,\n эВ");
    kEPlot->yAxis->setLabelFont(QFont("Arial", 8));
    kEPlot->addGraph();
    kEPlot->graph(0)->setData(ind, kE);
    kEPlot->rescaleAxes();
    kEPlot->replot();

    pEPlot->yAxis->setLabel("Потенциальная\n энергия, эВ");
    pEPlot->yAxis->setLabelFont(QFont("Arial", 8));
    pEPlot->addGraph();
    pEPlot->graph(0)->setData(ind, pE);
    pEPlot->rescaleAxes();
    pEPlot->replot();

    ePlot->yAxis->setLabel("Полная энергия, эВ");
    ePlot->yAxis->setLabelFont(QFont("Arial", 8));
    ePlot->addGraph();
    ePlot->graph(0)->setData(ind, e);
    ePlot->rescaleAxes();
    ePlot->replot();
}


void MainWindow::on_pushButton_clicked(bool checked)
{
    static QFuture<void> future;
    static QTimer sim_timer;
    sim_timer.setSingleShot(true);

    static bool running = true;



    if (checked)
    {
        running = true;
        m.SetInitialConditions(5,5,ui->DoubleSpinBox->value()* m.GetEquilibriumDistance());
        ui->pushButton->setText("Стоп");
        future = QtConcurrent::run([&]{start_simulation(running);});
        draw_timer.start();

        // sim_timer.singleShot(0,[&]{start_simulation();});
        // start_simulation();
    }
    else
    {
        running = false;
        draw_timer.stop();
        ui->pushButton->setText("Старт");
        future.waitForFinished();
        pE = QVector<double>(numOfPlotPoints, 0);
        kE = QVector<double>(numOfPlotPoints, 0);
        e  = QVector<double>(numOfPlotPoints, 0);
        curIdPlot = 0;
        isStarted = false;
        isScaled = false;
    }
}

void MainWindow::timer_event()
{
    draw_particles(ui->widget, m);
    draw_energy(ui->widget_2, ui->widget_3, ui->widget_4, m);
}

