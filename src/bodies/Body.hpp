#ifndef _BODY_HPP_
#define _BODY_HPP_

#include <string>
#include <stdlib.h>
#include <memory>
#include <initializer_list>
#include <orbit/StateVector.hpp>

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
    double mass;
    std::shared_ptr<math::vector> sv;
    std::vector<StateVector> trajectory;
public:
    /**
     * @brief Constructor from mass and statevector
     * @param mass - body mass in kg
     * @param sv - [x, y, z, vx, vy, vz] (in SI units, i.e. m and m/s)
    */
    Body(double mass, math::vector sv);
    /**
     * @brief Constructor that allows setting the body name
     * @param name
     * @param mass - body mass in kg
     * @param sv - [x, y, z, vx, vy, vz] (in SI units, i.e. m and m/s)
    */
    Body(std::string name, double mass, math::vector sv);
    /**
     * @brief Constructor that allows list initialization
     * @param mass - body mass in kg
     * @param sv - {x, y, z, vx, vy, vz} (in SI units, i.e. m and m/s)
    */
    Body(double mass, std::initializer_list<double> sv={0, 0, 0, 0, 0, 0});
    /**
     * @brief Constructor that allows list initialization and setting the body name
     * @param name  
     * @param mass - body mass in kg
     * @param sv - {x, y, z, vx, vy, vz} (in SI units, i.e. m and m/s)
    */
    Body(std::string name, double mass, std::initializer_list<double> sv);

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
    /**
     * Trajectory setter. Note: it does not overwrite any previous trajectory stored.
     * @param trajectory - vector of StateVector objects - it provides time-stampped position and velocity
     * 
    */
    void set_trajectory(std::vector<StateVector> trajectory);

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
     * Trajectory getter
     * @return Trajectory data computed during a simulation.
    */
    std::vector<StateVector> get_trajectory() const;
    /**
     * Name getter
    */
    std::string get_name() const;
};


# endif // _BODY_HPP