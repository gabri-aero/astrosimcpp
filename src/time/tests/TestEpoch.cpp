#include<gtest/gtest.h>
#include<time/Epoch.hpp>
#include<time/TimeUtils.hpp>
#include<iomanip>

TEST(TestEpoch, BackAndForthConversion) {
    // UTC to all
    Epoch utc{2006, 1, 1, 12, 0, 0, UTC, J2000};
    
    ASSERT_EQ(utc.get_days(), utc.with_reference_epoch(MJD).with_reference_epoch(J2000).get_days());
    ASSERT_EQ(utc.get_days(), utc.with_reference_epoch(GPS).with_reference_epoch(J2000).get_days());
    ASSERT_EQ(utc.get_days(), utc.with_reference_epoch(JD).with_reference_epoch(J2000).get_days());

    ASSERT_EQ(utc.get_days(), utc.with_timescale(TAI).with_timescale(UTC).get_days());
    ASSERT_EQ(utc.get_days(), utc.with_timescale(GPST).with_timescale(UTC).get_days());
    ASSERT_EQ(utc.get_days(), utc.with_timescale(TT).with_timescale(UTC).get_days());

    ASSERT_EQ(utc.with_reference_epoch(MJD), Epoch(2006, 1, 1, 12, 0, 0, UTC, MJD));
    ASSERT_EQ(utc.with_reference_epoch(GPS), Epoch(2006, 1, 1, 12, 0, 0, UTC, GPS));
    ASSERT_EQ(utc.with_reference_epoch(JD), Epoch(2006, 1, 1, 12, 0, 0, UTC, JD));

    // TAI
    Epoch tai{2006, 1, 1, 12, 0, 0, TAI, J2000};
    
    ASSERT_EQ(tai.get_days(), tai.with_reference_epoch(MJD).with_reference_epoch(J2000).get_days());
    ASSERT_EQ(tai.get_days(), tai.with_reference_epoch(GPS).with_reference_epoch(J2000).get_days());
    ASSERT_EQ(tai.get_days(), tai.with_reference_epoch(JD).with_reference_epoch(J2000).get_days());

    ASSERT_EQ(tai.get_days(), tai.with_timescale(GPST).with_timescale(TAI).get_days());
    ASSERT_EQ(tai.get_days(), tai.with_timescale(TT).with_timescale(TAI).get_days());

    ASSERT_EQ(tai.with_reference_epoch(MJD), Epoch(2006, 1, 1, 12, 0, 0, TAI, MJD));
    ASSERT_EQ(tai.with_reference_epoch(GPS), Epoch(2006, 1, 1, 12, 0, 0, TAI, GPS));
    ASSERT_EQ(tai.with_reference_epoch(JD), Epoch(2006, 1, 1, 12, 0, 0, TAI, JD));

    // TT
    Epoch tt{2006, 1, 1, 12, 0, 0, TT, J2000};
    
    ASSERT_EQ(tt.get_days(), tt.with_reference_epoch(MJD).with_reference_epoch(J2000).get_days());
    ASSERT_EQ(tt.get_days(), tt.with_reference_epoch(GPS).with_reference_epoch(J2000).get_days());
    ASSERT_EQ(tt.get_days(), tt.with_reference_epoch(JD).with_reference_epoch(J2000).get_days());

    ASSERT_EQ(tt.get_days(), tt.with_timescale(GPST).with_timescale(TT).get_days());

    ASSERT_EQ(tt.with_reference_epoch(MJD), Epoch(2006, 1, 1, 12, 0, 0, TT, MJD));
    ASSERT_EQ(tt.with_reference_epoch(GPS), Epoch(2006, 1, 1, 12, 0, 0, TT, GPS));
    ASSERT_EQ(tt.with_reference_epoch(JD), Epoch(2006, 1, 1, 12, 0, 0, TT, JD));

    // GPST
    Epoch gpst{2006, 1, 1, 12, 0, 0, GPST, J2000};
    
    ASSERT_EQ(gpst.get_days(), gpst.with_reference_epoch(MJD).with_reference_epoch(J2000).get_days());
    ASSERT_EQ(gpst.get_days(), gpst.with_reference_epoch(GPS).with_reference_epoch(J2000).get_days());
    ASSERT_EQ(gpst.get_days(), gpst.with_reference_epoch(JD).with_reference_epoch(J2000).get_days());

    ASSERT_EQ(gpst.with_reference_epoch(MJD), Epoch(2006, 1, 1, 12, 0, 0, GPST, MJD));
    ASSERT_EQ(gpst.with_reference_epoch(GPS), Epoch(2006, 1, 1, 12, 0, 0, GPST, GPS));
    ASSERT_EQ(gpst.with_reference_epoch(JD), Epoch(2006, 1, 1, 12, 0, 0, GPST, JD));
}

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
