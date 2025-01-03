#include "BodyFixed.hpp"
#include <functional>
#include <math/Rotation.hpp>
#include <math/Utils.hpp>
#include <frames/IAU2000.hpp>

math::matrix R(double alpha_0, double delta_0, double W) {
    return R3(deg2rad(W)) * R1(deg2rad(90 - delta_0)) * R3(deg2rad(90+alpha_0));
}

double epoch2d(const Epoch& epoch) {
    double d = epoch.with_reference_epoch(J2000).get_days();
    return d;
}

math::matrix sun_dcm(const Epoch& epoch) {
    double d = epoch2d(epoch);
    double alpha_0 = 286.13;
    double delta_0 = 63.87;
    double W = 84.176+14.1844000*d;
    return R(alpha_0, delta_0, W);
}

math::matrix mercury_dcm(const Epoch& epoch) {
    double d = epoch2d(epoch);
    double T = d/36525;

    double alpha_0 = 281.0103-0.0328*T;
    double delta_0 = 61.4155-0.0049*T;
    
    double M1 = 174.7910857+4.092335*d;
    double M2 = 349.5821714+8.184670*d;
    double M3 = 164.3732571+12.277005*d;
    double M4 = 339.1643429+16.369340*d;
    double M5 = 153.9554286+20.461675*d;

    double W = 329.5988+6.1385108*d 
                +0.01067257*sind(M1)
                -0.00112309*sind(M2)
                -0.00011040*sind(M3)
                -0.00002539*sind(M4)
                -0.00000571*sind(M5);

    return R(alpha_0, delta_0, W);
}

math::matrix venus_dcm(const Epoch& epoch) {
    double d = epoch2d(epoch);
    double alpha_0 = 272.76;
    double delta_0 = 67.16;
    double W = 160.20-1.4813688*d;
    return R(alpha_0, delta_0, W);
}

math::matrix mars_dcm(const Epoch& epoch) {
    double d = epoch2d(epoch);
    double T = d/36525;
    double alpha_0 = 317.269202 - 0.10927547 * T 
                    + 0.000068 * sind(198.991226 + 19139.4819985 * T)
                    + 0.000238 * sind(226.292679 + 38280.8511281 * T)
                    + 0.000052 * sind(249.663391 + 57420.7251593 * T)
                    + 0.000009 * sind(266.183510 + 76560.6367950 * T)
                    + 0.419057 * sind(79.398797 + 0.5042615 * T);

    double delta_0 = 54.432516 - 0.05827105 * T
                    + 0.000051 * cosd(122.433576 + 19139.9407476 * T)
                    + 0.000141 * cosd(43.058401 + 38280.8753272 * T)
                    + 0.000031 * cosd(57.663379 + 57420.7517205 * T)
                    + 0.000005 * cosd(79.476401 + 76560.6495004 * T)
                    + 1.591274 * cosd(166.325722 + 0.5042615 * T);

    double W = 176.049863 + 350.891982443297 * d
            + 0.000145 * sind(129.071773 + 19140.0328244 * T)
            + 0.000157 * sind(36.352167 + 38281.0473591 * T)
            + 0.000040 * sind(56.668646 + 57420.9295360 * T)
            + 0.000001 * sind(67.364003 + 76560.2552215 * T)
            + 0.000001 * sind(104.792680 + 95700.4387578 * T)
            + 0.584542 * sind(95.391654 + 0.5042615 * T);

    return R(alpha_0, delta_0, W);
}

math::matrix jupiter_dcm(const Epoch& epoch) {
    double d = epoch2d(epoch);
    double T = d/36525;

    double Ja = 99.360714 + 4850.4046 * T;
    double Jb = 175.895369 + 1191.9605 * T;
    double Jc = 300.323162 + 262.5475 * T;
    double Jd = 114.012305 + 6070.2476 * T;
    double Je = 49.511251 + 64.3000 * T;

    double alpha_0 = 268.056595 - 0.006499 * T
                 + 0.000117 * sin(Ja)
                 + 0.000938 * sin(Jb)
                 + 0.001432 * sin(Jc)
                 + 0.000030 * sin(Jd)
                 + 0.002150 * sin(Je);

    double delta_0 = 64.495303 + 0.002413 * T
                    + 0.000050 * cos(Ja)
                    + 0.000404 * cos(Jb)
                    + 0.000617 * cos(Jc)
                    - 0.000013 * cos(Jd)
                    + 0.000926 * cos(Je);

    double W = 284.95 + 870.5360000 * d;

    return R(alpha_0, delta_0, W);
}

math::matrix saturn_dcm(const Epoch& epoch) {
    double d = epoch2d(epoch);
    double T = d/36525;
    double alpha_0 = 40.589 - 0.036*T;
    double delta_0 = 83.537 - 0.004*T;
    double W = 38.90 + 810.7939024*d;
    return R(alpha_0, delta_0, W);
}

math::matrix uranus_dcm(const Epoch& epoch) {
    double d = epoch2d(epoch);
    double alpha_0 = 257.311;
    double delta_0 = -15.175;
    double W = 203.81-501.1600928*d;
    return R(alpha_0, delta_0, W);
}

math::matrix neptune_dcm(const Epoch& epoch) {
    double d = epoch2d(epoch);
    double T = d/36525;
    double N = 357.85 + 52.316 * T;
    double alpha_0 = 299.36 + 0.70 * sind(N);
    double delta_0 = 43.46 - 0.51 * cosd(N);
    double W = 249.978 + 541.1397757 * d - 0.48 * sind(N);
    return R(alpha_0, delta_0, W);
}

math::matrix deimos_dcm(const Epoch& epoch) {
    double d = epoch2d(epoch);
    double T = d/36525;
    double M1 = 190.72646643 + 15917.10818695 * T;
    double M2 = 21.46892470 + 31834.27934054 * T;
    double M3 = 332.86082793 + 19139.89694742 * T;
    double M4 = 394.93256437 + 38280.79631835 * T;
    double M5 = 189.63271560 + 41215158.18420050 * T + 12.71192322 * T * T;
    double M6 = 121.46893664 + 660.22803474 * T;
    double M7 = 231.05028581 + 660.99123540 * T;
    double M8 = 251.37314025 + 1320.50145245 * T;
    double M9 = 217.98635955 + 38279.96125550 * T;
    double M10 = 196.19729402 + 19139.83628608 * T;
    
    double alpha_0 = 316.65705808 - 0.10518014 * T
                     + 3.09217726 * sind(M6)
                     + 0.22980637 * sind(M7)
                     + 0.06418655 * sind(M8)
                     + 0.02533537 * sind(M9)
                     + 0.00778695 * sind(M10);
    
    double delta_0 = 53.50992033 - 0.05979094 * T
                     + 1.83936004 * cosd(M6)
                     + 0.14325320 * cosd(M7)
                     + 0.01911409 * cosd(M8)
                     - 0.01482590 * cosd(M9)
                     + 0.00192430 * cosd(M10);
    
    double W = 79.39932954 + 285.16188899 * d
               - 2.73954829 * sind(M6)
               - 0.39968606 * sind(M7)
               - 0.06563259 * sind(M8)
               - 0.02912940 * sind(M9)
               + 0.01699160 * sind(M10);
    
    return R(alpha_0, delta_0, W);
}

math::matrix phobos_dcm(const Epoch& epoch) {
    double d = epoch2d(epoch);
    double T = d/36525;
    double M1 = 190.72646643 + 15917.10818695 * T;
    double M2 = 21.46892470 + 31834.27934054 * T;
    double M3 = 332.86082793 + 19139.89694742 * T;
    double M4 = 394.93256437 + 38280.79631835 * T;
    double M5 = 189.63271560 + 41215158.18420050 * T + 12.71192322 * T * T;
    
    double alpha_0 = 317.67071657 - 0.10844326 * T
                     - 1.78428399 * sind(M1)
                     + 0.02212824 * sind(M2)
                     - 0.01028251 * sind(M3)
                     - 0.00475595 * sind(M4);
    
    double delta_0 = 52.88627266 - 0.06134706 * T
                     - 1.07516537 * cosd(M1)
                     + 0.00668626 * cosd(M2)
                     - 0.00648740 * cosd(M3)
                     + 0.00281576 * cosd(M4);
    
    double W = 34.9964842535 + 1128.84475928 * d + 12.72192797 * T * T
               + 1.42421769 * sind(M1)
               - 0.02273783 * sind(M2)
               + 0.00410711 * sind(M3)
               + 0.00631964 * sind(M4)
               + 1.143 * sind(M5);
    
    return R(alpha_0, delta_0, W);
}

std::unordered_map<std::string, std::function<math::matrix(const Epoch& epoch)>> dcm_map = {
    {"SUN", sun_dcm},
    {"MERCURY", mercury_dcm},
    {"VENUS", venus_dcm},
    {"EARTH", [](const Epoch& epoch) { return ITRF.get_dcm(epoch); }},
    {"MARS", mars_dcm},
    {"JUPITER", jupiter_dcm},
    {"SATURN", saturn_dcm},
    {"URANUS", uranus_dcm},
    {"NEPTUNE", neptune_dcm},
    {"PHOBOS", phobos_dcm},
    {"DEIMOS", deimos_dcm}
};

BodyFixed::BodyFixed(const Body& body) {
    this->body = std::make_shared<Body>(body);
}

math::matrix BodyFixed::get_dcm(const Epoch& epoch) const {
    return dcm_map[body->get_name()](epoch);
}