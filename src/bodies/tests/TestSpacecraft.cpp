#include<bodies/Spacecraft.hpp>
#include<bodies/EphemerisBody.hpp>
#include<math/Utils.hpp>
#include<gtest/gtest.h>

TEST(SpacecraftTest, Constructors) {
    // StateVector based Constructors
    Spacecraft sc1{"DUMMY_SC", math::vector{1, 2, 3, 4, 5, 6}};
    Spacecraft sc2{"DUMMY_SC2", {1, 2, 3, 4, 5, 6}};

    // Orbital elements based constructors
    spice::load_default();
    NaturalBody earth{"EARTH", Epoch(0), "EARTH"};
    Orbit oe{42e6, 0.1, 0, deg2rad(30), 0, 0};

    Spacecraft sc3{"DUMMY_SC3", oe, earth};
    Spacecraft sc4{"DUMMY_SC4", {42e6, 0.1, 0, deg2rad(30), 0, 0}, earth};

    // Assert SV
    auto sv1 = math::vector{1, 2, 3, 4, 5, 6};
    ASSERT_EQ(sv1, sc1.get_sv());
    ASSERT_EQ(sv1, sc2.get_sv());

    auto sv2 = oe.to_sv(earth);
    ASSERT_EQ(sv2, sc3.get_sv());
    ASSERT_EQ(sv2, sc4.get_sv());

    // Assert names
    ASSERT_EQ("DUMMY_SC", sc1.get_name());
    ASSERT_EQ("DUMMY_SC2", sc2.get_name());
    ASSERT_EQ("DUMMY_SC3", sc3.get_name());
    ASSERT_EQ("DUMMY_SC4", sc4.get_name());

    // Assert mass
    sc3.set_mass(1000);
    ASSERT_EQ(1000, sc3.get_mass());
    ASSERT_EQ(0, sc1.get_mass());

    
}