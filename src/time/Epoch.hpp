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

    /**
     * @brief Epoch dummy constructor. It provides MJD epoch.
    */
    Epoch();

    /**
     * @brief Epoch constructor from calendar format
     * @param year
     * @param month
     * @param day
     * @param h hours
     * @param m minutes
     * @param s seconds (+ second fraction)
     * @param ts timescale: TAI, UTC, GPST, TT
     * @param ref built-in reference epoch, that is consider 0 for a day,week... count: MJD, JD, J2000, GPS
     * @param format how to represent the epoch: DAY_COUNT, WEEK_COUNT, YEAR_COUNT, CALENDAR
    */
    Epoch(int year, int month, int day, int h, int m, double s, TimeScale ts=TAI, RefEpoch ref=MJD, Format format=CALENDAR);

    /**
     * @brief Epoch constructor from day count
     * @param days day count since reference epoch
     * @param ts timescale: TAI, UTC, GPST, TT
     * @param ref built-in reference epoch, that is consider 0 for a day,week... count: MJD, JD, J2000, GPS
     * @param format how to represent the epoch: DAY_COUNT, WEEK_COUNT, YEAR_COUNT, CALENDAR
    */
    Epoch(double days, TimeScale ts=TAI, RefEpoch ref=MJD, Format format=DAY_COUNT);

    /**
     * @brief Epoch constructor from day count and custom reference Epoch
     * @param days day count since reference epoch
     * @param ts timescale: TAI, UTC, GPST, TT
     * @param ref_epoch reference epoch
     * @param format how to represent the epoch: DAY_COUNT, WEEK_COUNT, YEAR_COUNT, CALENDAR
    */
    Epoch(double days, TimeScale ts, Epoch ref_epoch, Format format=DAY_COUNT);

    // Copy constructor
    Epoch(const Epoch& other);

    // Setters  (not in place)
    /**
     * @brief Applies transformation to the input timescale
     * @param ts timescale
     * @return New epoch object with the desired timescale
    */
    Epoch with_timescale(TimeScale ts) const;

    /**
     * @brief Applies transformation to a new built-in reference epoch
     * @param ref_epoch built-in reference epoch: MJD, JD, J2000, GPS
     * @return New epoch object with the desired reference epoch
    */
    Epoch with_reference_epoch(RefEpoch ref_epoch) const;

    /**
     * @brief Applies transformation to a new custom reference epoch
     * @param epoch new reference epoch
     * @return New epoch object with the desired reference epoch
    */
    Epoch with_reference_epoch(const Epoch& epoch) const;

    /**
     * @param format new format
     * @return New epoch object with the desired format
    */
    Epoch with_format(Format format) const;

    // Setters (in place version)
    /**
     * @brief Epoch timescale setter
     * @param ts new timescale
    */
    Epoch& set_timescale(TimeScale ts);
    
    /**
     * @brief Epoch reference epoch setter from built-in epoch
     * @param ref_epoch new built-in epoch MJD, JD, J2000, GPS
    */
    Epoch& set_reference_epoch(RefEpoch ref_epoch);
    
    /**
     * @brief Epoch reference epoch setter from custom epoch
     * @param epoch new reference epoch object
    */
    Epoch& set_reference_epoch(Epoch epoch);
    
    /**
     * @brief Epoch timescale setter
     * @param ts new timescale
    */
    Epoch& set_format(Format format);

    // Getters

    /**
     * @brief Seconds getter
     * @return Number of seconds since reference epoch
    */
    double get_secs() const;
    
    /**
     * @brief Days getter
     * @return Number of days since reference epoch
    */
    double get_days() const;
    
    /**
     * @brief Weeks getter
     * @return Number of weeks since reference epoch
    */
    double get_weeks() const;
    
    /**
     * @brief Years getter
     * @return Number of years since reference epoch
    */
    double get_years() const;
    
    /**
     * @brief Calendar getter
     * @return DateTime object in the relevant time scale
    */
    DateTime get_calendar() const;

    // Operator overloading
    friend std::ostream& operator<<(std::ostream& os, const Epoch& epoch);

    // Member functions

    /**
     * @brief Modifies current epoch by a given number of seconds
     * @param s number of seconds
    */
    Epoch& add_secs(double s);
    
    /**
     * @brief Modifies current epoch by a given number of days
     * @param d number of days
    */
    Epoch& add_days(double d);

};


#endif //_EPOCH_HPP_