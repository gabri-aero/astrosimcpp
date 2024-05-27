#include "SphericalHarmonics.hpp"
#include <bodies/Body.hpp>
#include <bodies/NaturalBody.hpp>
#include <frames/FrameUtils.hpp>
#include <parse/FileReader.hpp>

SphericalHarmonics::SphericalHarmonics(int n_max) {
    this->n_max = n_max;
    associated_legendre = ALP(n_max+1); // an extra order is required for the derivatives
    this->C = math::matrix::zeros(n_max+1, n_max+1);
    this->S = math::matrix::zeros(n_max+1, n_max+1);
    this->C[0][0] = 1; // by definition
}

SphericalHarmonics::SphericalHarmonics(std::string filename, int n_max, std::string root) {
    auto data = FileReader::read(root + '/' + filename);
    int n, m;

    // Check if there is header
    if(data[0][0] != 2) {
        this->n_max = n_max == 0 ? data[0][3] : n_max;
        *this = SphericalHarmonics(this->n_max);
        
        this->R = data[0][0] * 1e3;
        this->mu = data[0][1] * 1e9;

        data.erase(data.begin());
    }

    for(auto row: data) {
        n = row[0];
        m = row[1];
        if(n <= this->n_max && m <= this->n_max) {
            this->C[n][m] = row[2];
            this->S[n][m] = row[3];
        }
    }

}

math::vector SphericalHarmonics::gravity(const Body& i, const Body& j) {
    // Compute relative position vector
    math::vector rji = i.get_pos() - j.get_pos();

    // NEED TO CONVERT rji TO BODY j-FIXED FRAME
    auto r_vec = rji;

    // Compute spherical coordinates
    auto sph = cart2sph(rji);
    double r = sph[0];
    double lam = sph[1]; // longitude
    double phi = sph[2]; // latitude

    double theta = M_PI/2 - phi; // colatitude

    // Retrieve body j gravitational constant
    double mu_j = j.get_mu();

    // Pre-allocate variables
    long double dU_dr = 0;
    long double dU_dphi = 0;
    long double dU_dlam = 0;
    long double dU_dr_n, dU_dphi_n, dU_dlam_n;

    // Compute legendre polynomials
    auto P = this->associated_legendre.compute(theta);

    // Pre-compute some values
    auto cos_mlam = math::vector::zeros(n_max+1);
    auto sin_mlam = math::vector::zeros(n_max+1);
    for(int m=1; m<=n_max+1; m++) {
        cos_mlam[m] = cos(m*lam);
        sin_mlam[m] = sin(m*lam);
    }
    double tan_phi = tan(phi);
    double r_hat = R/r;
    double f; // attenuation factor
    int m, n;

    // Double summation
    for(n=1; n<=n_max; n++) {
        f = pow(r_hat, n);

        // Reset variables
        dU_dr_n = 0;
        dU_dlam_n = 0;
        dU_dphi_n = 0;

        // Derivative formula (without common terms)
        for(m=0; m<=n; m++) {
            dU_dr_n += P[n][m] * (C[n][m] * cos_mlam[m] + S[n][m] * sin_mlam[m]);
            dU_dphi_n += (P[n][m+1] - m * tan_phi * P[n][m]) * (C[n][m] * cos_mlam[m] + S[n][m] * sin_mlam[m]);
            dU_dlam_n += P[n][m] * (S[n][m] * cos_mlam[m] - C[n][m] * sin_mlam[m]);
        }

        dU_dr -= (n+1) * f * dU_dr_n / r;
        dU_dphi += f * dU_dphi_n;
        dU_dlam += f * dU_dlam_n;
    }

    // Unary vectors
    math::vector ux{1, 0, 0};
    math::vector uy{0, 1, 0};
    math::vector uz{0, 0, 1};

    double x2_y2 = pow(r_vec[0],2)+pow(r_vec[1],2);

    auto dr_dr_vec = r_vec / r;
    auto dphi_dr_vec = (uz - r_vec * r_vec[2] / pow(r, 2)) / sqrt(x2_y2);
    auto dlam_dr_vec = (r_vec[0] * uy - r_vec[1] * ux) / x2_y2;
    
    auto acc_body = mu_j/r * (dU_dr * dr_dr_vec + dU_dphi * dphi_dr_vec + dU_dlam * dlam_dr_vec) - mu_j * r_vec/pow(r,3);

    // NEED TO CONVERT acc TO REF FRAME
    auto acc = acc_body;
    
    return acc;
}

void SphericalHarmonics::set_coefficients(math::matrix C, math::matrix S) {
    for(int n=0; n<=n_max; n++) {
        for(int m=0; m<=n; m++) {
            this->C[n][m] = C[n][m];
            this->S[n][m] = S[n][m];
        }
    }
}  

// Coefficients getters
math::matrix SphericalHarmonics::get_C() const {
    return this->C;
}

math::matrix SphericalHarmonics::get_S() const {
    return this->S;
}

double SphericalHarmonics::get_C(int n, int m) const {
    return this->C[n][m];
}

double SphericalHarmonics::get_S(int n, int m) const {
    return this->S[n][m];
}

double SphericalHarmonics::get_mu() const {
    return this->mu;
}