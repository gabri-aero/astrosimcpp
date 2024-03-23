#include <gtest/gtest.h>
#include <bodies/EphemerisBody.hpp>
#include <accelerations/Gravity.hpp>
#include <spice/Spice.hpp>

TEST(TestEphemerisBody, Test) {
    spice::load_default();

    Epoch today{2024, 23, 3, 17, 53, 0};
    NaturalBody dummy(0);
    EphemerisBody earth("EARTH", "SUN", "ECLIPJ2000");

    earth.set_sv(today);

    ASSERT_EQ(spice::get_state("EARTH", "SUN", today), earth.get_sv());
}