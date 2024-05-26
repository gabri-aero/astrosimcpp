#include <math.h>
#include <stdexcept>
#include <math/Utils.hpp>
#include <math/Matrix.hpp>

#ifndef _LEGENDRE_HPP_
#define _LEGENDRE_HPP_

/**
 * @brief Evaulate Legendre polynomial. Source: Wikipedia.
 * 
 * @param n degree
 * @param x
*/
double legendre(int n, double x) {
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

/**
 * @brief Evaluation of associated Legendre polynomial. Source: Wikipedia.
 * 
 * @param l degree
 * @param m order
 * @param x
*/
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

class ALP {
private:
    math::matrix a;
    math::matrix b;
    int n_max;
public:
    ALP(int n_max) : n_max(n_max) {
        a = math::matrix::zeros(n_max+1, n_max+1);
        b = math::matrix::zeros(n_max+1, n_max+1);
        for(int n=0; n<=n_max; n++) {
            for(int m=0; m<=n_max; m++) {
                a[n][m] = sqrt((2*n-1)*(2*n+1)/static_cast<double>((n-m)*(n+m)));
                b[n][m] = sqrt((2*n+1)*(n+m-1)*(n-m-1)/static_cast<double>((n-m)*(n+m)*(2*n-3))) ? n-m != 1 : 0;
            }
        }

    }

    /**
     * This function computes the normalised Legendre Polynomials using recurrent
     * functions and store them in a lower triangular matrix.
     * 
     * Normalisation is the so-called geodetic normalisation (Heiskanen and Moritz, 1967)
     * 
     * This formula uses the FOID (Fixed-Order-Increasing-Degree) algorithm from Holmes and Featherstone (2002)
     * 
     * @param x evaluation point - typically co-latitude (theta)
     * @return Lower triangular matrix with degrees (n) as rows and columns as orders (m)
     */
    math::matrix compute(double theta) {
        int n, m;

        // Define cosine, sine
        double t = cos(theta);
        double u = sin(theta);

        // Pre-allocate nALPs matrix
        auto P = math::matrix::zeros(n_max+1, n_max+1);

        // Define P00 = 1
        P[0][0] = 1;

        // Define P11
        if(n_max > 0) {
            P[1][1] = sqrt(3) * u;
        }
        // Recursion for sectorial polynomials
        for(n=2; n<=n_max; n++){
            P[n][n] = sqrt((2*n+1)/(2*n)) * u * P[n-1][n-1];
        }
        
        // Recursion for terms below diagonal
        for(m=0; m<=n_max-1; m++) { // Fixed order
            // Now increase degree
            n=m+1;
            P[n][m] = a[n][m] * t * P[n-1][m];
            for(n=m+2; n<=n_max; n++) {
                P[n][m] = a[n][m] * t * P[n-1][m] - b[n][m] * P[n-2][m];
            }
        }
        
        return P;
    }
};



#endif //_LEGENDRE_HPP_