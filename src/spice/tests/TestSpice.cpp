#include <gtest/gtest.h>
#include <stdio.h>
#include <spice/Spice.hpp>
#include <filesystem>

TEST(Spice, Test) {
    spice::load_default();
    auto earth_radii = spice::get_radii("NAIAD");
    std::cout << earth_radii[0] << std::endl;
    std::cout << spice::get_mu("NAIAD") << std::endl;
}