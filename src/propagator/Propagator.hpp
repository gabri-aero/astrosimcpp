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
    /**
     * @brief Default propagator constructor
    */
    Propagator() = default;

    /**
     * @brief Propagator constructor
     * @param start start Epoch
     * @param end end Epoch
    */
    Propagator(Epoch start, Epoch end);

    /**
     * @brief Propagator start epoch setter
    */
    void set_start(Epoch start);
    /**
     * @brief Propagator end epoch setter
    */
    void set_end(Epoch end);

    /**
     * @brief Add bodies to the propagator
     * @param args an arbitrary of bodies can be passed as an argument.
    */
    template<typename... Args> // I would like to define this in my .cpp file but it seems not to be possilbe
    void add_bodies(Args&... args) {
        (bodies.push_back(&args), ...);
    }
    /**
     * @brief Add list of bodies to the propagator (mainly implemented for Python wrapper purposes)
     * @param body_list vector of bodies to be included for propagation
    */
    void add_body_list(const std::vector<Body>& body_list) {
        for (const auto& body : body_list) {
            bodies.push_back(body);
        }
    }

    /**
     * @brief Integrator setter
    */
    void set_integrator(std::shared_ptr<BaseIntegrator> integrator);

    /**
     * @brief Run propagation
    */
    void run();
};


#endif // _PROPAGATOR_HPP_