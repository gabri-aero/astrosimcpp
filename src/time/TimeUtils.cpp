#include "TimeUtils.hpp"
#include "Epoch.hpp"
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>


double HMS_to_fraction(int h, int m, double s) {
    return (h+(m+s/60)/60)/24;
}

double HMS_to_fraction(HMS hms) {
    return HMS_to_fraction(hms.h, hms.m, hms.s);
}

HMS fraction_to_HMS(double f) {
    f *= 24;
    int h = static_cast<int>(f);
    f -= h;
    f *= 60;
    int m = static_cast<int>(f);
    f -= m;
    double s = f*60;
    return HMS{h, m, s};
}

YMD yearday_to_YMD(int yearday, int year) {
    std::array<int, 12> month_days{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int y, m, d;
    d = yearday;
    if(year%4==0) {
        month_days[2] = 29;
    }
    for(m=0; d>month_days[m]; m++) {
        d -= month_days[m];
    }
    m+=1; // adjust indexing
    return YMD{y, m, d};
}

int YMD_to_yearday(int y, int m, int d) {
    std::array<int, 12> month_days{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(y%4==0) {
        month_days[2] = 29;
    }
    int yearday = 0;
    for(int i=1; i<m; i++) {
        yearday += month_days[i-1];
    }
    yearday+=d;
    return yearday;
}

int YMD_to_yearday(YMD ymd) {
    return YMD_to_yearday(ymd.year, ymd.month, ymd.day);
}

double mjd_to_jd(double mjd) {
    return mjd + 2400000.5;
}

double jd_to_mjd(double jd) {
    return jd - 2400000.5;
}

double jd_to_j2000(double jd) {
    return jd - 2451545;
}

double j2000_to_jd(double j2000) {
    return j2000 + 2451545;
}

double j2000_to_mjd(double j2000) {
    return j2000 + 51544;
}

double mjd_to_j2000(double mjd) {
    return mjd - 51544;
}

double datetime_to_mjd(int year, int month, int day, int h, int m, int s) {
    int f, g, A;
    f = m>=3 ? year : year-1;
    g = m>=3 ? month : month+12;
    A = 2-f/100+f/400;
    double mjd = static_cast<int>(365.25*f)+int(30.6001*(g+1))-679006+A+day;
    std::cout << mjd;
    mjd += HMS_to_fraction(h, m, s);    
    return mjd;
}

double datetime_to_jd(int year, int month, int day, int h, int m, int s) { 
    return mjd_to_jd(datetime_to_mjd(year, month, day, h, m, s));
}

DateTime jd_to_datetime(double jd) {
    DateTime dt;
    double jd1900 = 2415019.5;

    double T1900 = (jd - jd1900) / 365.25; // julian years since 1900
    dt.year = 1900 + static_cast<int>(T1900); // datetime year

    double leap_yrs = static_cast<int>(0.25*(dt.year-1900-1)); // leap years since 1900
    double yearday = (jd-jd1900)-((dt.year-1900)*365+leap_yrs); // day of the year
    YMD ymd = yearday_to_YMD(static_cast<int>(yearday), dt.year);
    dt.month = ymd.month;
    dt.day = ymd.day;
    
    double f = yearday - static_cast<int>(yearday); // day fraction
    HMS hms = fraction_to_HMS(f);
    dt.h = hms.h;
    dt.m = hms.m;
    dt.s = hms.s;

    return dt;
}

DateTime mjd_to_datetime(double mjd) {
    return jd_to_datetime(mjd_to_jd(mjd));
}


int get_leapsec(double mjd) {
    std::string data_dir{DATA_DIR};
    // open Leap_Second.dat file
    std::ifstream file(data_dir + "/Leap_Second.dat");
    // define variables to be used
    std::string line;
    double mjd_;
    int day, month, year, leapsec;

    // Read the file line by line using a while loop
    while (std::getline(file, line)) {
        if(line[0] != '#') {
            std::istringstream iss(line);
            iss >> mjd_;
            if(mjd_ > mjd) {
                return leapsec;
            }
            iss >> day >> month >> year >> leapsec;
        }
    }
    return leapsec;
}