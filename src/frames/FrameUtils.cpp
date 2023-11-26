#include "FrameUtils.hpp"
#include <math/Utils.hpp>

// Earth Rotation Angle
double era(const Epoch& epoch) {
    // TO DO: change epoch definition to UT1 - result: small angle deviation within 15 as.
    double jd = epoch.with_reference_epoch(JD).set_timescale(UTC).get_days(); // get JD
    double era = 2*M_PI * (0.7790572732640 + 1.00273781191135448 * (jd-2451545));  // ERA formula from Vallado
    return wrapTo2Pi(era); 
}