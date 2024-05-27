#include <gtest/gtest.h>
#include <accelerations/SphericalHarmonics.hpp>

TEST(SHTest, FromFile) {
    std::string rel_path{"jggrx_0420a_sha.tab"};
    auto filename = std::string{GRAVITY_DIR} + '/' + rel_path;
    auto sh = SphericalHarmonics(filename);

    ASSERT_EQ(sh.get_C().size(), 421);
    ASSERT_EQ(sh.get_C(33, 13), -0.3837464259266000E-06);
    ASSERT_EQ(sh.get_S(33, 13), -0.2881477316481000E-06);
}