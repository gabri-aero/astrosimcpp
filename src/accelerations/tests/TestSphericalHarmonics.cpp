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

double gravity_anomaly(double lon, double lat, NaturalBody body, SphericalHarmonics& sh, PointMass& pm) {
    Spacecraft sc{"SC", {2440e3, 0, deg2rad(lon), deg2rad(90), 0, deg2rad(lat)}, body};

    body.set_gravity(pm);
    auto point_mass =  sc.acceleration_from(body);

    body.set_gravity(sh);

    double dg_free_air = norm(sc.acceleration_from(body)) - norm(point_mass);
    return dg_free_air;
}

TEST(SHTest, GravityAnomalyValueTest) {
    spice::load_default();

    Epoch today{2024, 5, 27, 12, 0, 0};
    NaturalBody mercury{spice::get_mu("MERCURY")}; // not from SPICE (simplify orientation for test)
    PointMass pm;
    SphericalHarmonics sh("jgmess_160a_sha.tab");

    math::vector test_longitudes = {0, 234, 45, 107, 330};
    math::vector test_latitudes = {0, 80, -13, 34, -67};

    // math::vector expected_anomalies = {66.8, -91.3, 31.9, -52.3, -66.6}; // from NASA SSD https://ssd.jpl.nasa.gov/tools/gravity.html#/mercury
    math::vector expected_anomalies = {67.3414, -98.8748, 28.7482, -51.6678, -60.7519}; // tested with PYSHTOOLS

    for(int i=0; i<test_longitudes.size(); i++) {
        double lon = test_longitudes[i];
        double lat = test_latitudes[i];

        auto dg_free_air = gravity_anomaly(lon, lat, mercury, sh, pm) * 1e5; // mGal

        ASSERT_NEAR(dg_free_air, expected_anomalies[i], 0.0001);
        std::cout << dg_free_air << "  :  " << dg_free_air - expected_anomalies[i] << std::endl;  // TO DO (ERROR): check discrepancies
    }

}

TEST(SHTest, GravityAnomalyTest) {
    spice::load_default();

    Epoch today{2024, 5, 27, 12, 0, 0};
    PointMass pm{};
    SphericalHarmonics sh("jgmess_160a_sha.tab");
    NaturalBody mercury{sh.get_mu()};
    
    int Nx = 360;
    int Ny = 180;
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
    
    std::cout << "Number of threads: " << omp_get_max_threads() << std::endl;

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