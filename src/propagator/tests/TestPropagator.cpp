#include <gtest/gtest.h>
#include <propagator/Propagator.hpp>
#include <numerical/Euler.hpp>
#include <numerical/RK4.hpp>
#include <orbit/Trajectory.hpp>
#include <spice/Spice.hpp>

TEST(Propagator, Test) {
    // Define bodies
    Body sun{"SUN", 1, {0, 0, 0, 0, 0, 0}};
    Body earth{"EARTH", 0.1, {1, 0, 0, 0, 1, 0}};
    // Define epochs
    Epoch start(2024, 1, 1, 0, 0, 0);
    Epoch end(2025, 1, 1, 0, 0, 0);
    // Create propagator
    Propagator ae(start, end);
    // Add bodies
    std::vector<Body> bodies{sun, earth};
    ae.add_body_list(bodies); // (python-like)
    // Define integrator
    auto integrator = std::make_shared<Euler>(3600);
    ae.set_integrator(integrator); // set to propagator
    // Run propagator
    ae.run();
    // Retrieve Earth trajectory
    auto earth_trajectory = ae.get_trajectory(earth);

    // Assert
    ASSERT_EQ(earth_trajectory.at(100).first, start.add_secs(100*3600));
    std::cout << earth_trajectory.at(100).second <<  std::endl;
    // Ensure fixed step interpolation behaves correctly for Trajectory
    Trajectory interpolated_trajectory;
    interpolated_trajectory = earth_trajectory.interpolate(1800); // interpolated trajectory for every half an hour
}


TEST(Propagator, Ephemeris) {
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
    auto integrator = std::make_shared<RK4>(3600);
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