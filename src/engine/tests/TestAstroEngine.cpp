#include <gtest/gtest.h>
#include <engine/AstroEngine.hpp>
#include <numerical/Euler.hpp>

TEST(AstroEngine, Test) {
    Body sun{"SUN", 1, {0, 0, 0, 0, 0, 0}};
    Body moon{"MOON", 0.1, {1, 0, 0, 0, 1, 0}};
    Epoch start(2024, 1, 1, 0, 0, 0);
    Epoch end(2025, 1, 1, 0, 0, 0);

    AstroEngine ae(start, end);
    ae.add_bodies(sun, moon);
    auto integrator = std::make_shared<Euler>(3600);
    ae.set_integrator(integrator);

    ae.run();

    auto moon_trajectory = moon.get_trajectory();
    std::cout << "Hola" << std::endl;
}