#include <math/Vector.hpp>
#include <functional>

#ifndef _BASE_INTEGRATOR_HPP_
#define _BASE_INTEGRATOR_HPP_

class BaseIntegrator {
protected:
    double h; // step size
    double t0;
    math::vector X0;
    std::vector<std::pair<double, math::vector>> data;
public:
    std::function<math::vector(double, math::vector)> dX;
    BaseIntegrator(double step) : h{step} {};
    void set_ic(double t0, math::vector X0) {
        this->t0 = t0;
        this->X0 = X0;
        data.emplace_back(t0, X0);
    };
    void set_dX(std::function<math::vector(double, math::vector)> dX_func) {
        this->dX = dX_func;
    };
    void run(double tf) {
        for(double t=t0; true; t+=h) {
            std::pair<double, math::vector> next = integrate();
            if(next.first > tf) {
                h = tf-data.back().first;
                next = integrate();
                std::cout << "T: " << next.first << " X: " << next.second.at(0)  << " h: " << next.first - data.back().first << std::endl;
                data.emplace_back(next.first, next.second);
                break;
            }
            std::cout << "T: " << next.first << " X: " << next.second.at(0)  << " h: " << next.first - data.back().first << " t: " << t << std::endl;
            data.emplace_back(next.first, next.second);
        }
    }
    std::vector<std::pair<double, math::vector>> get_data() const {
        return data;
    }
    virtual std::pair<double, math::vector> integrate() = 0;
};

#endif // _BASE_INTEGRATOR_HPP_