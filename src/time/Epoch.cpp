#include "Epoch.hpp"
#include <time/TimeUtils.hpp>
#include <stdexcept>

const double TT_TAI = 32.184;  // TAI_TT = TAI - TT
const double GPST_TAI = -19;  // GPST_TT = GPST - TAI
const double MJD_EPOCH = 2400000.5;  // MJD epoch expressed as JD
    
Epoch::Epoch(int year, int month, int day, int h, int m, double s, TimeScale ts, RefEpoch ref, Format fmt) 
    : Epoch(datetime_to_mjd(year, month, day, h, m, s), ts, ref, fmt) {
}

Epoch::Epoch(double daycount, TimeScale ts, RefEpoch ref, Format fmt) 
    : days{daycount}, timescale{ts}, ref_epoch{ref}, format{fmt} {
    if(ref_epoch == CUSTOM) {
        throw std::invalid_argument("To set custom reference epoch, provide reference epoch");
    }
    // Save reference epoch as mjd
    switch(ref_epoch) { // definition of reference dates from Vallado
        case MJD:
            ref_mjd = 0;
            break;
        case JD:
            ref_mjd = -MJD_EPOCH;
            break;
        case J2000:
            ref_mjd = Epoch(1980, 1, 6, 0, 0, 0, UTC, MJD).set_timescale(ts).days;
        case GPS:
            ref_mjd = Epoch(2000, 1, 1, 12, 0, 0, TT, MJD).set_timescale(ts).days;
    }
}

Epoch::Epoch(double days, TimeScale ts, Epoch epoch, Format format)
    : days{days}, timescale{ts}, format{format}, ref_epoch{CUSTOM} {
    ref_mjd = epoch.set_timescale(ts).days;
}

// Define setters
Epoch& Epoch::set_timescale(TimeScale new_timescale) {
    if (timescale == new_timescale) {
        return *this;
    } else {
        // First convert to TAI
        switch(timescale) {
            double mjd;
            case GPST:
                add_secs(-GPST_TAI);
                break;
            case TT:
                add_secs(-TT_TAI);
                break;
            case UTC:
                mjd = ref_mjd + days;
                add_secs(get_leapsec(mjd));
                break;
            case TAI: // nothing to do
                break;
        }
        // Now convert to new timescale
        switch (new_timescale) {
            double mjd;
            case GPST:
                add_secs(GPST_TAI);
                break;
            case TT:
                add_secs(TT_TAI);
                break;
            case UTC:
                mjd = ref_mjd + days;
                add_secs(-get_leapsec(mjd));
                break;
            case TAI: // nothing to do
                break;
        }
    }
    return *this;
}


Epoch& Epoch::set_reference_epoch(RefEpoch new_ref_epoch) {
    // Check that reference epoch type is adequate to function
    if(new_ref_epoch == CUSTOM) {
        throw std::invalid_argument("To set custom reference epoch, provide reference epoch");
    }
    if(new_ref_epoch != ref_epoch) {  // If reference epochs are the same, no conversion needed
        // First convert days to MJD
        days += ref_mjd;
        // Then convert days into new reference epoch and set new ref epoch (w.r.t. MJD)
        switch (new_ref_epoch) {
            case JD:
                ref_mjd = -MJD_EPOCH;
                break;
            case J2000:
                ref_mjd = Epoch(2000, 1, 1, 12, 0, 0, TT, MJD).set_timescale(timescale).days;
                break;
            case GPS:
                ref_mjd = Epoch(1980, 1, 6, 0, 0, 0, UTC, MJD).set_timescale(timescale).days;
                break;
        }
    }
    days -= ref_mjd;
    return *this;
}

Epoch& Epoch::set_reference_epoch(Epoch new_ref_epoch) {
    this->set_reference_epoch(MJD);
    this->ref_mjd = new_ref_epoch.set_reference_epoch(MJD).days;
    this->days += this->ref_mjd;
    this->ref_epoch = CUSTOM;
    return *this;
}

Epoch& Epoch::set_format(Format fmt) {
    this->format = fmt;
    return *this;
}


// Define getters
DateTime Epoch::get_calendar() const {
    double mjd = ref_mjd + days;
    return mjd_to_datetime(mjd);
};

double Epoch::get_days() const {
    return days;
}

double Epoch::get_weeks() const {
    return days/7;
}

double Epoch::get_years() const {
    return days/365.25;
}


// Define operator overloading

std::ostream& operator<<(std::ostream& os, const Epoch& epoch) {
    switch (epoch.format)
    {
    case DAY_COUNT:
        os << epoch.get_days();
        break;
    case WEEK_COUNT:
        os << epoch.get_weeks();
        break;
    case YEAR_COUNT:
        os << epoch.get_years();
        break;
    case CALENDAR:
        os << epoch.get_calendar() << " ";
        switch (epoch.timescale)
        {
        case TAI:
            os << "TAI";
            break;
        case TT:
            os << "TT";
            break;
        case UTC:
            os << "UTC";
            break;
        case GPST:
            os << "GPST";
            break;
        }
    }
    return os;
}

// Define member functions
Epoch& Epoch::add_secs(double s) {
    this->days += (s/86400);
    return *this;
}
    
Epoch& Epoch::add_days(double d) {
    this->days += d;
    return *this;
}


   