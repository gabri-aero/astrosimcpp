#include "RK45.hpp"
#include <math/Vector.hpp>

std::pair<double, math::vector> RK45::integrate() {

    double t = data.back().first;
    double t_next = t+h;
    math::vector X = data.back().second;

    while(true) {
        // Compute coefficients
        math::vector k1 = dX(t,       X)*h;
        math::vector k2 = dX(t+2/9*h, X   +k1*2/9)*h;
        math::vector k3 = dX(t+1/3*h, X  +k1*1/12    +k2*1/4)*h;
        math::vector k4 = dX(t+3/4*h, X+k1*69/128-k2*243/128+k3*135/64)*h;
        math::vector k5 = dX(t+h,     X -k1*17/12   +k2*27/4  -k3*27/5+k4*16/15)*h;
        math::vector k6 = dX(t+5/6*h, X+k1*65/432   -k2*5/16 +k3*13/16 +k4*4/27+k5*5/144)*h;
        // Compute next iteration
        math::vector X_next = X + k1*47/450 + k3*12/25 + k4*32/225 + k5*1/30 + k6*6/25;
        // Estimate error
        math::vector TE_vec = k1*1/150 - k3*3/100 + k4*16/75 + k5*1/20 - k6*6/25;
        double TE = norm(TE_vec);
        // Set new step size
        double h_new = 0.9 * h * pow(tol/TE, 0.2);
        // Check tolerance
        if(TE <= tol) { // Accept step
            double t_next = t + h;
            h = h_new;
            return std::make_pair(t_next, X_next);
        }
        h = h_new;
    }
};