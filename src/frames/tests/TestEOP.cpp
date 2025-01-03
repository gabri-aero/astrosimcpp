#include <gtest/gtest.h>
#include <frames/EOP.hpp>

TEST(EOPTest, LoadEOP) {
    EOPData eop_data;
    Epoch epoch{2013, 1, 10, 0, 0, 0, UTC};
    EOP eop = eop_data.get(epoch);
    EOP expected{0.064418, 0.292248, 0.2677610, 0.0008859, 0.000233, 0.000185};
    ASSERT_EQ(eop.xp, expected.xp);
    ASSERT_EQ(eop.yp, expected.yp);
    ASSERT_EQ(eop.dUT1, expected.dUT1);
    ASSERT_EQ(eop.dX, expected.dX);
    ASSERT_EQ(eop.dY, expected.dY);
    ASSERT_EQ(eop.lod, expected.lod);
}