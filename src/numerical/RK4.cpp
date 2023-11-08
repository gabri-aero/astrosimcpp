#include "RK4.hpp"

std::pair<double, math::vector> RK4::integrate() {
    double t = data.back().first;
    double t_next = t+h;
    math::vector X = data.back().second;
    math::vector k1 = dX(t, X)*h;
    math::vector k2 = dX(t+h/2, X+k1/2)*h;
    math::vector k3 = dX(t+h/2, X+k2/2)*h;
    math::vector k4 = dX(t+h, X+k3)*h;
    math::vector X_next = X + (k1+2*k2+2*k3+k4)/6;
    return std::make_pair(t_next, X_next);
};