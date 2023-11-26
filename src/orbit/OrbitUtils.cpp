#include "OrbitUtils.hpp"
#include<math.h>
#include<stdexcept>
#include<math/Utils.hpp>

double kepSolver(double M, double e, double tol) {
    if(e<1) {
        double E = e > 0.8 ? M_PI : M;
        double E_prev;
        do {
            E_prev = E; // store Ei
            E = E - (E - e*sin(E) - M) / (1 - e*cos(E)); // compute E(i+1)
        } while(fabs(E-E_prev) > tol);
        return wrapTo2Pi(E);
    } else if(e>1) {
        double F = M_PI;
        double F_prev;
        do {
            F_prev = F; // store Fi
            F = F - (e*sinh(F) - F - M) / (e*cosh(F) - 1); // compute F(i+1)
        } while(fabs(F-F_prev) > tol);
        return wrapTo2Pi(F);
    } else {
        throw std::invalid_argument("For parabollic orbits use the parameter of the parabola");
    }
}

double ta_to_M(double ta, double e) {
    if(e<1) { // Compute eccentric anomaly
        double E = 2 * atan(sqrt((1-e)/(1+e))*tan(ta/2));
        double M = E - e*sin(E);
        return wrapTo2Pi(M);
    } else if(e>1) {// Compute hyperbolic anomaly
        double F = 2 * atanh(sqrt((e-1)/(e+1))*tanh(ta/2));
        double M = e*sinh(F) - F;
        return wrapTo2Pi(M);
    } else {
        throw std::invalid_argument("For parabollic orbits use the parameter of the parabola");
    }
}

double M_to_ta(double M, double e) {
    if(e<1) { // Compute eccentric anomaly
        double E = kepSolver(M, e);
        double ta = 2*atan(sqrt((1+e)/(1-e))*tan(E/2));
        return wrapTo2Pi(ta);
    } else if(e>1) { // Compute hyperbolic anomaly
        double F = kepSolver(M, e);
        double ta = 2*atanh(sqrt((e+1)/(e-1))*tanh(F/2));
        return wrapTo2Pi(ta);
    } else {
        throw std::invalid_argument("For parabollic orbits use the parameter of the parabola");
    }
}