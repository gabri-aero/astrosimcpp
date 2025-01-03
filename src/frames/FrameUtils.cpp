#include "FrameUtils.hpp"
#include <math/Utils.hpp>
#include <type_traits>

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

template<>
double gmst<double>(Epoch epoch) {
    epoch.set_reference_epoch(JD).set_timescale(UTC);
    Epoch j2000_utc{2000, 1, 1, 12, 0, 0, UTC, JD};
    double T_UT1 = (epoch.get_days() - j2000_utc.get_days()) / 36525;
    double gmst_deg = wrapTo360(1/240.0 * (67310.54841 + (876600*3600.0 + 8640184.812866)*T_UT1 + 0.093104*pow(T_UT1,2) - 6.2e-6*pow(T_UT1,3)));
    return gmst_deg;
}

template<>
HMS gmst<HMS>(Epoch epoch) {
    return fraction_to_HMS(gmst(epoch) / 360.0);
}

double gmst(Epoch epoch) {
    return gmst<double>(epoch);
}

template<>
double lst<double>(Epoch epoch, double longitude_deg) {
    return wrapTo360(gmst(epoch) + longitude_deg);
}

template<>
HMS lst<HMS>(Epoch epoch, double longitude_deg) {
    return fraction_to_HMS(lst(epoch, longitude_deg) / 360.0);
}

double lst(Epoch epoch, double longitude_deg) {
    return lst<double>(epoch, longitude_deg);
}


long double l(long double t) {
    return  wrapTo2Pi(deg2rad(
        134.96340251
        +as2deg(1717915923.2178)*t
        +as2deg(31.8792)*pow(t,2)
        +as2deg(0.051635)*pow(t,3)
        -as2deg(0.00024470)*pow(t,4)
    ));
};

long double lp(long double t) {
    return  wrapTo2Pi(deg2rad(
        357.52910918
        +as2deg(129596581.0481)*t
        -as2deg(0.5532)*pow(t,2)
        +as2deg(0.000136)*pow(t,3)
        -as2deg(0.00001149)*pow(t,4)
    ));
}

long double F(long double t) {
    return  wrapTo2Pi(deg2rad(
        93.27209062
        +as2deg(1739527262.8478)*t
        -as2deg(12.7512)*pow(t,2)
        -as2deg(0.001037)*pow(t,3)
        +as2deg(0.00000417)*pow(t,4)
    ));
}

long double D(long double t) {
    return  wrapTo2Pi(deg2rad(
        297.85019547
        +as2deg(1602961601.2090)*t
        -as2deg(6.3706)*pow(t,2)
        +as2deg(0.006593)*pow(t,3)
        -as2deg(0.00003169)*pow(t,4)
    ));
}

long double Om(long double t) {
    return  wrapTo2Pi(deg2rad(
        125.04455501
        -as2deg(6962890.5431)*t
        +as2deg(7.4722)*pow(t,2)
        +as2deg(0.007702)*pow(t,3)
        -as2deg(0.00005939)*pow(t,4)
    ));
}

long double L_Me(long double t) {
    return wrapTo2Pi(4.402608842+2608.7903141574*t);
}

long double L_Ve(long double t) {
    return wrapTo2Pi(3.176146697+1021.3285546211*t);
}

long double L_E(long double t) {
    return wrapTo2Pi(1.753470314+628.3075849991*t);
}

long double L_Ma(long double t) {
    return wrapTo2Pi(6.203480913+334.0612426700*t);
}

long double L_J(long double t) {
    return wrapTo2Pi(0.599546497+52.9690962641*t);
}

long double L_Sa(long double t) {
    return wrapTo2Pi(0.874016757+21.3299104960*t);
}

long double L_U(long double t) {
    return wrapTo2Pi(5.481293872+7.4781598567*t);
}

long double L_Ne(long double t) {
    return wrapTo2Pi(5.311886287+3.8133035638*t);
}

long double p_A(long double t) {
    return wrapTo2Pi(0.02438175*t+0.00000538691*t*t);
}

