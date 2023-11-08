#include "AstroEngine.hpp"
#include <accelerations/Gravity.hpp>

math::vector AstroEngine::compute_derivatives(double t, math::vector X) {
    int n = bodies.size();
    math::vector dX(6*n); // X = [x0, y0, z0, vx0, vy0, vz0, x1, ...]
    math::vector dri(3); 
    math::vector dvi(3);// Initialize the derivatives vector of a single body (6 coordinates)

    // Update body state to input X
    for(int i=0; i<n; i++) {
        bodies.at(i).set_sv(X.subvec(6*i, 6*(i+1)));
    }

    for(int i=0; i<n; i++) {
        std::fill(dri.begin(), dri.end(), 0);
        std::fill(dvi.begin(), dvi.end(), 0);
        // Arrange accelerations
        for(int j=0; j<n; j++) {
            if(i != j) {
                dvi += gravity(bodies.at(i), bodies.at(j));
            }
        }
        // Arrange velocities
        dri = bodies.at(i).get_vel();
        // Arrange final vector
        for(int k=0; k<3; k++) {
            dX.at(6*i+k) = dri.at(k); // dr/dt
            dX.at(6*i+3+k) = dvi.at(k); //d2r/dt2
        }
    }
    return dX;
};