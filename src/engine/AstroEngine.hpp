#include <vector>
#include <stdlib.h>
#include <bodies/Body.hpp>
#include <numerical/BaseIntegrator.hpp>
#include <time/Epoch.hpp>

#ifndef _ASTRO_ENGINE_HPP_
#define _ASTRO_ENGINE_HPP_

class AstroEngine {
private:
    std::vector<Body> bodies;
    std::shared_ptr<BaseIntegrator> integrator;
    Epoch start;
    Epoch end;

    // private member functions - only for internal use
    math::vector compute_derivatives(Epoch, math::vector);

    math::vector get_X();
public:
    AstroEngine() = default;
    AstroEngine(Epoch start, Epoch end);

    void set_start(Epoch start);
    void set_end(Epoch end);

    template<typename... Args> // I would like to define this in my .cpp file but it seems not to be possilbe
    void add_bodies(Args&&... args) {
        (bodies.push_back(std::forward<Args>(args)), ...);
    }

    void set_integrator(std::shared_ptr<BaseIntegrator> integrator);

    void run();
};


#endif // _ASTRO_ENGINE_HPP_