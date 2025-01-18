#ifndef _SPICE_HPP_
#define _SPICE_HPP_

#include <SpiceUsr.h>
#include <math/Matrix.hpp>
#include <time/Epoch.hpp>
#include <states/Cartesian.hpp>

namespace spice {

void load_kernel(std::string rel_path);

void load_default();

std::array<double, 3> get_radii(std::string body);

double get_mu(std::string body);

double epoch_to_et(Epoch epoch);

Cartesian get_state(std::string body, std::string ref_body, Epoch epoch, std::string frame = "ECLIPJ2000");

/**
 * Provides rotation matrix from input frame to body-fixed frame
*/
math::matrix get_orientation(std::string body, Epoch epoch, std::string frame = "ECLIPJ2000");

}

#endif // _SPICE_HPP_