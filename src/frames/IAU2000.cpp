#include "IAU2000.hpp"
#include <frames/EOP.hpp>
#include <frames/FrameUtils.hpp>
#include <fstream>
#include <limits>

BaseITRF::BaseITRF() {
    // Load Tab5.2a.txt file
    std::string iers_dir{IERS_DIR};
    std::string tab52a_file = "tab5.2a.txt";
    std::ifstream tab52a_path(iers_dir + '/' + tab52a_file);
    
    std::string line;
    int i;
    
    // Read the file line by line using a while loop
    while (std::getline(tab52a_path, line)) {
        std::istringstream iss(line);
        iss >> i;
        i--;
        if(i >=0 && i<1600) {
            iss >> Aa.at(i) 
                >> Ba.at(i);
            for(int k=0; k<14; k++) {
                iss >> a.at(i).at(k);
            }
        }
    }
    
    // Load Tab5.2b.txt file
    std::string tab52b_file = "tab5.2b.txt";
    std::ifstream tab52b_path(iers_dir + '/' + tab52b_file);
    
    // Read the file line by line using a while loop
    while (std::getline(tab52b_path, line)) {
        std::istringstream iss(line);
        iss >> i;
        i--;
        if(i >=0 && i<1275) {
            iss >> Ab.at(i) 
                >> Bb.at(i);
            for(int k=0; k<14; k++) {
                iss >> b.at(i).at(k);
            }
        }
    }
    
    // Load Tab5.2d.txt file
    std::string tab52d_file = "tab5.2d.txt";
    std::ifstream tab52d_path(iers_dir + '/' + tab52d_file);
    
    // Read the file line by line using a while loop
    while (std::getline(tab52d_path, line)) {
        std::istringstream iss(line);
        iss >> i;
        i--;
        if(i >=0 && i<66) {
            iss >> Ad.at(i) 
                >> Bd.at(i);
            for(int k=0; k<14; k++) {
                iss >> d.at(i).at(k);
            }
        }
    }
}

std::array<long double,3> BaseITRF::get_XYs(const Epoch& epoch) const {
    long double X = 0.0L, Y = 0.0L, s = 0.0L, X_poly = 0.0L, X_sum = 0.0L, 
                Y_poly = 0.0L, Y_sum = 0.0L, s_poly = 0.0L, s_sum = 0.0L;
    // Compute Julian centuries from J2000
    Epoch j2000_TT{2000, 1, 1, 12, 0, 0, TT, J2000};
    long double t = (epoch.with_reference_epoch(J2000).with_timescale(TT).get_days() - j2000_TT.get_days()) / 36525;

    // Compute polynomial parts (microarcseconds)
    X_poly = -16617. + 2004191898.*t - 429782.9*pow(t,2) - 198618.34*pow(t,3) + 7.578*pow(t,4) + 5.9285*pow(t,5);
    Y_poly = -6951. + 25896.*t - 22407274.7*pow(t,2) - 1900.59*pow(t,3) + 1112.526*pow(t,4) + 0.1358*pow(t,5);
    s_poly = 94.0 + 3808.65*t - 122.68*pow(t,2) - 72574.11*pow(t,3) + 27.98*pow(t,4) + 15.62*pow(t,5);

    // Compute non-polynomial parts
    // Define fundamental arguments
    std::array<long double, 14> fargs;
    fargs.at(0) = l(t);
    fargs.at(1) = lp(t);
    fargs.at(2) = F(t);
    fargs.at(3) = D(t);
    fargs.at(4) = Om(t);
    fargs.at(5) = L_Me(t);
    fargs.at(6) = L_Ve(t);
    fargs.at(7) = L_E(t);
    fargs.at(8) = L_Ma(t);
    fargs.at(9) = L_J(t);
    fargs.at(10) = L_Sa(t);
    fargs.at(11) = L_U(t);
    fargs.at(12) = L_Ne(t);
    fargs.at(13) = p_A(t);
    // Compute X series
    long double arg;
    std::array<int, 4> j_levels; int j;
    j_levels = {1306, 1559, 1595, 1599};
    j=0;
    for(int i=0; i<1600; i++) {
        if(j_levels.at(j) == i) j++;
        arg = 0;
        for(int k=0; k<14; k++) {
            arg += a.at(i).at(k)*fargs.at(k);
        }
        X_sum += (Aa.at(i)*sin(arg) + Ba.at(i)*cos(arg)) * pow(t,j);
    }
    // Compute Y series
    j_levels = {962, 1239, 1269, 1274};
    j=0;
    for(int i=0; i<1275; i++) {
        if(j_levels.at(j) == i) j++;
        arg = 0;
        for(int k=0; k<14; k++) {
            arg += b.at(i).at(k)*fargs.at(k);
        }
        Y_sum += (Ab.at(i)*sin(arg) + Bb.at(i)*cos(arg)) * pow(t,j);
    }
    // Compute s series
    j_levels = {33, 36, 61, 65};
    j=0;
    for(int i=0; i<66; i++) {
        if(j_levels.at(j) == i) j++;
        arg = 0;
        for(int k=0; k<14; k++) {
            arg += d.at(i).at(k)*fargs.at(k);
        }
        s_sum += (Ad.at(i)*sin(arg) + Bd.at(i)*cos(arg)) * pow(t,j);
    }
    // Add and convert to radians
    X = X_poly+X_sum;
    Y = Y_poly+Y_sum;
    X = as2rad(X*1e-6);
    Y = as2rad(Y*1e-6);
    s = s_poly+s_sum-rad2as(X*Y/2)*1e6;
    s = as2rad(s*1e-6);

    return {X, Y, s};
}

math::matrix BaseITRF::PN(const Epoch& epoch) const {
    // Retrieve EOP data at epoch
    auto eop = eop_data.get(epoch);
    // Retrieve X, Y, s
    auto XYs = get_XYs(epoch);
    long double X = XYs.at(0);
    long double Y = XYs.at(1);
    long double s = XYs.at(2);
    // Retrieve dX, dY due to free-core nutation
    double dX = eop.dX;
    double dY = eop.dY;
    // Apply free-core nutation (FCN) corrections
    // NOTE: errors due to floating point precision might be above FCN
    X += as2rad(dX);
    Y += as2rad(dY);
    // Build intermediate parameters
    long double E = atan2(Y, X);
    long double d = atan(sqrt((X*X+Y*Y)/(1-X*X-Y*Y)));
    // Return PN matrix
    return static_cast<math::matrix>(R3(-E)*R2(-d)*R3(E+s));
}

math::matrix BaseITRF::R(const Epoch& epoch) const {
    // Retrieve dUT1
    auto dUT1 = eop_data.get(epoch).dUT1 / 86400; // in days
    long double JD_UT1 = epoch.with_timescale(UTC).with_reference_epoch(JD).get_days() + dUT1;
    // Compute Earth Rotation Angle
    long double theta_era = 2*M_PI*(0.7790572732640+1.00273781191135448*(JD_UT1-2451545.0));
    theta_era = wrapTo2Pi(theta_era);
    // Return rotation matrix
    return static_cast<math::matrix>(R3(-theta_era));
}

math::matrix BaseITRF::W(const Epoch& epoch) const {
    // Retrieve pole position (arcsecs)
    EOP eop = eop_data.get(epoch);
    double xp = eop.xp;
    double yp = eop.yp;
    // Compute Julian centuries from J2000
    Epoch j2000_TT{2000, 1, 1, 12, 0, 0, TT, J2000};
    long double t = (epoch.with_reference_epoch(J2000).with_reference_epoch(TT).get_days() - j2000_TT.get_days()) / 36525;
    // Define mean Chandler and annual wobbles (arcsecs)
    double sp = -47e-6*t;
    // Convert to radians
    xp = as2rad(xp);
    yp = as2rad(yp);
    sp = as2rad(sp);
    // Return polar motion matrix
    return static_cast<math::matrix>(R3(-sp)*R2(xp)*R1(yp));
}

math::matrix B() {
    long double dalpha_0 = as2rad(-0.0146);
    long double eps_0 = as2rad(84381.406);
    long double xi_0 = as2rad(-0.041775*sin(eps_0));
    long double eta_0 = as2rad(-0.0068192);
    return static_cast<math::matrix>(R3(-dalpha_0)*R2(-xi_0)*R1(eta_0));
}


math::matrix BaseITRF::get_dcm(const Epoch& epoch) const {
    return static_cast<math::matrix>(PN(epoch)*R(epoch)*W(epoch));
}

math::matrix BaseCIRF::get_dcm(const Epoch& epoch) const {
    return PN(epoch);
}

math::matrix BaseTIRF::get_dcm(const Epoch& epoch) const {
    return PN(epoch)*R(epoch);
}

math::matrix BasePEF::get_dcm(const Epoch& epoch) const {
    // Compute Julian centuries from J2000
    Epoch j2000_TT{2000, 1, 1, 12, 0, 0, TT, J2000};
    long double t = (epoch.with_reference_epoch(J2000).with_timescale(TT).get_days() - j2000_TT.get_days()) / 36525;
    // Define mean Chandler and annual wobbles (arcsecs)
    double sp = -47e-6*t;
    // Convert to radians
    sp = as2rad(sp);
    // Return matrix
    return PN(epoch)*R(epoch)*R3(-sp);
}

// Define Earth intermediate frames
const BaseITRF ITRF;
const BaseCIRF CIRF;
const BaseTIRF TIRF;
const BasePEF PEF;