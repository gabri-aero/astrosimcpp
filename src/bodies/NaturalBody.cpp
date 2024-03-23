#include "NaturalBody.hpp"

void NaturalBody::set_gravity(Gravity& gravity_model) {
    this->gravity_model = &gravity_model;
}

void NaturalBody::set_atmosphere(Atmosphere& atmosphere) {
    this->atmosphere = &atmosphere;
}

void NaturalBody::set_luminosity(double luminosity) {
    this->luminosity = luminosity;
}