#include <gtest/gtest.h>
#include <engine/AstroEngine.hpp>
#include <numerical/Euler.hpp>

TEST(AstroEngine, Test) {
    Body sun{"SUN", 1, {0, 0, 0, 0, 0, 0}};
    Body moon{"MOON", 0.1, {1, 0, 0, 0, 1, 0}};

    AstroEngine ae;
    ae.add_bodies(sun, moon);

    auto integrator = std::make_shared<Euler>(1);
    ae.set_integrator(integrator);

    ae.run(100);
    
    std::cout << "Hola" << std::endl;
}