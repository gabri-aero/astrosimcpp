#include "NaturalBody.hpp"
#include "Body.hpp"

NaturalBody::NaturalBody(std::string name, Epoch epoch,std::string ref_body,  std::string frame)
    : Body(name, spice::get_mu(name), spice::get_state(name, ref_body, epoch, frame)) {
}

void NaturalBody::set_gravity(Gravity& gravity_model) {
    this->gravity_model = &gravity_model;
}

void NaturalBody::set_atmosphere(Atmosphere& atmosphere) {
    this->atmosphere = &atmosphere;
}

void NaturalBody::set_luminosity(double luminosity) {
    this->luminosity = luminosity;
}

math::vector Body::acceleration_from(const NaturalBody& other) {
    return other.gravity_model->gravity(*this, other) + other.get_atmosphere()->aerodynamic_acceleration(*this, other);
}