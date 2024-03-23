#include <SpiceUsr.h>
#include <bodies/Body.hpp>
#include <math/Matrix.hpp>
#include <time/Epoch.hpp>

namespace spice {

void load_kernel(std::string rel_path) {
    std::string path = std::string{SPICE_KERNELS_DIR} + '/' + rel_path;
    furnsh_c( + path.c_str());
}

void load_default() {
    load_kernel("de440.bsp");
    load_kernel("pck00011.tpc");
    load_kernel("gm_de440.tpc");
}

std::array<double, 3> get_radii(std::string body) {
    SpiceInt n;
    SpiceDouble spice_radii[3];
    bodvrd_c(body.c_str(), "RADII", 3, &n, spice_radii);
    std::array<double, 3> radii = {spice_radii[0]*1e3, spice_radii[1]*1e3, spice_radii[2]*1e3};
    return radii;
}

double get_mu(std::string body) {
    SpiceInt n;
    SpiceDouble spice_gm;
    bodvrd_c(body.c_str(), "GM", 1, &n, &spice_gm);
    return spice_gm * 1e9;
}

double epoch_to_et(Epoch epoch) {
    return epoch.set_reference_epoch(RefEpoch::J2000).get_secs();
}

StateVector get_state(std::string body, std::string ref_body, Epoch epoch, std::string frame = "ECLIPJ2000") {

    SpiceDouble et = epoch_to_et(epoch);
    SpiceDouble state[6];
    SpiceDouble lt; // One-way light time

    spkezr_c(body.c_str(), et, frame.c_str(), "NONE", ref_body.c_str(), state, &lt);

    return math::vector{
        state[0] * 1e3,
        state[1] * 1e3,
        state[2] * 1e3,
        state[3] * 1e3,
        state[4] * 1e3,
        state[5] * 1e3,
    };
}

math::matrix get_orientation(std::string body, Epoch epoch, std::string frame = "ECLIPJ2000") {
    SpiceDouble et = epoch_to_et(epoch);
    SpiceDouble mat[3][3];

    pxform_c(frame.c_str(), ("IAU_" + body).c_str(), et, mat);

    return math::matrix{
        {mat[0][0], mat[0][1], mat[0][2]},
        {mat[1][0], mat[1][1], mat[1][2]},
        {mat[2][0], mat[2][1], mat[2][2]}
    };
}

}