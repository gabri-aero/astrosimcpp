#ifndef _NATURAL_BODY_HPP_
#define _NATURAL_BODY_HPP_

#include <bodies/Body.hpp>
#include <accelerations/Atmosphere.hpp>
#include <spice/Spice.hpp>

class NaturalBody : public Body {
protected:
    double luminosity = 0;
    Atmosphere* atmosphere = nullptr;

public:
    // Retrieve Body constructors
    using Body::Body;

    NaturalBody(std::string name, Epoch epoch, std::string ref_body = "SSB", std::string frame = "ECLIPJ2000");

    // Natural body setters
    void set_gravity(Gravity& gravity_model);
    void set_atmosphere(Atmosphere& atmosphere);
    void set_luminosity(double luminosity);
};


#endif // _NATURAL_BODY_HPP_