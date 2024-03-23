#include "EphemerisBody.hpp"
#include <spice/Spice.hpp>

EphemerisBody::EphemerisBody(std::string name, std::string ref_body, std::string frame) :
    ref_body(ref_body), frame(frame), NaturalBody(0) {
    this->mu = spice::get_mu(name);
    this->name = name;
}

void EphemerisBody::set_sv(Epoch epoch) {
    sv = spice::get_state(name, ref_body, epoch, frame);
}

void EphemerisBody::set_ref_body(std::string ref_body) {
    this->ref_body = ref_body;
}
    
void EphemerisBody::set_frame(std::string frame) {
    this->frame = frame;
}