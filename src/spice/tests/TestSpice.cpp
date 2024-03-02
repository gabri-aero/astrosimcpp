#include <gtest/gtest.h>
#include <SpiceUsr.h>

TEST(Spice, Test) {
    furnsh_c("furnsh_ex5.tm");
}