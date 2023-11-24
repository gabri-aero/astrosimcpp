#include<gtest/gtest.h>
#include<time/Epoch.hpp>
#include<time/TimeUtils.hpp>
#include<iomanip>

TEST(TestEpoch, TimeScale) {
    // Tests compared with results from IERS Web Clock
    Epoch utc{2023, 11, 24, 23, 25, 7.447, UTC, MJD};

    double mjd = utc.get_days();
    ASSERT_EQ(static_cast<int>(mjd), 60272);
    Epoch tai = utc.with_timescale(TAI);
    Epoch tt = utc.with_timescale(TT);

    std::cout << utc << std::endl;
    std::cout << tai << std::endl;
    std::cout << tt << std::endl;
    
    auto utc_date = utc.get_calendar();
    auto tai_date = tai.get_calendar();
    auto tt_date = tt.get_calendar();

    ASSERT_EQ(utc_date.day, 24);
    ASSERT_EQ(tai_date.day, 24);
    ASSERT_EQ(tt_date.day, 24);

    ASSERT_EQ(utc_date.h, 23);
    ASSERT_EQ(utc_date.m, 25);
    ASSERT_NEAR(utc_date.s, 7.447, 1e-3);
    
    ASSERT_EQ(tai_date.h, 23);
    ASSERT_EQ(tai_date.m, 25);
    ASSERT_NEAR(tai_date.s, 44.447, 1e-3);
    
    ASSERT_EQ(tt_date.h, 23);
    ASSERT_EQ(tt_date.m, 26);
    ASSERT_NEAR(tt_date.s, 16.631, 1e-3);
}
