#include "Body.hpp"

// Body constructor

Body::Body(std::string name, double mu, math::vector sv)
: name{name}, mu{mu}, sv{sv}, gravity_model(new PointMass()) {
};

Body::Body(double mu, math::vector sv)
: Body{"UNKNOWN", mu, sv} {
};

Body::Body(double mu, std::initializer_list<double> init_sv)
: Body(mu, math::vector(init_sv)) {
};

Body::Body(std::string name, double mu, std::initializer_list<double> init_sv)
: Body(name, mu, math::vector(init_sv)) {
};

// Body functions

math::vector Body::acceleration_from(const Body &other) {
    return gravity_model->gravity(*this, other);
}


// Body setters
void Body::set_name(std::string name) {
    this->name = name;
};

void Body::set_sv(math::vector sv) {
    this->sv = sv;
}


// Body getters

math::vector Body::get_pos() const {
    return {sv.at(0), sv.at(1), sv.at(2)};
}

math::vector Body::get_vel() const {
    return {sv.at(3), sv.at(4), sv.at(5)};
};

math::vector Body::get_sv() const{
    return sv;
};

double Body::get_mass() const {
    return mu/G;
}

double Body::get_mu() const {
    return mu;
};

std::string Body::get_name() const {
    return name;
};

bool Body::operator==(const Body& other) const {
    return this->name == other.name && this->mu == other.mu;
}

bool Body::operator<(const Body& other) const {
    return this->name < other.name;
}