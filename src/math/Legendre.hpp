#include <math.h>
#include <stdexcept>
#include <math/Utils.hpp>

#ifndef _LEGENDRE_HPP_
#define _LEGENDRE_HPP_

double  legendre(int n, double x) {
    switch(n) {
        case 0:
            return 1;
        case 1:
            return x;
        case 2:
            return 1/2. * (3*pow(x, 2) - 1);
        case 3:
            return 1/2. * (5*pow(x, 3) - 3*x);
        case 4:
            return 1/8. * (35*pow(x, 4) - 30*pow(x, 2) + 3);
        case 5:
            return 1/8. * (63*pow(x, 5) - 70*pow(x, 3) + 15*x);
        case 6:
            return 1/16. * (231*pow(x, 6) - 315*pow(x, 4) + 105*pow(x, 2) - 5);
        case 7:
            return 1/16. * (429*pow(x, 7) - 693*pow(x, 5) + 315*pow(x, 3) - 35*x);
        case 8:
            return 1/128. * (6435*pow(x, 8) - 12012*pow(x, 6) + 6930*pow(x, 4) - 1260*pow(x, 2) + 35);
        default:
            double sum = 0;
            for(int k=0; k<n; k++) {
                sum += pow(C(n, k), 2) * pow((x+1), n-k) * pow(x-1, k);
            }
            return 1/pow(2, n) * sum;
    }
}

double  legendre(int l, int m, double x) {
    if (m < 0) {
        m = abs(m);
        double k = pow(-1, m) * static_cast<double>(factorial(l-m)) / factorial(l+m);
        return k* legendre(l, m, x) ;
    }
    switch(l) {
        case 0:
            switch (m) {
                case 0:
                    return 1;            
                default:
                    throw std::invalid_argument("That associated Legendre polynomial does not exist");
                    break;
            }
        case 1:
            switch (m) {
                case 0:
                    return x; 
                case 1:
                    return -pow((1-pow(x, 2)), 1/2.);       
                default:
                    throw std::invalid_argument("That associated Legendre polynomial does not exist");
                    break;
            }
        case 2:
            switch (m) {
                case 0:
                    return 1/2. * (3*pow(x, 2) - 1); 
                case 1:
                    return -3*x * pow((1 - pow(x, 2)), 1/2.);       
                case 2:
                    return 3 * (1 - pow(x, 2));
                default:
                    throw std::invalid_argument("That associated Legendre polynomial does not exist");
                    break;
            }
        case 3:
            switch (m) {
                case 0:
                    return 1/2. * (5*pow(x, 3) - 3*x); 
                case 1:
                    return -3/2. * (5*pow(x, 2) - 1) * pow(1 - pow(x, 2), 1/2.);       
                case 2:
                    return 15*x * (1 - pow(x, 2));
                case 3:
                    return -15 * pow(1 - pow(x, 2), 3/2.);
                default:
                    throw std::invalid_argument("That associated Legendre polynomial does not exist");
                    break;
            }
        default:
            if(abs(m) > l) {
                throw std::invalid_argument("That associated Legendre polynomial does not exist");
            }
            if(abs(m) > 1) { // order (m) reduction
                m -= 1;
                return (x*(l-m)*legendre(l, m, x) - (l+m)*legendre(l-1, m, x)) / pow(1-pow(x, 2), 1/2.);
            } else { 
                l -= 1;
                return ((2*l+1)*x*legendre(l, m, x) - (l+m)*legendre(l-1, m, x)) / (l+1-m);  // degree (l) reduction
            }
    };
}


#endif //_LEGENDRE_HPP_