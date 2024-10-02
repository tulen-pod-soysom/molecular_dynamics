#include "../evaporation/evaporation.h"
#include <fstream>
#include <iostream>

constexpr static double m_boltzman = 1.38E-23;

int main()
{
    std::ofstream f("out.txt");

    Model m;

    double   left  = 0.9, right  = 1.5;
    unsigned width = 6,   height = 6;

    unsigned numOfExperiments = 10;
    unsigned numOfPoints      = 100;

    std::cout << "Type num of expirements:" << std::endl;
    std::cin >> numOfExperiments;

    std::cout << "Type num of points:" << std::endl;
    std::cin >> numOfPoints;

    std::cout << "Period interval: " << left << ' ' << right << std::endl;
    std::cout << "Particles amount: " << width << 'x' << height << std::endl;
    std::cout << "Number of expirements: " << numOfExperiments << std::endl;
    std::cout << "Number of points:" << numOfPoints << std::endl;

    double   b                 = 0;
    unsigned numOfIter         = 5000;
    unsigned iterDuration      = 20;
    unsigned numOfIterDuration = numOfIter - iterDuration;

    for (auto i = 0; i < numOfPoints; ++i)
    {
        b = left + (right - left) * i / (double)numOfPoints;
        m.EvaluateTimeStep(0.01);

        for (auto j = 0; j < numOfExperiments; ++j)
        {
            m.SetInitialConditions(width, height, b * m.GetEquilibriumDistance());

            m.Process(numOfIterDuration);
            m.GetKineticEnergySum();
            m.Process(iterDuration);

            auto x = m.GetKineticEnergySum() / m.GetParticlesAmount() / m_boltzman / numOfIter;
            //   auto x = b;
            auto y = m.GetParticlesLoss();

            f << x << ' ' << y << std::endl;
        }

        std::cout << "step: " << b << std::endl;
    }
}
