#include <vector>
#include <stdlib.h>
#include <bodies/Body.hpp>
#include <numerical/BaseIntegrator.hpp>
#include <time/Epoch.hpp>

#ifndef _PROPAGATOR_HPP_
#define _PROPAGATOR_HPP_

class Propagator {
private:
    std::vector<Body*> bodies;
    std::shared_ptr<BaseIntegrator> integrator;
    Epoch start;
    Epoch end;

    // private member functions - only for internal use
    math::vector compute_derivatives(Epoch, math::vector);

    math::vector get_X();
public:
    Propagator() = default;
    Propagator(Epoch start, Epoch end);

    void set_start(Epoch start);
    void set_end(Epoch end);

    template<typename... Args> // I would like to define this in my .cpp file but it seems not to be possilbe
    void add_bodies(Args&... args) {
        (bodies.push_back(&args), ...);
    }

    void set_integrator(std::shared_ptr<BaseIntegrator> integrator);

    void run();
};


#endif // _PROPAGATOR_HPP_