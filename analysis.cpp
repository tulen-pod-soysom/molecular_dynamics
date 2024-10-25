#include "evaporation/evaporation.h"
#include <fstream>
#include <iostream>

constexpr static double m_boltzman = 1.38E-23;

int main() {
  std::ofstream f("out.txt");

  Model m;

  double left = 0.9, right = 1.5;
  unsigned width = 6, height = 6;
  std::cout << "period interval: " << left << ' ' << right << std::endl;
  std::cout << "particles amount: " << width << 'x' << height << std::endl;



  for (auto i = 0; i < 4096; ++i) {
    double b = left + (right - left) * i / 4096.;
    m.EvaluateTimeStep(0.01);
    for (auto j = 0; j < 10; ++j) {

      m.SetInitialConditions(width, height, b * m.GetEquilibriumDistance());

      int average_step = 50;
      
      m.Process(5000 - average_step);
      m.GetKineticEnergySum();
      m.Process(average_step);

      auto x = m.GetKineticEnergySum() / m.GetParticlesAmount() / m_boltzman / average_step;
      //   auto x = b;
      auto y = m.GetParticlesLoss();

      f << x << ' ' << y << std::endl;
    }
    std::cout << "step: " << b << std::endl;
  }
}