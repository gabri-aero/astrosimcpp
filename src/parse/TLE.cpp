#include "TLE.hpp"
#include "TLEParser.hpp"
#include <sstream>
#include <cmath>
#include<bodies/Body.hpp>
#include<math/Utils.hpp>
#include<orbit/OrbitUtils.hpp>

TLE::TLE(int norad_id) {
    // Create parser
    TLEParser parser;
    // Retrieve TLE data
    std::string tle_lines = parser.from_id(norad_id);
    std::string delimiter = "\r\n";
    // Split tle lines
    size_t i = 0;
    size_t pos = 0;
    while((pos = tle_lines.find(delimiter)) != std::string::npos) {
        lines[i] = tle_lines.substr(0, pos);
        tle_lines.erase(0, pos+delimiter.length());
        i++;
    }
    // Assign data of TLE line 1
    this->norad_id = std::stoi(lines[1].substr(2, 5));
    this->int_designator = lines[1].substr(9, 8);

    int year = std::stoi(lines[1].substr(18, 2));
    year = year >= 57 ? year + 1900 : year + 2000;
    double yearday = std::stod(lines[1].substr(20, 12));
    double f = yearday - static_cast<int>(yearday);
    YMD ymd = yearday_to_YMD(yearday, year);
    HMS hms = fraction_to_HMS(f);
    
    this->epoch = Epoch(ymd.year, ymd.month, ymd.day, hms.h, hms.m, hms.s, UTC);

    this->n_dot = std::stod(lines[1].substr(33, 10));
    this->n_ddot = std::stod(lines[1].substr(44, 6)) * pow(10, -5 + std::stoi(lines[1].substr(50, 2)));

    this->b_star = std::stod(lines[1].substr(53, 6)) * pow(10, -5 + std::stoi(lines[1].substr(59, 2)));

    this->set_number = std::stoi(lines[1].substr(64, 4));
    this->checksum = std::stoi(lines[1].substr(68, 1));

    // Asign data of TLE line 2
    this->i = std::stod(lines[2].substr(8, 8));
    this->raan = std::stod(lines[2].substr(17, 8));
    this->e = std::stod("." + lines[2].substr(26, 7));
    this->aop = std::stod(lines[2].substr(34, 8));
    this->M = std::stod(lines[2].substr(43, 8));
    this->n = std::stod(lines[2].substr(52, 11));
    this->n_rev = std::stoi(lines[2].substr(63, 5));
}

Orbit TLE::get_orbit(Body body) {
    // Retrieve orbital elements
    double n = this->n * 2*M_PI / 86400;
    double a = pow(body.get_mu() / pow(n, 2), 1/3.);
    double e = this->e;
    double i = deg2rad(this->i);
    double raan = deg2rad(this->raan);
    double aop = deg2rad(this->aop);
    double ta = M_to_ta(M, e);

    return Orbit(a, e, raan, i, aop, ta);
}