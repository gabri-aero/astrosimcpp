#include "Utils.hpp"

unsigned long long factorial(int n) {
    return n <= 1 ? 1LL : n*factorial(n-1);
}

int C(int n, int k) {
    if (n<k) {
        throw std::invalid_argument( "Unexisting combinatorial number: k cannot be larger than n" );
    }
    return factorial(n) / (factorial(k) * factorial(n-k));
}

double rad2deg(double rad) {
    return rad * 180 / M_PI; 
}

double deg2rad(double deg) {
    return deg * M_PI / 180;
}