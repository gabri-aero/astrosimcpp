#ifndef _ORBIT_UTILS_HPP_
#define _ORBIT_UTILS_HPP_

double kepSolver(double M, double e, double tol=1e-10);
double ta_to_M(double ta, double e);
double M_to_ta(double M, double e);

#endif //_ORBIT_UTILS_HPP_