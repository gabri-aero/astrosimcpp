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
    
    SpiceDouble et;
    str2et_c("2005 DEC 31 12:00", &et);

    Epoch epoch{2005, 12, 31, 12, 0, 0, UTC};

    double dt = static_cast<double>(et) - spice::epoch_to_et(epoch);
    
    ASSERT_NEAR(0, dt, 1e-3);
}