#ifndef _BODY_HPP_
#define _BODY_HPP_

#include <string>
#include <stdlib.h>
#include <memory>
#include <initializer_list>

#include <math/Vector.hpp>


class Body {
protected:
    std::string name;
    double mass;
    std::shared_ptr<math::vector> sv;
public:
    Body(double mass, math::vector sv);
    Body(std::string name, double mass, math::vector sv);
    // Allow list initialization as well
    Body(double mass, std::initializer_list<double> sv);
    Body(std::string name, double mass, std::initializer_list<double> sv);
    // Setters
    void set_name(std::string);
    void set_sv(math::vector);
    // Getters
    math::vector get_pos() const;
    math::vector get_vel() const;
    math::vector get_sv() const;
    double get_mass() const;
    double get_mu() const;
    std::string get_name() const;
};


# endif // _BODY_HPP