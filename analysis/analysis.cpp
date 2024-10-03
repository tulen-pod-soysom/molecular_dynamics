#include "../evaporation/evaporation.h"
#include <fstream>
#include <iostream>
#include <vector>

constexpr static double boltzman_constant = 1.38E-23;

int main()
{
    std::ofstream f("out.txt");

    Model m;
    m.EvaluateTimeStep(0.01);

    double   left  = 0.9, right  = 1.5;
    unsigned width = 6,   height = 6;

    unsigned numOfExperimentsPerStep = 10;
    unsigned numOfSteps              = 100;
    double   initTemp         = 0;

    std::cout << "Type num of steps:" << std::endl;
    std::cin >> numOfSteps;

    std::cout << "Type num of experiments per step:" << std::endl;
    std::cin >> numOfExperimentsPerStep;

    std::cout << "Type initial velocities (Kelvin):" << std::endl;
    std::cin >> initTemp;

    m.SetTemperature(initTemp);

    std::cout << "Period interval: " << left << ' ' << right << std::endl;
    std::cout << "Particles amount: " << width << 'x' << height << std::endl;
    std::cout << "Number of experiments: " << numOfExperimentsPerStep << std::endl;
    std::cout << "Number of points: " << numOfSteps << std::endl;
    std::cout << "Initial velocities: " << initTemp << std::endl;

    double   b                 = 0;
    unsigned numOfIter         = 5000;
    unsigned iterDuration      = 500;
    unsigned numOfIterDuration = numOfIter - iterDuration;

    // std::vector<double> temprature(numOfSteps);
    // std::vector<int> loss(numOfSteps);

    // double t_sum    = 0;
    // double loss_sum = 0;

    double period = 0;
    double eqDis  = m.GetEquilibriumDistance();

    double numParticles = (double)height * (double)width;

    for (auto i = 0; i < numOfSteps; ++i)
    {
        b      = left + (right - left) * i / (double)numOfSteps;
        period = b * eqDis;

        for (auto j = 0; j < numOfExperimentsPerStep; ++j)
        {
            m.SetInitialConditions(width, height, period);

            m.Process(numOfIterDuration);
            m.GetKineticEnergySum();
            m.Process(iterDuration);

            // t_sum    += m.GetKineticEnergySum() / numParticles / boltzman_constant / iterDuration;
            // loss_sum += m.GetParticlesLoss();
            // temprature[i] = t_sum / (double)numOfExperimentsPerStep;
            // loss[i]       = loss_sum / numOfExperimentsPerStep;

            double temperature = m.GetKineticEnergySum() / numParticles / boltzman_constant / iterDuration;
            double loss = m.GetParticlesLoss();
            f << temperature << ' ' << loss << std::endl;
        }


        // t_sum    = 0;
        // loss_sum = 0;

        std::cout << "Point: " << i << '/' << numOfSteps << std::endl;
    }

    // Write in file
    // for (auto i = 0; i < numOfSteps; ++i)
        // f << temprature.at(i) << ' ' << loss.at(i) << std::endl;
}
