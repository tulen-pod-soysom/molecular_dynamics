#ifndef EVAPORATION_H
#define EVAPORATION_H

#include <cmath>
#include <cstdint>
#include <vector>

struct Particle
{
public:    // variables

    double m_x  = 0;
    double m_y  = 0;
    double m_vX = 0;
    double m_vY = 0;
    double m_aX = 0;
    double m_aY = 0;
    // double m_m  = 0;

public:    // methods

    Particle(){};

    ~Particle(){};
};




class Model
{
private:    // variables

    std::vector<Particle> m_particles;

    double    m_maxIter    = 5000;
    double    m_iter       = 0;
    double    m_timestep;

public:     // methods

    Model();

    ~Model();

    auto& GetParticles() {return m_particles;}

    void SetInitialConditions();

    auto ParticleInteraction(Particle& p1, Particle& p2)
    {
        double dx = p2.m_x - p1.m_x;
        double dy = p2.m_y - p1.m_y;

        double r2  = dx*dx + dy*dy;
        // double r   = std::sqrt(r2);
        double ir6 = 1/(r2*r2*r2);

        constexpr double depth = 0.0103 * 1.602176634E-19;
        constexpr double sigma = 0.382 * 1E-9;
        constexpr double sigma6 = sigma*sigma*sigma*sigma*sigma*sigma;

        double potential = 4 * depth * sigma6 * ir6 * (sigma6 * ir6 - 1);
        double force2_x = -24 * depth * sigma6 * ir6 * (-2*sigma6*ir6 + 1) * dx / r2;
        double force2_y = -24 * depth * sigma6 * ir6 * (-2*sigma6*ir6 + 1) * dy / r2;

        double force1_x = -force2_x;
        double force1_y = -force2_y;


        
    }

    template<typename Real, typename RealFunction>
    auto VelocityVerlet(Real& position, Real& velocity, Real& acceleration, RealFunction calculate_acceleration)
    {
        position += velocity * m_timestep + aX * m_timestep * m_timestep / 2.0;
        velocity += 
    };


    void Process(uint32_t iterations)
    {
      for (uint32_t i = 0; i < iterations; ++i)
        Process();
    }
    void Process()
    {
        
        m_iter++;
    }

};

#endif    // EVAPORATION_H
