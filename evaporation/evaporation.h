#ifndef EVAPORATION_H
#define EVAPORATION_H

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <tuple>
#include <vector>
#include <mutex>
#include <random>

struct Particle
{
public:    // variables

    double                  m_x           = 0;                             //!< Value of x coordinate
    double                  m_y           = 0;                             //!< Value of y coordinate
    double                  m_vX          = 0;                             //!< Value of x velocity
    double                  m_vY          = 0;                             //!< Value of y velocity
    double                  m_aX          = 0;                             //!< Current value of x acceleration
    double                  m_aY          = 0;                             //!< Current value of y acceleration
    double                  m_aX_previous = 0;                             //!< Previous value of x acceleration
    double                  m_aY_previous = 0;                             //!< Previous value of y acceleration
    constexpr static double m_m           = 39.948 * 1.66053906660E-27;    //!< Mass of particle
    double                  m_vSum        = 0;                             //!< Summ of velocity modul
    uint32_t                m_counter     = 0;                             //!< Number of items in sum

public:    // methods

    // Default constructor
    Particle(){};

    // Default destructor
    ~Particle(){};

    // Add velocity to sum function
    void AddVelocityInSum()
    {
        m_vSum += m_vX * m_vX + m_vY * m_vY;
        ++m_counter;
    };

    // Get mean square velocity
    double GetMeanSVelocity()
    {
        if (m_counter == 0)
            return 0;

        double mVelocity = m_vSum / (double)m_counter;

        m_counter = 0;
        m_vSum    = 0;

        return mVelocity;
    };
};

class Model
{
private:    // variables

    constexpr static double m_sigma                = 0.382 * 1E-9;                   //!< Distance between atomic centers
    constexpr static double m_equilibrium_distance = m_sigma * 1.12246204831;        //!< Equilibrium distance between particles
    constexpr static double m_sigma6               = m_sigma * m_sigma * m_sigma *
                                                     m_sigma * m_sigma * m_sigma;    //!< Value of distanse between atomic centers to the sixth power
    constexpr static double m_depth                = 0.0103 * 1.602176634E-19;       //!< Potential module energy
                                                                                     //!< of interaction between atoms at equilibrium

    constexpr static double m_boltzman             = 1.38E-23;
    std::vector<Particle>   m_particles;                                             //!< Array with particles

    double    m_spaceLeft        = 0;                                                //!< Position of the left wall of the modeling area
    double    m_spaceRight       = 30 * m_equilibrium_distance;                      //!< Position of the right wall of the modeling area
    double    m_spaceTop         = 30 * m_equilibrium_distance;                      //!< Position of the top wall of the modeling area
    double    m_spaceBot         = 0;                                                //!< Position of the bot wall of the modeling area
    double    m_spaceWidthHalf   = (m_spaceRight - m_spaceLeft) / 2;                 //!< Value of half space width
    double    m_spaceHeightHalf  = (m_spaceTop - m_spaceBot) / 2;                    //!< Value of half space height

    double    m_maxIter    = 5000;                                                   //!< Max value of iterations
    double    m_iter       = 0;                                                      //!< Current value of iterations
    double    m_timestep   = 0;                                                      //!< Time step of modeling
    double    m_kESum      = 0;                                                      //!< Kinetic energy sum
    double    m_pESum      = 0;                                                      //!< Potencial energy sum

    double    m_temp       = 1;                                                      //!< Init temprature in K

    std::mutex protection_mutex;                                                     //!< Mutex for data

public:     // methods

    //*****************************************************************************************************
    // Default constructor
    //*****************************************************************************************************
    Model() = default;

    //*****************************************************************************************************
    // Default destructor
    //*****************************************************************************************************
    ~Model() = default;

    //*****************************************************************************************************
    // GetParticles() - get vector with particlues function
    //*****************************************************************************************************
    // @return vector with particles
    //*****************************************************************************************************
    auto GetParticles()
    {
        std::lock_guard<std::mutex> lock(protection_mutex);

        return m_particles;
    };

    //*****************************************************************************************************
    // GetPotentialEnergySum() - get potensial energy sum and set p.e. as zero
    //*****************************************************************************************************
    // @return potension energy sum
    //*****************************************************************************************************
    auto GetPotentialEnergySum()
    {
        double pe        = m_pESum;
               m_pESum   = 0;

        return pe;
    };

    //*****************************************************************************************************
    // GetKineticEnergySum() - get kinetic energy sum and set p.e. as zero
    //*****************************************************************************************************
    // @return potension energy sum
    //*****************************************************************************************************
    auto GetKineticEnergySum()
    {
        double ke        = m_kESum;
               m_kESum   = 0;

        return ke;
    };


    //*****************************************************************************************************
    // GetParticlesPositions() - get tuple with vectors of particlues positions function
    //*****************************************************************************************************
    // @return tuple with vectors of particles positions
    //*****************************************************************************************************
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
    };

    //*****************************************************************************************************
    // GetEquilibriumDistance() - get equilibrium distanse between particles function
    //*****************************************************************************************************
    // @return equilibrium distance
    //*****************************************************************************************************
    auto GetEquilibriumDistance()
    {
        return m_equilibrium_distance;
    };

    //*****************************************************************************************************
    // grid2d() - function which makes two dimensional grid
    //*****************************************************************************************************
    // @param [in] i index of x axis coordinate for grid
    // @param [in] j index of y axis coordinate for grid
    // @param [in] period period of grid
    // @param [in] center_x value of x coordinate for center of grid
    // @param [in] center_y value of y coordinate for center of grid
    // @return tuple with grid coordinates
    //*****************************************************************************************************
    auto grid2d(int i, int j, double period, double center_x, double center_y)
    {
        double x = center_x + i * period;
        double y = center_y + j * period;

        return std::make_tuple(x, y);
    };

    //*****************************************************************************************************
    // grid2d() - function which makes two dimensional grid
    //*****************************************************************************************************
    // @param [in] i index of x axis coordinate for grid
    // @param [in] j index of y axis coordinate for grid
    // @param [in] period period of grid
    // @param [in] center_x value of x coordinate for center of grid
    // @param [in] center_y value of y coordinate for center of grid
    // @return tuple with grid coordinates
    //*****************************************************************************************************
    template<typename InputIt>
    auto SetInitialVelocities(InputIt begin, InputIt end, double temperature)
    {
        size_t N = end - begin;

        double V = sqrt(N * m_boltzman * temperature / Particle::m_m);

        static std::random_device rd;
        std::uniform_real_distribution<> dist(0, 2 * 3.14159265358979323);

        double sumVx = 0;
        double sumVy = 0;

        for (auto i = begin; i != end; ++i)
        {
            i->m_vX = V * cos(dist(rd));
            i->m_vY = V * sin(dist(rd));

            sumVx += i->m_vX;
            sumVy += i->m_vY;
        }

        sumVx /= N;
        sumVy /= N;

        for (auto i = begin; i != end; ++i)
        {
            i->m_vX -= sumVx;
            i->m_vY -= sumVy;
        }
    }

    //*****************************************************************************************************
    // SetInitialConditions() - function which set initial conditions for particles
    //*****************************************************************************************************
    // @param [in] width number of segments along the y axis into which the grid is divided
    // @param [in] height number of segments along the x axis into which the grid is divided
    // @param [in] period period of grid
    //*****************************************************************************************************
    void SetInitialConditions(int width, int height, double period)
    {
        // height or width == 1 is problematic
        if ((width <= 1) || (height <= 1) || (period < 0))
            return;

        m_iter = 0;

        // purely centered grid is not beautiful if side is even
        // double center_x = int(m_spaceRight - m_spaceLeft) / 2;
        // double center_y = int(m_spaceTop - m_spaceBot) / 2;

        double center_x = (m_spaceRight - m_spaceLeft) / 2.;
        double center_y = (m_spaceTop - m_spaceBot) / 2.;

        m_particles.resize(width*height);
        m_particles = std::vector<Particle>(width * height);

        int leftX  = - height / 2;
        int rightX = - leftX;
        int leftY  = - width / 2;
        int rightY = - leftY;
        int size   = width * height;
        // for (int i = leftX; i <= rightX; ++i)
        // {
        //     for (int j = leftY; j <= rightY; ++j)
        //     {
        //         auto [x, y] = grid2d(i, j, period, center_x, center_y);

        //         m_particles[(i + height / 2) * height + (j + width / 2)].m_x = x;
        //         m_particles[(i + height / 2) * height + (j + width / 2)].m_y = y;
        //     }
        // }

        for (auto i = 0; i < size; ++i)
        {
            auto [x, y] = grid2d(leftX + i / width , leftY + i % width, period, center_x, center_y);
            m_particles[i].m_x = x;
            m_particles[i].m_y = y;
        }

        // temperature 1 Kelvin
        SetInitialVelocities(m_particles.begin(), m_particles.end(), m_temp);

        EvaluateTimeStep();
    }

    //*****************************************************************************************************
    // EvaluateTimeStep() - evaluate time step funtion
    //*****************************************************************************************************
    // @param [in, optional] factor value of factor of time step for adjustment
    //*****************************************************************************************************
    double EvaluateTimeStep(double factor = 0.01)
    {
        if (factor <= 0)
            factor = 0.01;

        // time_step = factor * characteristic_time_for_the_model.

        // In that case characteristic time for the model will be period
        // of particle oscillation in the quadratic approximation of Lennard-Jones potential well.
        // T = (m * a ^ 2 / D) ^ (1 / 2) ~ 2 * 10 ^ (- 12)
        m_timestep = factor * sqrt(Particle::m_m * m_equilibrium_distance * m_equilibrium_distance / m_depth);

        return m_timestep;
    };

    //*****************************************************************************************************
    // particle_interaction() - function of particle interaction
    //*****************************************************************************************************
    // @param [in] p1 link to first particle
    // @param [in] p2 link to second particle
    // @return tuple with potential, force_x for first particle, force_y for first particle
    //*****************************************************************************************************
    inline static auto particle_interaction(Particle& p1, Particle& p2)
    {
        double dx = p2.m_x - p1.m_x;
        double dy = p2.m_y - p1.m_y;

        double r2  = dx * dx + dy * dy;
        double ir6 = 1 / (r2 * r2 * r2);

        double potential = 4  * m_depth * m_sigma6 * ir6 * (m_sigma6 * ir6 - 1);
        double force1_x  = 24 * m_depth * m_sigma6 * ir6 * (- 2 * m_sigma6 * ir6 + 1) * dx / r2;
        double force1_y  = 24 * m_depth * m_sigma6 * ir6 * (- 2 * m_sigma6 * ir6 + 1) * dy / r2;

        return std::make_tuple(potential, force1_x, force1_y);
    };

    //*****************************************************************************************************
    // integrate_position() - function of Verle algorithm for position of particle
    //*****************************************************************************************************
    // @param [in] pos current value of particle position
    // @param [in] vel current value of particle velocity
    // @param [in] acc current value of particle acceleration
    // @param [in] dt value time step for modeling
    // @return new value of particle position
    //*****************************************************************************************************
    template <typename T>
    auto integrate_position(T pos, T vel, T acc, T dt)
    {
        return pos + vel * dt + acc * dt * dt / 2.0;
    };

    //*****************************************************************************************************
    // integrate_velocity() - function of Verle algorithm for velocity of particle
    //*****************************************************************************************************
    // @param [in] vel current value of particle velocity
    // @param [in] acc_prew current value of particle acceleration
    // @param [in] acc_new new value of particle acceleration
    // @param [in] dt value time step for modeling
    // @return new value of particle position
    //*****************************************************************************************************
    template <typename T>
    auto integrate_velocity(T vel, T acc_prev, T acc_new, T dt)
    {
        return vel + dt * (acc_prev + acc_new) / 2.0;
    };

    //*****************************************************************************************************
    // separation() - function that cuts off interactions between distant particles
    //*****************************************************************************************************
    // @param [in] vel current value of particle velocity
    // @param [in] acc_prew current value of particle acceleration
    // @param [in] acc_new new value of particle acceleration
    // @param [in] dt value time step for modeling
    // @return new value of particle position
    //*****************************************************************************************************
    //template<typename T>
    //bool separation(T r)
    //{
    //    if ((dx > m_spaceWidthHalf) || (dy > m_spaceWidth))
    //};

    //*****************************************************************************************************
    // velocity_verlet_process() - function of Verle algorithm
    //*****************************************************************************************************
    // @param [in] begin begin iterator for particles vector
    // @param [in] end end iterator for particles vector
    // @param [in] particle_interaction link to function of interaction between 2 particles (see particle_interaction above)
    //*****************************************************************************************************
    template <typename InputIt, typename InteractionFunc>
    auto velocity_verlet_process(InputIt begin, InputIt end,
                                 InteractionFunc particle_interaction)
    {
        // swap a_i with a_i+1
        for (auto i = begin; i != end; ++i)
        {
            i->m_aX_previous = i->m_aX;
            i->m_aX = 0.0;
            i->m_aY_previous = i->m_aY;
            i->m_aY = 0.0;
        }

        // defines lock`s scope
        {
           std::lock_guard<std::mutex> lock(protection_mutex);

           // update positions values
           for (auto i = begin; i != end; ++i)
           {
               i->m_x = integrate_position(i->m_x, i->m_vX, i->m_aX_previous, m_timestep);
               i->m_y = integrate_position(i->m_y, i->m_vY, i->m_aY_previous, m_timestep);
           }
        }

        double potential_energy = 0;    // Potential energy for all system

        // Find new accelerations
        for (auto i = begin; i != end - 1; ++i)
        {
            for (auto j = i + 1; j != end; ++j)
            {
                auto [pot, force_x1, force_y1] = particle_interaction(*i, *j);

                i->m_aX += force_x1;
                i->m_aY += force_y1;
                j->m_aX -= force_x1;
                j->m_aY -= force_y1;

                potential_energy += pot;
            }
        }

        m_pESum += potential_energy;

        for (auto i = begin; i != end; ++i)
        {
            i->m_aX /= Particle::m_m;
            i->m_aY /= Particle::m_m;
        }

        double kinetic_energy = 0;

        for (auto i = begin; i != end; ++i)
        {
            i->m_vX = integrate_velocity(i->m_vX, i->m_aX, i->m_aX_previous, m_timestep);
            i->m_vY = integrate_velocity(i->m_vY, i->m_aY, i->m_aY_previous, m_timestep);

            i->AddVelocityInSum();

            kinetic_energy += i->m_m * (i->m_vX * i->m_vX + i->m_vY * i->m_vY) / 2.;
        }

        m_kESum += kinetic_energy;
    }

    //*****************************************************************************************************
    // Process() - process some iterations of modeling function
    //*****************************************************************************************************
    // @param [in] iterations value of iterations to process
    //*****************************************************************************************************
    void Process(uint32_t iterations)
    {
        for (uint32_t i = 0; i < iterations; ++i)
            Process();

        return;
    };

    //*****************************************************************************************************
    // Process() - process one iteration of modeling function
    //*****************************************************************************************************
    void Process()
    {
        velocity_verlet_process(m_particles.begin(), m_particles.end(), particle_interaction);
        ++m_iter;

        return;
    };

    //*****************************************************************************************************
    // GetIteration() - get cur value of iteration function
    //*****************************************************************************************************
    // @return value of cur iteration
    //*****************************************************************************************************
    uint32_t GetIteration()
    {
        return m_iter;
    };

    //*****************************************************************************************************
    // GetParticlesLoss() - get cur value of particles out of modeling space
    //*****************************************************************************************************
    // @return number of lost particles
    //*****************************************************************************************************
    uint32_t GetParticlesLoss()
    {
        uint32_t numOfLoss = 0;

        for (uint32_t i = 0; i < m_particles.size(); ++i)
        {
            auto& p = m_particles.at(i);

            if ( (p.m_x < m_spaceLeft) || (p.m_x > m_spaceRight) ||
                 (p.m_y < m_spaceBot)  || (p.m_y > m_spaceTop) )
                numOfLoss++;
        }

        return numOfLoss;
    };

    //*****************************************************************************************************
    // GetParticlesAmount() - get number of particles
    //*****************************************************************************************************
    // @return number of particles
    //*****************************************************************************************************
    uint32_t GetParticlesAmount()
    {
        return m_particles.size();
    };

    //*****************************************************************************************************
    // GetMeanTemprature() - get mean temprature of system in K
    //*****************************************************************************************************
    // @return temptrature in K
    //*****************************************************************************************************
    double GetMeanTemprature()
    {
        double   vSum = 0;
        uint32_t size = m_particles.size();

        for (uint32_t i = 0; i < size; ++i)
            vSum += m_particles.at(i).GetMeanSVelocity();

        return (vSum * Particle::m_m / 2.D / (double)size / m_boltzman);
    };

    //*****************************************************************************************************
    // SetTemprature() - get initial temprature in K
    //*****************************************************************************************************
    //! @param [in] t value of init temprature in K
    //*****************************************************************************************************
    void SetTemprature(double t)
    {
        if (t >= 0)
            m_temp = t;
    };

};

#endif    // EVAPORATION_H
