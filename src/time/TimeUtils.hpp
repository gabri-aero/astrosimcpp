#include <iomanip>
#include <iostream>

#ifndef _TIME_UTILS_HPP_
#define _TIME_UTILS_HPP_

struct DateTime {
    int year;
    int month;
    int day;
    int h;
    int m;
    double s;
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

struct YMD {
    int year;
    int month;
    int day;
};

struct HMS {
    int h;
    int m;
    double s;
};

double HMS_to_fraction(int h, int m, double s);
double HMS_to_fraction(HMS);
HMS fraction_to_HMS(double f);
int YMD_to_yearday(int y, int m, int d);
int YMD_to_yearday(YMD);
YMD yearday_to_YMD(int yd, int y);
double mjd_to_jd(double);
double jd_to_mjd(double);
double jd_to_j2000(double);
double j2000_to_jd(double);
double j2000_to_mjd(double);
double mjd_to_j2000(double);
DateTime jd_to_datetime(double);
DateTime mjd_to_datetime(double);
double datetime_to_jd(int year, int month, int day, int h, int m, double s);
double datetime_to_mjd(int year, int month, int day, int h, int m, double s);

int get_leapsec(double mjd);

#endif //_TIME_UTILS_HPP