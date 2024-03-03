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