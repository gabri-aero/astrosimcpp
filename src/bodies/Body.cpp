#include "Body.hpp"
#include <accelerations/Gravity.hpp>

// Body constructor

Body::Body(std::string name, double mass, math::vector sv)
: name{name}, mass{mass}, sv{std::make_shared<math::vector>(sv)} {
};

Body::Body(double mass, math::vector sv)
: Body{"UNKNOWN", mass, sv} {
};

Body::Body(double mass, std::initializer_list<double> init_sv)
: Body(mass, math::vector(init_sv)) {
};

Body::Body(std::string name, double mass, std::initializer_list<double> init_sv)
: Body(name, mass, math::vector(init_sv)) {
};

// Body setters
void Body::set_name(std::string name) {
    this->name = name;
};

void Body::set_sv(math::vector sv) {
    this->sv = std::make_shared<math::vector>(sv);
}


// Body getters

math::vector Body::get_pos() const {
    return {sv->at(0), sv->at(1), sv->at(2)};
}

math::vector Body::get_vel() const {
    return {sv->at(3), sv->at(4), sv->at(5)};
};

math::vector Body::get_sv() const{
    return *sv;
};

double Body::get_mass() const {
    return mass;
}

double Body::get_mu() const {
    return G*mass;
};

std::string Body::get_name() const {
    return name;
};