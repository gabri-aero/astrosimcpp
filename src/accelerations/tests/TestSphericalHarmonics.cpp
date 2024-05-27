#include <gtest/gtest.h>
#include <accelerations/SphericalHarmonics.hpp>
#include <bodies/EphemerisBody.hpp>
#include <bodies/Spacecraft.hpp>
#include <spice/Spice.hpp>
#include <chrono>
#include <omp.h>

TEST(SHTest, FromFile) {
    auto sh = SphericalHarmonics("jggrx_0420a_sha.tab");

    ASSERT_EQ(sh.get_C().size(), 421);
    ASSERT_EQ(sh.get_C(33, 13), -0.3837464259266000E-06);
    ASSERT_EQ(sh.get_S(33, 13), -0.2881477316481000E-06);
}

double gravity_anomaly(double lon, double lat, EphemerisBody body, SphericalHarmonics& sh, PointMass& pm) {
    Spacecraft sc{"SC", {2440e3, 0, deg2rad(lon), deg2rad(90), 0, deg2rad(lat)}, body};

    body.set_gravity(pm);
    auto point_mass =  sc.acceleration_from(body);

    body.set_gravity(sh);

    double dg_free_air = norm(sc.acceleration_from(body)) - norm(point_mass);
    return dg_free_air;
}

TEST(SHTest, GravityTest) {
    spice::load_default();

    Epoch today{2024, 5, 27, 12, 0, 0};
    EphemerisBody mercury{"MERCURY"};
    PointMass pm{};
    SphericalHarmonics sh("jgmess_160a_sha.tab");
    
    int Nx = 720;
    int Ny = 360;
    math::matrix dg_free_air = math::matrix::zeros(Nx, Ny);
    math::vector longitudes;
    for(double lon=360.0/(2*Nx); lon<360; lon+=360.0/Nx) {
        longitudes.push_back(lon);
    }
    math::vector colatitudes;
    for(double lat=180.0/(2*Ny); lat<180; lat+=(180.0/Ny)) {
        colatitudes.push_back(lat);
    }

    auto tic = std::chrono::high_resolution_clock::now();
    
    std::cout << omp_get_max_threads() << std::endl;

    int i, j;
    #pragma omp parallel for num_threads(20) private(j) collapse(2)
    for(i=0; i<Nx; i++) {
        for(j=0; j<Ny; j++) {
            dg_free_air[i][j] = gravity_anomaly(longitudes[i], 90-colatitudes[j], mercury, sh, pm) * 1e5;
        }
    }
    auto toc = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>( toc - tic ).count();
    std::cout << time/1e3 << std::endl;
}