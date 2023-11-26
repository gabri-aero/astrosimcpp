#include "FrameUtils.hpp"
#include <math/Utils.hpp>

// Earth Rotation Angle
double era(const Epoch& epoch) {
    double jd = epoch.with_reference_epoch(JD).set_timescale(UTC).get_days(); // TO DO: change epoch definition to UT1
    double era = 2*M_PI * (0.7790572732640 + 1.00273781191135448 * (jd-2451545));  // TO DO: search for test cases
    return wrapTo2Pi(era);
}