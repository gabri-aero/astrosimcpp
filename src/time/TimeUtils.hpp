#include <iomanip>
#include <iostream>

#ifndef _TIME_UTILS_HPP_
#define _TIME_UTILS_HPP_

/**
 * @struct DateTime
 * @brief Provides calendar format support:
 * @param year
 * @param month
 * @param day
 * @param h hours
 * @param m minutes
 * @param s seconds
*/
struct DateTime {
    int year;
    int month;
    int day;
    int h;
    int m;
    double s;
    // Overlaod operator<<
    friend std::ostream& operator<<(std::ostream& os, const DateTime& dt) {
        os << std::setfill('0');
        os << std::setw(4) << dt.year << '-'
                  << std::setw(2) << dt.month << '-'
                  << std::setw(2) << dt.day << ' '
                  << std::setw(2) << dt.h << ':'
                  << std::setw(2) << dt.m << ':'
                  << std::setw(2) << dt.s;
        return os;
    }
};

/**
 * @struct YMD
 * @brief Provides year, month, day support:
 * @param year
 * @param month
 * @param day
*/
struct YMD {
    int year;
    int month;
    int day;
};

/**
 * @struct YMD
 * @brief Provides hour, minutes, seconds support:
 * @param h hours
 * @param m minutes
 * @param s seconds
*/
struct HMS {
    int h;
    int m;
    double s;
};

/**
 * @brief Conversion from hours, minutes, seconds to day fraction
 * @param h hours
 * @param m minutes
 * @param s seconds
 * @return day fraction
*/
double HMS_to_fraction(int h, int m, double s);

/**
 * @brief Conversion from hours, minutes, seconds to day fraction
 * @param hms HMS struct containing hours, minutes and seconds
 * @return day fraction
*/
double HMS_to_fraction(HMS hms);

/**
 * @brief Conversion from day fraction to hours, minutes and seconds
 * @param f day fraction
 * @return HMS struct with hours, minutes and seconds
*/
HMS fraction_to_HMS(double f);

/**
 * @brief Conversion from year, month, day to day of the year
 * @param y year
 * @param m month
 * @param d day
 * @return day of the year
*/
int YMD_to_yearday(int y, int m, int d);

/**
 * @brief Conversion from year, month, day to day of the year
 * @param ymd YMD struct containing year, month, day
 * @return day of the year
*/
int YMD_to_yearday(YMD ymd);

/**
 * @brief Conversion from day of the year to year, month, day
 * @param yd day of the year
 * @param y year
 * @return YMD struct containing year, month, day
*/
YMD yearday_to_YMD(int yd, int y);

/**
 * @brief Modified Julian Date to Julian Date conversion
 * @param mjd
 * @return jd
*/
double mjd_to_jd(double mjd);

/**
 * @brief Julian Date to Modified Julian Date conversion
 * @param jd
 * @return mjd
*/
double jd_to_mjd(double jd);

/**
 * @brief Julian Date to J2000 conversion
 * @param jd
 * @return number of days since 2000-01-01 12:00:00
*/
double jd_to_j2000(double jd);

/**
 * @brief J2000 to Julian Date conversion
 * @param j2000 number of days since 2000-01-01 12:00:00
 * @return jd
*/
double j2000_to_jd(double j2000);

/**
 * @brief J2000 to Modified Julian Date conversion
 * @param j2000 number of days since 2000-01-01 12:00:00
 * @return mjd
*/
double j2000_to_mjd(double j2000);

/**
 * @brief Modified Julian Date to J2000 conversion
 * @param mjd
 * @return number of days since 2000-01-01 12:00:00
*/
double mjd_to_j2000(double mjd);

/**
 * @brief Conversion from Julian Date to Calendar
 * @param jd
 * @return DateTime struct with: year, month, day, hour, minute, seconds.
*/
DateTime jd_to_datetime(double);

/**
 * @brief Conversion from Modified Julian Date to Calendar
 * @param mjd
 * @return DateTime struct with: year, month, day, hour, minute, seconds.
*/
DateTime mjd_to_datetime(double);

/**
 * @brief Conversion from Calendar to Julian Date  
 * @param year
 * @param month
 * @param day
 * @param h hour
 * @param m minute
 * @param s seconds
 * @return jd
*/
double datetime_to_jd(int year, int month, int day, int h, int m, double s);

/**
 * @brief Conversion from Calendar to Modified Julian Date  
 * @param year
 * @param month
 * @param day
 * @param h hour
 * @param m minute
 * @param s seconds
 * @return mjd
*/
double datetime_to_mjd(int year, int month, int day, int h, int m, double s);

/**
 * @brief Retrieve leap second number from LeapSeconds.dat provided by IERS. 
 * Updated version can be found in https://hpiers.obspm.fr/iers/bul/bulc/Leap_Second.dat
 * 
*/
int get_leapsec(double mjd);

#endif //_TIME_UTILS_HPP