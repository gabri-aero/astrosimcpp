#ifndef _ORBIT_UTILS_HPP_
#define _ORBIT_UTILS_HPP_

/**
 * @brief Solve Kepler equation M = E - e sin(E)
 * @param M mean anomaly [rad]
 * @param e eccentricity
 * @param tol tolerance
 * @return E - eccentric anomaly [rad]
*/
double kepSolver(double M, double e, double tol=1e-10);

/**
 * @brief Conversion from true anomaly to mean anomaly. 
 * @param ta true anomaly [rad]
 * @param e eccentricity
 * @return M - mean anomaly [rad]
*/
double ta_to_M(double ta, double e);

/**
 * @brief Conversion from mean anomaly to true anomaly. Solves Kepler equation internally.
 * @param M mean anomaly
 * @param e eccentricity
 * @return ta - true anomaly
*/
double M_to_ta(double M, double e);

#endif //_ORBIT_UTILS_HPP_