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

double wrapTo2Pi(double angle) {
    angle = fmod(angle, 2 * M_PI);
    return (angle < 0) ? angle + 2 * M_PI : angle;
}

math::vector cart_to_sph(math::vector cart) {
    double x = cart.at(0);
    double y = cart.at(1);
    double z = cart.at(2);

    double r = sqrt(dot(cart, cart));
    double longitude = atan2(cart[1], cart[0]);
    double latitude = asin(cart[2]/r);

    return math::vector{r, longitude, latitude};
}

math::vector sph_to_cart(math::vector sph) {
    double r = sph.at(0);
    double longitude = sph.at(1);
    double latitude = sph.at(2);

    double x = r * cos(longitude) * cos(latitude);
    double y = r * sin(longitude) * cos(latitude);
    double z = r * sin(latitude);

    return math::vector{x, y, z};
}