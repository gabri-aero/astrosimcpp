#include <vector>
#include <stdlib.h>
#include <bodies/Body.hpp>
#include <numerical/BaseIntegrator.hpp>

#ifndef _ASTRO_ENGINE_HPP_
#define _ASTRO_ENGINE_HPP_

class AstroEngine {
    std::vector<Body> bodies;
    std::shared_ptr<BaseIntegrator> integrator;
public:
    AstroEngine() = default;

    template<typename... Args> // I would like to define this in my .cpp file but it seems not to be possilbe
    void add_bodies(Args&&... args) {
        (bodies.push_back(std::forward<Args>(args)), ...);
    }
    math::vector compute_derivatives(double, math::vector);

    math::vector get_X() {
        math::vector X;
        for(auto body: bodies) {
            X.push_back(body.get_sv());
        }
        return X;
    }

    void set_integrator(std::shared_ptr<BaseIntegrator> integrator) {
        this->integrator = integrator;
        this->integrator->set_ic(0, get_X());
        this->integrator->set_dX([this](double t, math::vector X) -> math::vector {
            return this->compute_derivatives(t, X);
        });
    };

    void run(double tf) {
        this->integrator->run(tf);
    }    

    void add_bodies_py(const std::vector<Body>& body_list);
};


#endif // _ASTRO_ENGINE_HPP_