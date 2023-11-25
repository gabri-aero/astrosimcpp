#include <iostream>
#include <time/TimeUtils.hpp>

#ifndef _EPOCH_HPP_
#define _EPOCH_HPP_


enum TimeScale {
    TAI,
    TT,
    UTC,
    GPST  // note the difference with GPS
};

enum RefEpoch {
    MJD,
    JD,
    J2000,
    GPS,  // GPS refers to GPS epoch
    CUSTOM
};

enum Format {
    DAY_COUNT,
    WEEK_COUNT,
    YEAR_COUNT,
    CALENDAR
};

class Epoch {
private:
    double days;  // day count from ref epoch is used internally along with TAI
    TimeScale timescale;
    RefEpoch ref_epoch;
    Format format;
    double ref_mjd; // ref epoch defined in MJD
public:
    // Constructors
    Epoch();
    Epoch(int year, int month, int day, int h, int m, double s, TimeScale ts=TAI, RefEpoch ref=MJD, Format format=CALENDAR);
    Epoch(double days, TimeScale ts=TAI, RefEpoch ref=MJD, Format format=DAY_COUNT);
    Epoch(double days, TimeScale ts, Epoch ref_epoch, Format format=DAY_COUNT);

    // Copy constructor
    Epoch(const Epoch& other);

    // Setters  (not in place)
    Epoch with_timescale(TimeScale ts) const;
    Epoch with_reference_epoch(RefEpoch ref_epoch) const;
    Epoch with_reference_epoch(const Epoch& epoch) const;
    Epoch with_format(Format format) const;

    // Setters (in place version)
    Epoch& set_timescale(TimeScale ts);
    Epoch& set_reference_epoch(RefEpoch ref_epoch);
    Epoch& set_reference_epoch(Epoch epoch);
    Epoch& set_format(Format format);

    // Getters
    double get_days() const;
    double get_weeks() const;
    double get_years() const;
    DateTime get_calendar() const;

    // Operator overloading
    friend std::ostream& operator<<(std::ostream& os, const Epoch& epoch);

    // Member functions
    Epoch& add_secs(double s);
    Epoch& add_days(double d);

};


#endif //_EPOCH_HPP_