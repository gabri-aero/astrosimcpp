#include <vector>
#include <stdlib.h>
#include <type_traits>
#include <bodies/EphemerisBody.hpp>
#include <numerical/BaseIntegrator.hpp>
#include <time/Epoch.hpp>
#include <map>


#ifndef _PROPAGATOR_HPP_
#define _PROPAGATOR_HPP_

class Propagator {
private:
    std::vector<Body> propagation_bodies;
    std::vector<EphemerisBody> ephemeris_bodies;
    BaseIntegrator* integrator;
    
    // TO DO: define origin as type Body - central body
    std::string origin;
    // TO DO: combine frame (orientation) and origin into single Frame object
    std::string frame;
    Epoch start;
    Epoch end;
    std::map<Body, Trajectory> trajectory_map;
    // private member functions - only for internal use
    math::vector compute_derivatives(double, math::vector);

    math::vector get_X();

    void add_body(EphemerisBody body) {
        body.set_frame(this->frame);
        body.set_ref_body(this->origin);
        ephemeris_bodies.push_back(body);
    }
    
    template<class T>
    void add_body(const T& body) {
        propagation_bodies.push_back(body);
    }
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
    Propagator(Epoch start, Epoch end, std::string origin = "UNDEFINED", std::string frame = "UNDEFINED");

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
        (add_body(args), ...);
    }
    /**
     * @brief Add list of bodies to the propagator (mainly implemented for Python wrapper purposes)
     * @param body_list vector of bodies to be included for propagation
    */
    void add_body_list(std::vector<Body> body_list) {
        for (const auto& body : body_list) {
            add_body(body);
        }
    }

    /**
     * @brief Integrator setter
    */
    void set_integrator(BaseIntegrator& integrator);

    /**
     * @brief Run propagation
    */
    void run();

    /**
     * @brief Retrieve propagated trajectory from input body (if run executed before)
     * @param body
    */
    Trajectory get_trajectory(const Body& body);
};


#endif // _PROPAGATOR_HPP_