#include "FrameUtils.hpp"
#include <math/Utils.hpp>

// Earth Rotation Angle
double era(const Epoch& epoch) {
    // TO DO: change epoch definition to UT1 - result: small angle deviation within 15 as.
    double jd = epoch.with_reference_epoch(JD).set_timescale(UTC).get_days(); // get JD
    double era = 2*M_PI * (0.7790572732640 + 1.00273781191135448 * (jd-2451545));  // ERA formula from Vallado
    return wrapTo2Pi(era); 
}


math::vector sph2cart(double r, double lambda, double phi) {
    return r * math::vector{
        cos(lambda) * cos(phi),
        sin(lambda) * cos(phi),
        sin(phi)
    };
}

math::vector cart2sph(math::vector r) {
    double radius = norm(r);
    double lam = atan2(r[1], r[0]);
    double phi = atan(r[2]/sqrt(r[0]*r[0]+r[1]*r[1]));

    return math::vector{radius, lam, phi};
}