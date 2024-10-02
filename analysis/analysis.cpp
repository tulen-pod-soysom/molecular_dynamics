#include "../evaporation/evaporation.h"
#include <fstream>
#include <iostream>
#include <vector>
constexpr static double m_boltzman = 1.38E-23;

int main()
{
    std::ofstream f("out.txt");

    Model m;
    m.EvaluateTimeStep(0.01);

    double   left  = 0.9, right  = 1.5;
    unsigned width = 6,   height = 6;

    unsigned numOfExperiments = 10;
    unsigned numOfPoints      = 100;
    double   initTemp         = 0;

    std::cout << "Type num of expirements:" << std::endl;
    std::cin >> numOfExperiments;

    std::cout << "Type num of points:" << std::endl;
    std::cin >> numOfPoints;

    std::cout << "Type initial temprature:" << std::endl;
    std::cin >> initTemp;

    m.SetTemprature(initTemp);

    std::cout << "Period interval: " << left << ' ' << right << std::endl;
    std::cout << "Particles amount: " << width << 'x' << height << std::endl;
    std::cout << "Number of expirements: " << numOfExperiments << std::endl;
    std::cout << "Number of points: " << numOfPoints << std::endl;
    std::cout << "Init temprature: " << initTemp << std::endl;

    double   b                 = 0;
    unsigned numOfIter         = 5000;
    unsigned iterDuration      = 500;
    unsigned numOfIterDuration = numOfIter - iterDuration;

    std::vector<double> temprature(numOfPoints);
    std::vector<int> loss(numOfPoints);

    double t_sum    = 0;
    double loss_sum = 0;

    double period = 0;
    double eqDis  = m.GetEquilibriumDistance();

    double numParticles = (double)height * (double)width;

    for (auto i = 0; i < numOfPoints; ++i)
    {
        b      = left + (right - left) * i / (double)numOfPoints;
        period = b * eqDis;

        for (auto j = 0; j < numOfExperiments; ++j)
        {
            m.SetInitialConditions(width, height, period);

            m.Process(numOfIterDuration);
            m.GetKineticEnergySum();
            m.Process(iterDuration);

            t_sum    += m.GetKineticEnergySum() / numParticles / m_boltzman / iterDuration;
            loss_sum += m.GetParticlesLoss();
        }

        temprature[i] = t_sum / (double)numOfExperiments;
        loss[i]       = loss_sum / numOfExperiments;

        t_sum    = 0;
        loss_sum = 0;

        std::cout << "Point: " << i <<std::endl;
    }

    // Write in file
    for (auto i = 0; i < numOfPoints; ++i)
        f << temprature.at(i) << ' ' << loss.at(i) << std::endl;
}
