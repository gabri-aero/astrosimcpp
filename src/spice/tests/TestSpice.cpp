#include <gtest/gtest.h>
#include <stdio.h>
#include <spice/Spice.hpp>
#include <filesystem>
#include <time/Epoch.hpp>

TEST(Spice, Test) {
    spice::load_default();
    auto earth_radii = spice::get_radii("NAIAD");
    std::cout << earth_radii[0] << std::endl;
    std::cout << spice::get_mu("NAIAD") << std::endl;
}

TEST(Spice, UTC_TO_ET) {
    spice::load_kernel("naif0012.tls");
    
    SpiceDouble et, et2;
    str2et_c("2005 DEC 31 12:00 UTC", &et);
    str2et_c("2010 JAN 1 12:00 UTC", &et2);

    Epoch epoch{2005, 12, 31, 12, 0, 0, UTC, J2000};
    Epoch epoch2{2010, 1, 1, 12, 0, 0, UTC, J2000};

    double dt = static_cast<double>(et) - spice::epoch_to_et(epoch);
    double dt2 = static_cast<double>(et2) - spice::epoch_to_et(epoch2);
    
    ASSERT_NEAR(0, dt, 1e-3);
    ASSERT_NEAR(0, dt2, 1e-3);
}

TEST(Spice, GetState) {
    spice::load_default();

    Epoch today{2024, 3, 17, 17, 26, 0};

    auto moon_state = spice::get_state("MOON", "EARTH", today);

    std::cout << moon_state.subvec(0, 3) << std::endl;
    std::cout << moon_state.subvec(3, 6) << std::endl;
}

TEST(Spice, GetOrientation) {
    spice::load_default();

    Epoch j2000{0, TAI, J2000};
    Epoch today{2024, 3, 17, 17, 26, 0};

    auto earth_orientation_j2000 = spice::get_orientation("EARTH", j2000, "J2000");
    auto earth_orientation = spice::get_orientation("EARTH", today);

    std::cout << earth_orientation_j2000 << std::endl;
    std::cout << earth_orientation << std::endl;
}