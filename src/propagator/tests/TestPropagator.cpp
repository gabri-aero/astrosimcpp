#include <gtest/gtest.h>
#include <propagator/Propagator.hpp>
#include <numerical/Euler.hpp>

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
    std::vector<Body*> bodies{&sun, &earth};
    ae.add_body_list(bodies); // (python-like)
    // Define integrator
    auto integrator = std::make_shared<Euler>(3600);
    ae.set_integrator(integrator); // set to propagator
    // Run propagator
    ae.run();
    // Retrieve Earth trajectory
    auto earth_trajectory = earth.get_trajectory();

    // Assert
    ASSERT_EQ(earth_trajectory.at(100).first, start.add_secs(100*3600));
    std::cout << earth_trajectory.at(100).second <<  std::endl;
}