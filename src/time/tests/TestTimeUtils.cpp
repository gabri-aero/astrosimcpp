#include <gtest/gtest.h>
#include <time/TimeUtils.hpp>

TEST(TestTimeUtils, HMS_to_fraction) {
    ASSERT_NEAR(HMS_to_fraction(13, 5, 24), 0.54541666666666667, 1e-12);
}

TEST(TestTimeUtils, fraction_to_HMS) {
    HMS hms = fraction_to_HMS(0.96734953704);
    ASSERT_EQ(23, hms.h);
    ASSERT_EQ(12, hms.m);
    ASSERT_NEAR(59, hms.s, 1);
}

TEST(TestTimeUtils, YMD_to_yearday) {
    // leap year case
    YMD ymd = yearday_to_YMD(235, 2022);
    ASSERT_EQ(ymd.month, 8);
    ASSERT_EQ(ymd.day, 23);
    // not leap year case
    YMD ymd2 = yearday_to_YMD(313, 2023);
    ASSERT_EQ(ymd2.month, 11);
    ASSERT_EQ(ymd2.day, 9);
}

TEST(TestTimeUtils, yearday_to_YMD) {
    // leap year case
    ASSERT_EQ(YMD_to_yearday(2022, 8, 23), 235);
    // not leap year case
    ASSERT_EQ(YMD_to_yearday(2023, 11, 9), 313);
}


TEST(TestTimeUtils, Datetime) { // example case taken from NASA JD datetime converter
    auto dt = jd_to_datetime(2452555.17);
    ASSERT_EQ(dt.year, 2002);
    ASSERT_EQ(dt.month, 10);
    ASSERT_EQ(dt.day, 7);
    ASSERT_EQ(dt.h, 16);
    ASSERT_EQ(dt.m, 4);
    ASSERT_NEAR(dt.s, 48, 1);

    auto dt2 = jd_to_datetime(2449877.3458762);  // example from Vallado
    ASSERT_EQ(dt2.year, 1995);
    ASSERT_EQ(dt2.month, 6);
    ASSERT_EQ(dt2.day, 8);
    ASSERT_EQ(dt2.h, 20);
    ASSERT_EQ(dt2.m, 18);
    ASSERT_NEAR(dt2.s, 3.70368, 1e-4);
}

TEST(TestTimeUtils, MJDtoDatetime) {
    auto dt = mjd_to_datetime(60271.25);
    ASSERT_EQ(dt.year, 2023);
    ASSERT_EQ(dt.month, 11);
    ASSERT_EQ(dt.day, 23);
    ASSERT_EQ(dt.h, 6);
    ASSERT_EQ(dt.m, 0);
    ASSERT_NEAR(dt.s, 0, 0);
}

TEST(TestTimeUtils, DatetimeToJD) {
    auto jd = datetime_to_jd(1996, 10, 26, 14, 20, 0);
    ASSERT_NEAR(jd, 2450383.0972222222, 1e-8);
}

TEST(TestTimeUtils, LeapSeconds) {
    ASSERT_EQ(get_leapsec(50000), 29);
    ASSERT_EQ(get_leapsec(44000), 18);
    ASSERT_EQ(get_leapsec(60000), 37);
}