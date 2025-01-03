#include <gtest/gtest.h>
#include <time/Epoch.hpp>
#include <frames/BodyFixed.hpp>
#include <math/Utils.hpp>
#include <spice/Spice.hpp>
#include <cmath>
#include <vector>


TEST(BodyFixedTest, Sun) {
    spice::load_default();  
    Epoch epoch{2024, 10, 28, 0, 0, 0};
    std::vector<std::string> bodies{
        "SUN", "MERCURY", "VENUS", "EARTH", "MARS", "JUPITER", "SATURN", "URANUS", "NEPTUNE", "PHOBOS", "DEIMOS"
    };
    
    for(auto name: bodies) {
        auto body_dcm_spice = spice::get_orientation(name, epoch, "J2000");
        Body body{name, 0.0, {0.0, 0.0, 0.0, 0.0, 0.0, 0.0}};
        BodyFixed frame_bf{body};
        std::cout << name << "\n";
        std::cout << frame_bf.get_dcm(epoch) - body_dcm_spice << "\n"; // discrepancies mainly associated to IAU2018 rotation model (very high precision is not intended)
    }
}