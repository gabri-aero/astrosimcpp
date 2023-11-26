#include <math/Vector.hpp>
#include <functional>

#ifndef _BASE_INTEGRATOR_HPP_
#define _BASE_INTEGRATOR_HPP_

/**
 * @class BaseIntegrator
 * @brief Parent class for different integrator algorithms
*/
class BaseIntegrator {
protected:
    double h; // step size
    double t0;
    math::vector X0; // initial state
    std::vector<std::pair<double, math::vector>> data;
public:
    // Derivatives function
    std::function<math::vector(double, math::vector)> dX;

    /**
     * @brief Constructor
     * @param step integrator stepsize. For adaptive step integrators it is set as a initial value for the step.
    */
    BaseIntegrator(double step) : h{step} {};

    /**
     * @brief Setter for the initial conditions
     * @param t0 initial time (in secs)
     * @param X0 initial conditions
    */
    void set_ic(double t0, math::vector X0) {
        this->t0 = t0;
        this->X0 = X0;
        data.emplace_back(t0, X0);
    };

    /**
     * @brief Setter for the derivative function
     * @param dX_func - derivative function, dx/dt = f(t,x)
    */
    void set_dX(std::function<math::vector(double, math::vector)> dX_func) {
        this->dX = dX_func;
    };

    /**
     * @brief Integration is performed until input end time
     * @param tf end time (in secs)
    */
    void run(double tf) {
        for(double t=t0; true; t+=h) {
            std::pair<double, math::vector> next = integrate(); // every integrator shall define its integrate method
            if(next.first > tf) { // check that not end time reached
                h = tf-data.back().first; // reduce step stize to reach exactly tend
                next = integrate();
                data.emplace_back(next.first, next.second);
                break;
            }
            data.emplace_back(next.first, next.second); // computed step is stored in data
        }
    }

    /**
     * @brief Retrieved stored data from the integration process
     * @return time-stampped solution vector
    */
    std::vector<std::pair<double, math::vector>> get_data() const {
        return data;
    }

    /**
     * @brief Virtual integration method, to be defined by every integrator class
    */
    virtual std::pair<double, math::vector> integrate() = 0;
};

#endif // _BASE_INTEGRATOR_HPP_