#include "Spacecraft.hpp"
#include "Body.hpp"

Spacecraft::Spacecraft(std::string name, math::vector sv) 
: Body{name, 0, sv} {
}

Spacecraft::Spacecraft(std::string name, Orbit oe,  Body central_body) {
    auto sv = oe.to_sv(central_body);
    *this = Spacecraft(name, sv);
}

Spacecraft::Spacecraft(std::string name, std::initializer_list<double> sv) 
    : Spacecraft{name, math::vector(sv)} {

}

Spacecraft::Spacecraft(std::string name, std::initializer_list<double> oe,  Body central_body) 
    : Spacecraft{name, math::vector{oe}, central_body} {

}

// Setters
void Spacecraft::set_mass(double mass) {
    this->mass = mass;
}

// Getters
double Spacecraft::get_mass() const {
    return mass;
}

math::vector Body::acceleration_from(const Spacecraft& other) {
    return math::vector{0.0, 0.0, 0.0};
}