#include <gtest/gtest.h>
#include <bodies/Body.hpp>

TEST(TestBody, Utils) {
    Body sun{"SUN", 1, math::vector{1, 2, 3, 4, 5, 6}};
    Body moon{"MOON", 0.1, {0, 1, 2, 3, 4, 5}};
    
    ASSERT_EQ(sun.get_name(), "SUN");
    ASSERT_EQ(sun.get_mass(), 1);
    ASSERT_EQ(moon.get_name(), "MOON");
    ASSERT_EQ(moon.get_mass(), 0.1);
    ASSERT_EQ(moon.get_sv().at(3), 3);
    ASSERT_EQ(sun.get_sv().at(5), 6);
}