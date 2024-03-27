#include "Propagator.hpp"
#include <accelerations/Gravity.hpp>
#include <orbit/Trajectory.hpp>
#include <bodies/EphemerisBody.hpp>

Propagator::Propagator(Epoch start, Epoch end, std::string origin, std::string frame) 
    : start{start}, end{end}, origin{origin}, frame{frame} {
}

void Propagator::set_start(Epoch start) {
    this->start = start;
}

void Propagator::set_end(Epoch end) {
    this->end = end;
}

math::vector Propagator::get_X() {
    math::vector X;
    for(auto body: propagation_bodies) {
        X.push_back(body.get_sv());
    }
    return X;
}

void Propagator::set_integrator(BaseIntegrator& integrator) {
    this->integrator = &integrator;
    this->integrator->set_ic(0, get_X()); // start epoch taken as t=0
    this->integrator->set_dX([this](double t, math::vector X) -> math::vector {
        return this->compute_derivatives(t, X);
    });
}

math::vector Propagator::compute_derivatives(double t, math::vector X) {
    Epoch epoch = start.add_secs(t);
    int n = propagation_bodies.size();
    math::vector dX(6*n); // X = [x0, y0, z0, vx0, vy0, vz0, x1, ...]
    math::vector dri(3); 
    math::vector dvi(3);// Initialize the derivatives vector of a single body (6 coordinates)

    // Update body state to input X
    for(int i=0; i<n; i++) {
        propagation_bodies.at(i).set_sv(X.subvec(6*i, 6*(i+1)));
    }

    for(int i=0; i<ephemeris_bodies.size(); i++) {
        ephemeris_bodies.at(i).set_sv(epoch);
    }

    for(int i=0; i<n; i++) {
        std::fill(dri.begin(), dri.end(), 0);
        std::fill(dvi.begin(), dvi.end(), 0);
        // Arrange accelerations
        for(int j=0; j<n; j++) {
            if(i != j) {
                dvi += propagation_bodies.at(i).acceleration_from(propagation_bodies.at(j)); 
            }
        }
        for(int j=0; j<ephemeris_bodies.size(); j++) {
            dvi += propagation_bodies.at(i).acceleration_from(ephemeris_bodies.at(j));
        }
        // Arrange velocities
        dri = propagation_bodies.at(i).get_vel();
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

void Propagator::run()  {
    this->integrator->run(end.get_secs() - start.get_secs()); // time integration from start as t=0
    // Retrieve data from integrator
    auto data = this->integrator->get_data();
    // Create necessary variables
    double t; 
    std::vector<Epoch> epochs; 
    math::vector states;
    const int N = propagation_bodies.size();

    // Build time vector
    for(int i=0; i<data.size(); i++) {
        t = data[i].first; // delta seconds from start
        epochs.push_back(start.add_secs(t));
    }
    
    // Retrieve trajectory data and add to map
    for(int j=0; j<N; j++) {
        Trajectory trajectory;
        for(int i=0; i<data.size(); i++) {
            states = data[i].second;
            trajectory.emplace_back(epochs.at(i), StateVector(states.subvec(6*j, 6*(j+1))));
        }
        trajectory_map[propagation_bodies.at(j)] = trajectory;
    }

    // Create trajectory data for Ephemeris bodies
    for(int j=0; j<ephemeris_bodies.size(); j++) {
        Trajectory trajectory;
        for(int i=0; i<epochs.size(); i++) {
            ephemeris_bodies.at(j).set_sv(epochs.at(i));
            trajectory.emplace_back(epochs.at(i), StateVector(ephemeris_bodies.at(j).get_sv()));
        }
        trajectory_map[ephemeris_bodies.at(j)] = trajectory;
    }
}

Trajectory Propagator::get_trajectory(const Body& body) {
    return trajectory_map[body];
    // TO DO: add exception when no body
}




