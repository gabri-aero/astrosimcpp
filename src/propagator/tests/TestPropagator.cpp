#include <gtest/gtest.h>
#include <propagator/Propagator.hpp>
#include <numerical/Euler.hpp>
#include <numerical/RK4.hpp>
#include <orbit/Trajectory.hpp>
#include <spice/Spice.hpp>
#include <bodies/Spacecraft.hpp>
#include <math/Utils.hpp>

TEST(PropagatorTest, Dummy) {
    // Define bodies
    Body sun{"SUN", 1, {0, 0, 0, 0, 0, 0}};
    Body earth{"EARTH", 0.1, {1, 0, 0, 0, 1, 0}};
    // Define epochs
    Epoch start(2024, 1, 1, 0, 0, 0, TAI, J2000);
    Epoch end(2025, 1, 1, 0, 0, 0, TAI, J2000);
    // Create propagator
    Propagator ae(start, end);
    // Add bodies
    std::vector<Body> bodies{sun, earth};
    ae.add_body_list(bodies); // (python-like)
    // Define integrator
    auto integrator = Euler(3600);
    ae.set_integrator(integrator); // set to propagator
    // Run propagator
    ae.run();
    // Retrieve Earth trajectory
    auto earth_trajectory = ae.get_trajectory(earth);

    // Assert
    ASSERT_EQ(earth_trajectory.at(100).first, start.add_secs(100*3600).get_days());
    std::cout << earth_trajectory.at(100).second <<  std::endl;
    // Ensure fixed step interpolation behaves correctly for Trajectory
    Trajectory interpolated_trajectory;
    interpolated_trajectory = earth_trajectory.fixed_time_series(0.5/24); // interpolated trajectory for every half an hour
}


TEST(PropagatorTest, Ephemeris) {
    // Load SPICE kernels
    spice::load_default();
    // Define epochs
    Epoch start(2024, 1, 1, 0, 0, 0);
    Epoch end(2024, 7, 1, 0, 0, 0);
    // Define bodies
    EphemerisBody sun{"SUN"};
    NaturalBody mercury{"MERCURY BARYCENTER", start};
    NaturalBody venus{"VENUS BARYCENTER", start};
    NaturalBody earth{"EARTH BARYCENTER", start};
    NaturalBody mars{"MARS BARYCENTER", start};
    NaturalBody jupiter{"JUPITER BARYCENTER", start};
    NaturalBody saturn{"SATURN BARYCENTER", start};
    NaturalBody uranus{"URANUS BARYCENTER", start};
    NaturalBody neptune{"NEPTUNE BARYCENTER", start};
    // Create propagator
    Propagator ae(start, end, "SSB", "ECLIPJ2000");
    // Add bodies
    ae.add_bodies(earth, sun, mercury, venus, mars, jupiter, saturn, uranus, neptune); // (python-like)
    // Define integrator
    auto integrator = RK4(3600);
    ae.set_integrator(integrator); // set to propagator
    // Run propagator
    ae.run();
    // Retrieve Earth trajectory
    auto earth_trajectory = ae.get_trajectory(earth);
    auto sun_trajectory = ae.get_trajectory(sun);
    // Compare earth trajectory with the one from SPICE
    auto end_sv = earth_trajectory.get(end);
    auto end_spice = spice::get_state("EMB", "SSB", end);

    std::cout << "Propagation final epoch analysis" << std::endl;
    std::cout << end_spice << std::endl;
    std::cout << end_sv << std::endl;
    
    auto d_sv = end_spice - end_sv;
    math::vector rel_error = d_sv.subvec(0,3) / norm(end_sv.subvec(0, 3));
    std::cout << rel_error * 100 << std::endl;
    /* 
    Half year Earth barycenter propagation accounting for planetary perturbations 
    with less than 0.0001 % position error 
    */
    ASSERT_TRUE(norm(rel_error) * 100 < 0.0001);
}

TEST(PropagatorTest, EarthSatellites) {
    // Load SPICE kernels
    spice::load_default();
    // Create Earth body
    EphemerisBody earth{"EARTH"};
    // Create satellite
    double n_geo = 2*M_PI / 86400;
    double a_geo = pow(earth.get_mu() / pow(n_geo, 2) , 1.0/3.0);
    double ecc = 0.2;
    Spacecraft satellite{"MY_SATELLITE", {a_geo, ecc, 0, deg2rad(30), 0, 0}, earth};
    Spacecraft satellite2{"MY_SATELLITE_2", {a_geo, ecc, 0, deg2rad(30), 0, 0}, earth};
    // Set start and end epoch
    Epoch start{2024, 27, 3, 17, 38, 0, UTC};
    Epoch end = start.add_days(1);
    // Create propagator
    Propagator propagator{start, end, "EARTH", "J2000"};
    // Add bodies to propagation
    propagator.add_bodies(earth, satellite, satellite2);
    // Setup integrator
    RK4 integrator{60};
    propagator.set_integrator(integrator);
    // Run propagation
    propagator.run();
    // Retrieve trajectory
    auto sat_trajectory = propagator.get_trajectory(satellite);

    // Assess result
    auto mid_sv = sat_trajectory.get(start.add_days(0.5));
    auto end_sv = sat_trajectory.get(end);

    ASSERT_NEAR(a_geo * (1+ecc), norm(mid_sv.subvec(0, 3)), 1);
    ASSERT_NEAR(a_geo * (1-ecc), norm(end_sv.subvec(0, 3)), 1);
}