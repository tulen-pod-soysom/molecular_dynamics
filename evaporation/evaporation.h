#ifndef EVAPORATION_H
#define EVAPORATION_H

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <tuple>
#include <vector>
#include <mutex>

struct Particle
{
public:    // variables

    double m_x  = 0;
    double m_y  = 0;
    double m_vX = 0;
    double m_vY = 0;
    double m_aX = 0;
    double m_aY = 0;
    double m_aX_previous = 0;
    double m_aY_previous = 0;
    constexpr static double m_m  = 39.948 * 1.66053906660E-27;


public:    // methods

    Particle(){};

    ~Particle(){};
};

class Model
{
private:    // variables

    std::vector<Particle> m_particles;

    double    m_spaceLeft    = 0;
    double    m_spaceRight   = 30*m_equilibrium_distance;
    double    m_spaceTop     = 30*m_equilibrium_distance;
    double    m_spaceBot     = 0;

    double    m_maxIter    = 5000;
    double    m_iter       = 0;
    double    m_timestep;

    constexpr static double m_sigma = 0.382 * 1E-9;
    constexpr static double m_equilibrium_distance = m_sigma*1.12246204831; // pow(2,1/6.)
    constexpr static double m_sigma6 = m_sigma*m_sigma*m_sigma*m_sigma*m_sigma*m_sigma;
    constexpr static double m_depth = 0.0103 * 1.602176634E-19;

    std::mutex protection_mutex;
public:     // methods

    Model() = default;

    ~Model() = default;

    auto GetParticles() {
        std::lock_guard<std::mutex> lock(protection_mutex);
        return m_particles;
    }

    auto GetParticlePositions()
    {
        std::lock_guard<std::mutex> lock(protection_mutex);
        std::vector<double> x(m_particles.size());
        std::vector<double> y(m_particles.size());
        for (auto i = 0; i < m_particles.size(); ++i)
        {
            x[i] = m_particles[i].m_x;
            y[i] = m_particles[i].m_y;
        }
        return std::make_tuple(x,y);
    }

    // Равновесное расстояние
    auto GetEquilibriumDistance() {return m_equilibrium_distance;}

    auto grid2d(int i, int j, double period, double center_x, double center_y)
    {
        double x = center_x + i * period;
        double y = center_y + j * period;
        return std::make_tuple(x,y);
    }

    void SetInitialConditions(int width , int height, double period)
    {

        m_iter = 0;
        // purely centered grid is not beautiful if side is even
        // double center_x = int(m_spaceRight - m_spaceLeft) / 2;
        // double center_y = int(m_spaceTop - m_spaceBot) / 2;

        double center_x = (m_spaceRight - m_spaceLeft) / 2.;
        double center_y = (m_spaceTop - m_spaceBot)/ 2.;

        m_particles = std::vector<Particle>(width*height);

        // height or width == 1 is problematic
        for(int i = -height/2; i <= height/2; ++i)
          for (int j = -width / 2; j <= width / 2; ++j) {
            auto [x,y] = grid2d(i, j, period, center_x, center_y);
            m_particles[(i + height/2) * height + (j+width/2)].m_x = x;
            m_particles[(i + height/2) * height + (j+width/2)].m_y = y;
          }
    }



    double EvaluateTimeStep()
    {
        m_timestep = 0.01 * sqrt(Particle::m_m*m_equilibrium_distance*m_equilibrium_distance/m_depth);
        return m_timestep;
    }

    inline static auto particle_interaction(Particle& p1, Particle& p2)
    {
        double dx = p2.m_x - p1.m_x;
        double dy = p2.m_y - p1.m_y;

        double r2  = dx*dx + dy*dy;
        // double r   = std::sqrt(r2);
        double ir6 = 1/(r2*r2*r2);

        // constexpr double depth =
        // constexpr double sigma =
        // constexpr double sigma6 = sigma*sigma*sigma*sigma*sigma*sigma;

        double potential = 4 * m_depth * m_sigma6 * ir6 * (m_sigma6 * ir6 - 1);
        double force2_x = -24 * m_depth * m_sigma6 * ir6 * (-2*m_sigma6*ir6 + 1) * dx / r2;
        double force2_y = -24 * m_depth * m_sigma6 * ir6 * (-2*m_sigma6*ir6 + 1) * dy / r2;

        double force1_x = -force2_x;
        double force1_y = -force2_y;

        return std::make_tuple(potential,force1_x,force1_y,force2_x,force2_y);
    }


    template <typename T> 
    auto integrate_position(T pos, T vel, T acc, T dt)
    {
        return pos + vel * dt + acc*dt*dt/2.0;
    }

    template <typename T> 
    auto integrate_velocity(T vel, T acc_prev, T acc_new, T dt)
    {
        return vel + dt*(acc_prev + acc_new)/2.0;
    }

    // Interaction function requires to return potential energy and 4 force projections for two particles as a std::tuple<T,T,T,T,T>
    template <typename InputIt, typename InteractionFunc>
    auto velocity_verlet_process(InputIt begin, InputIt end,
                                 InteractionFunc particle_interaction) 
    {

        // swap a_i with a_i+1
      for (auto i = begin; i != end; ++i) {
        i->m_aX_previous = i->m_aX;
        i->m_aX = 0.0;
        i->m_aY_previous = i->m_aY;
        i->m_aY = 0.0;
      }


      { // defines lock's scope
      std::lock_guard<std::mutex> lock(protection_mutex);
      for (auto i = begin; i != end; ++i) {
        i->m_x =
            integrate_position(i->m_x, i->m_vX, i->m_aX_previous, m_timestep);
        i->m_y =
            integrate_position(i->m_y, i->m_vY, i->m_aY_previous, m_timestep);
      }
      }

        double potential_energy = 0;
      for (auto i = begin; i != end - 1; ++i)
        for (auto j = i + 1; j != end; ++j) {
          auto [pot, force_x1, force_y1, force_x2, force_y2] = particle_interaction(*i, *j);
          i->m_aX += force_x1;
          i->m_aY += force_y1;
          j->m_aX += force_x2;
          j->m_aY += force_y2;

          potential_energy += pot;
        }

      for (auto i = begin; i != end; ++i) {
          i->m_aX /= Particle::m_m;
          i->m_aY /= Particle::m_m;
      }

      for (auto i = begin; i != end; ++i) {
        i->m_vX =
            integrate_velocity(i->m_vX, i->m_aX, i->m_aX_previous, m_timestep);
        i->m_vY =
            integrate_velocity(i->m_vY, i->m_aY, i->m_aY_previous, m_timestep);
      }
    }

    void Process(uint32_t iterations)
    {
      for (uint32_t i = 0; i < iterations; ++i)
        Process();
    }
    void Process()
    {
        velocity_verlet_process(m_particles.begin(), m_particles.end(), particle_interaction);
        m_iter++;
    }

    uint32_t GetIteration(){return m_iter;}

};

#endif    // EVAPORATION_H
