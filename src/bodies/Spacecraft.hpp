#ifndef _SPACECRAFT_HPP_
#define _SPACECRAFT_HPP_

#include <bodies/Body.hpp>
#include <states/Keplerian.hpp>

class Spacecraft : public Body {
private:
    double mass = 0; // mass variable takes over mu

public:
    Spacecraft(std::string name, math::vector sv);
    Spacecraft(std::string name, Keplerian oe,  Body central_body);
    Spacecraft(std::string name, std::initializer_list<double> sv);
    Spacecraft(std::string name, std::initializer_list<double> oe,  Body central_body);

    // Disable some Body functionality
    double get_mu() const = delete;

    // Mass setter
    void set_mass(double mass);

    // Mass getter
    double get_mass() const;
};

#endif // _SPACECRAFT_HPP_