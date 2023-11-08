#include "Euler.hpp"

std::pair<double, math::vector> Euler::integrate() {
    double t = data.back().first;
    math::vector X = data.back().second;
    math::vector Xn = X + dX(t, X)*h;
    return std::make_pair(t+h, Xn);
};