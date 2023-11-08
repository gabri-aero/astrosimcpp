#include <gtest/gtest.h>
#include <math/Legendre.hpp>

void test(std::array<double, 5> x_values, std::array<double, 5> expected, int l, int m) {
    for (int i = 0; i < 5; i++) {
        double x = x_values[i];
        double result = legendre(l, m, x);
        EXPECT_NEAR(result, expected[i], 1e-10);
    }
}


TEST(LegendreTest, P00) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{ 1.0, 1.0, 1.0, 1.0, 1.0 };

    test(x_values, expected, 0, 0);
}

TEST(LegendreTest, P1_1) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{0.21794494717703364, 0.4330127018922193, 0.5, 0.4330127018922193, 0.21794494717703364};

    test(x_values, expected, 1, -1);
}

TEST(LegendreTest, P10) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{ -0.9, -0.5, 0.0, 0.5, 0.9};

    test(x_values, expected, 1, 0);
}

TEST(LegendreTest, P11) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{-0.4358898943540673, -0.8660254037844386, -1.0, -0.8660254037844386, -0.4358898943540673};

    test(x_values, expected, 1, 1);
}

TEST(LegendreTest, P2_2) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{0.02374999999999999, 0.09374999999999999, 0.125, 0.09374999999999999, 0.02374999999999999};

    test(x_values, expected, 2, -2);
}

TEST(LegendreTest, P2_1) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{-0.19615045245933027, -0.21650635094610968, -0.0, 0.21650635094610968, 0.19615045245933027};

    test(x_values, expected, 2, -1);
}

TEST(LegendreTest, P20) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{0.7150000000000001, -0.125, -0.5, -0.125, 0.7149999999999999};

    test(x_values, expected, 2, 0);
}

TEST(LegendreTest, P21) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{1.1769027147559816, 1.299038105676658, 0.0, -1.299038105676658, -1.1769027147559816};

    test(x_values, expected, 2, 1);
}

TEST(LegendreTest, P22) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{0.5699999999999997, 2.2499999999999996, 3.0, 2.2499999999999996, 0.5699999999999997};

    test(x_values, expected, 2, 2);
}

TEST(LegendreTest, P3_3) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{0.001725397498484849, 0.013531646934131851, 0.020833333333333332, 0.013531646934131851, 0.001725397498484849};

    test(x_values, expected, 3, -3);
}

TEST(LegendreTest, P3_2) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{-0.02137499999999999, -0.04687499999999999, -0.0, 0.04687499999999999, 0.021374999999999988};

    test(x_values, expected, 3, -2);
}

TEST(LegendreTest, P3_1) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{0.16618302222248815, 0.02706329386826371, -0.125, 0.02706329386826371, 0.16618302222248815};

    test(x_values, expected, 3, -1);
}

TEST(LegendreTest, P30) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{-0.4725000000000001, 0.4375, 0.0, -0.4375, 0.47249999999999986};

    test(x_values, expected, 3, 0);
}

TEST(LegendreTest, P31) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{-1.9941962666698578, -0.3247595264191645, 1.5, -0.3247595264191645, -1.9941962666698578};

    test(x_values, expected, 3, 1);
}

TEST(LegendreTest, P32) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{-2.564999999999999, -5.624999999999999, -0.0, 5.624999999999999, 2.5649999999999986};

    test(x_values, expected, 3, 2);
}

TEST(LegendreTest, P33) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{-1.2422861989090912, -9.742785792574933, -15.0, -9.742785792574933, -1.2422861989090912};

    test(x_values, expected, 3, 3);
}

TEST(LegendreTest, P4_4) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{9.40104166666666e-05, 0.0014648437499999996, 0.0026041666666666665, 0.0014648437499999996, 9.40104166666666e-05};

    test(x_values, expected, 4, -4);
}

TEST(LegendreTest, P4_3) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{-0.001552857748636364, -0.006765823467065926, -0.0, 0.006765823467065926, 0.0015528577486363638};

    test(x_values, expected, 4, -3);
}

TEST(LegendreTest, P4_2) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{0.01848541666666666, 0.011718749999999998, -0.020833333333333332, 0.011718749999999998, 0.018485416666666657};

    test(x_values, expected, 4, -2);
}

TEST(LegendreTest, P4_1) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{-0.13093042701660298, 0.06765823467065928, -0.0, -0.06765823467065928, 0.13093042701660298};

    test(x_values, expected, 4, -1);
}

TEST(LegendreTest, P40) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{0.2079375, -0.2890625, 0.375, -0.2890625, 0.2079374999999999};

    test(x_values, expected, 4, 0);
}

TEST(LegendreTest, P41) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{2.6186085403320596, -1.3531646934131853, 0.0, 1.3531646934131853, -2.6186085403320596};

    test(x_values, expected, 4, 1);
}

TEST(LegendreTest, P42) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{6.654749999999998, 4.218749999999999, -7.5, 4.218749999999999, 6.654749999999996};

    test(x_values, expected, 4, 2);
}

TEST(LegendreTest, P43) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{7.826403053127274, 34.099750274012266, 0.0, -34.099750274012266, -7.826403053127273};

    test(x_values, expected, 4, 3);
}

TEST(LegendreTest, P44) {
    std::array<double, 5> x_values{ -0.9, -0.5, 0.0, 0.5, 0.9 };
    std::array<double, 5> expected{3.790499999999997, 59.062499999999986, 105.0, 59.062499999999986, 3.790499999999997};

    test(x_values, expected, 4, 4);
}