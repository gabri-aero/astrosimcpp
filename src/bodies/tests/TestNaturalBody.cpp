#include <gtest/gtest.h>
#include <bodies/NaturalBody.hpp>
#include <accelerations/gravity/Gravity.hpp>
#include <spice/Spice.hpp>

TEST(TestBody, Utils) {
    Epoch today{2024, 3, 23, 11, 43, 0};
    spice::load_default();
    NaturalBody earth{"EARTH", spice::get_mu("EARTH"), spice::get_state("EARTH", "EARTH", today, "J2000")};
    NaturalBody moon{"MOON", spice::get_mu("MOON"), spice::get_state("MOON", "EARTH", today, "J2000")};
    
    PointMass gravity;
    earth.set_gravity(gravity);

    // Expected acceleration in the Moon
    double mu = earth.get_mu();
    double r = norm(moon.get_pos());
    double expected = mu / pow(r, 2);

    double result = norm(moon.acceleration_from(earth));

    ASSERT_NEAR(result, expected, 1e-15 * result);
}