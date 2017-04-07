#include <iostream>
#include <random>

#include "../points.hpp"
#include "../camera.hpp"
#include "../src/simulated_annealing.hpp"

double cost_function(const Observations& observations, const PinholeCameraModel& model)
{
    double err = 0.0;
    for (size_t i = 0 ; i<observations.pixels.size() ; ++i)
    {
        double d = distance(observations.pixels.at(i), model.project(observations.p3ds.at(i)));
        err += std::hypot(d, d);
    }

    return std::sqrt(err / (double)observations.pixels.size());
}

struct Energy
{
    const Observations& observations;

    double operator()(const PinholeCameraModel& p) const
    {
        return cost_function(observations, p);
    }
};

struct Generator
{
    PinholeCameraModel operator()(PinholeCameraModel const& p) const
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> distrib(0, 0.01);

        return PinholeCameraModel{
              p.focal + distrib(gen)
            , p.u0 + distrib(gen)
            , p.v0 + distrib(gen)
            , p.k + distrib(gen)
            , p.l + distrib(gen)
        };
    }
};

int main()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::normal_distribution<> distrib(0, 10.0);

    SimulatedAnnealing sim(1e3, 0.0, int(1e3));

    PinholeCameraModel reference_camera{200.0, 400.0, 400.0, 1.0, 1.0};

    //Creating observations
    Observations observations;

    for (int p=0; p<100 ; ++p)
    {
        observations.p3ds.emplace_back( double(p*distrib(g)), double(p*distrib(g)), 100.0);
    }
    // for (auto& p : observations.p3ds)
    //     std::cout << p << "\n";


    observations.pixels.resize(observations.p3ds.size());
    for (size_t i=0 ; i<observations.pixels.size() ; ++i)
        observations.pixels[i] = reference_camera.project(observations.p3ds[i]);
    // for (auto& p : observations.pixels)
    //     std::cout << p << "\n";

    // PinholeCameraModel camera_to_optimize;
    PinholeCameraModel camera_to_optimize{200.0, 400.0, 400.0, 1.0, 1.0};
    Energy energy{observations};
    Generator gen;

    std::cout << "initial state: " << camera_to_optimize << std::endl;

    sim(energy, camera_to_optimize, gen);

    std::cout << "final state: " << camera_to_optimize << std::endl;
}
