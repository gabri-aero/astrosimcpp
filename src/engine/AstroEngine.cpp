#include "AstroEngine.hpp"
#include <accelerations/Gravity.hpp>

AstroEngine::AstroEngine(Epoch start, Epoch end) 
    : start{start}, end{end} {
}

void AstroEngine::set_start(Epoch start) {
    this->start = start;
}

void AstroEngine::set_end(Epoch end) {
    this->end = end;
}

math::vector AstroEngine::get_X() {
    math::vector X;
    for(auto body: bodies) {
        X.push_back(body->get_sv());
    }
    return X;
}

void AstroEngine::set_integrator(std::shared_ptr<BaseIntegrator> integrator) {
    this->integrator = integrator;
    this->integrator->set_ic(0, get_X()); // start epoch taken as t=0
    this->integrator->set_dX([this](Epoch epoch, math::vector X) -> math::vector {
        return this->compute_derivatives(epoch, X);
    });
}

math::vector AstroEngine::compute_derivatives(Epoch epoch, math::vector X) {
    int n = bodies.size();
    math::vector dX(6*n); // X = [x0, y0, z0, vx0, vy0, vz0, x1, ...]
    math::vector dri(3); 
    math::vector dvi(3);// Initialize the derivatives vector of a single body (6 coordinates)

    // Update body state to input X
    for(int i=0; i<n; i++) {
        bodies.at(i)->set_sv(X.subvec(6*i, 6*(i+1)));
    }

    for(int i=0; i<n; i++) {
        std::fill(dri.begin(), dri.end(), 0);
        std::fill(dvi.begin(), dvi.end(), 0);
        // Arrange accelerations
        for(int j=0; j<n; j++) {
            if(i != j) {
                dvi += gravity(*(bodies.at(i)), *(bodies.at(j))) ; 
            }
        }
        // Arrange velocities
        dri = bodies.at(i)->get_vel();
        // Arrange final vector
        for(int k=0; k<3; k++) { 
            dX.at(6*i+k) = dri.at(k); // dr/dt
            dX.at(6*i+3+k) = dvi.at(k); //d2r/dt2
        }
    }
    return dX;
};

// TO DO: study alternative implementations to enable more control of every integration step. 
// Ex: next() function of the integrator called from a for loop within the propagator

void AstroEngine::run()  {
    this->integrator->run(end.get_secs() - start.get_secs()); // time integration from start as t=0
    // Retrieve data from integrator
    auto data = this->integrator->get_data();
    // Create necessary variables
    double t; 
    Epoch epoch; 
    math::vector states;
    const int N = bodies.size();
    std::vector<std::vector<StateVector>> trajectories(N);
    // Retrieve trajectory data
    for(int i=0; i < data.size(); i++) {
        t = data[i].first; // delta seconds from start
        epoch = start.add_secs(t);
        states = get_X();
        for(int j=0; j<N; j++) {
            trajectories.at(j).push_back(StateVector(states.subvec(6*j, 6*(j+1)), epoch));
        }
    }
    // Assign trajectory data to each body
    for(int i=0; i<N; i++) {
        bodies.at(i)->set_trajectory(trajectories.at(i));
    }
} 