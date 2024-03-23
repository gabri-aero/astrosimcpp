#ifndef _BODY_HPP_
#define _BODY_HPP_

#include <string>
#include <stdlib.h>
#include <memory>
#include <initializer_list>
#include <orbit/Trajectory.hpp>
#include <accelerations/Gravity.hpp>

#include <math/Vector.hpp>

// Forward class
class StateVector;

/**
 * @class Body
 * @brief General purpose body class.
 * 
*/
class Body {
protected:
    std::string name;
    double mu;
    math::vector sv;
    Gravity* gravity_model;
public:
    /**
     * @brief Constructor from mass and statevector
     * @param mu - body gravitational parameter in m^3/s^2
     * @param sv - [x, y, z, vx, vy, vz] (in SI units, i.e. m and m/s)
    */
    Body(double mass, math::vector sv);
    /**
     * @brief Constructor that allows setting the body name
     * @param name
     * @param mu - body gravitational parameter in m^3/s^2
     * @param sv - [x, y, z, vx, vy, vz] (in SI units, i.e. m and m/s)
    */
    Body(std::string name, double mass, math::vector sv);
    /**
     * @brief Constructor that allows list initialization
     * @param mu - body gravitational parameter in m^3/s^2
     * @param sv - {x, y, z, vx, vy, vz} (in SI units, i.e. m and m/s)
    */
    Body(double mass, std::initializer_list<double> sv={0, 0, 0, 0, 0, 0});
    /**
     * @brief Constructor that allows list initialization and setting the body name
     * @param name  
     * @param mu - body gravitational parameter in m^3/s^2
     * @param sv - {x, y, z, vx, vy, vz} (in SI units, i.e. m and m/s)
    */
    Body(std::string name, double mass, std::initializer_list<double> sv);

    // Body functions
    /**
     * @brief Compute acceleration from other body
     * @param other - body that is exerting an acceleration to the current body
    */
    math::vector acceleration_from(const Body& other);

    // Setters
    /**
     * Name setter
     * @param name
    */
    void set_name(std::string name);
    /**
     * State vector setter
     * @param sv - {x, y, z, vx, vy, vz} (in SI units, i.e. m and m/s)
    */
    void set_sv(math::vector sv);

    // Getters
    /**
     * Position getter
     * @return [x, y, z]
     * Note that only the current position assigned to the body is returned. 
     * To get the computed positions over time see get_trajectory().
     * Be careful because when performing a simulation this position is overwritten.
    */
    math::vector get_pos() const;
    /**
     * Velocity getter
     * @return [vx, vy, vz]
     * Note that only the current velocity assigned to the body is returned. 
     * To get the computed positions over time see get_trajectory().
     * Be careful because when performing a simulation this velocity is overwritten.
    */
    math::vector get_vel() const;
    /**
     * Velocity getter
     * @return [x, y, z, vx, vy, vz]
     * Note that only the current state vector assigned to the body is returned. 
     * To get the computed positions over time see get_trajectory().
     * Be careful because when performing a simulation this velocity is overwritten.
    */
    math::vector get_sv() const;
    /**
     * Mass getter
    */
    double get_mass() const;
    /**
     * Mu getter
     * @return Gravitational parameter of the body, i.e. G*M
    */
    double get_mu() const;
    /**
     * Name getter
    */
    std::string get_name() const;

    // Operators
    /**
     * Equality operator
    */
    bool operator==(const Body& other) const;
    /**
     * Comparison operator
    */
    bool operator<(const Body& other) const;
};


# endif // _BODY_HPP