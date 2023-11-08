#include <gtest/gtest.h>
#include <numerical/RK45.hpp>

// simple function case
math::vector dX(double t, math::vector X) {
    math::vector dX(X.size());
    dX.at(0) = X.at(0);
    dX.at(1) = 0.5 * X.at(1);
    return dX;
};


TEST(RK45, Integration) {
    RK45 integrator{1, 1e-5};
    integrator.set_ic(0, {1, 2});
    integrator.set_dX(dX);
    integrator.run(1);
    double expected = 2.7182787380337867;
    double result = integrator.get_data().back().second.at(0);
    ASSERT_EQ(expected, result);
}