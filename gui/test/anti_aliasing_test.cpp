#include <gtest/gtest.h>
#include "anti_aliasing.h"

TEST(anti_aliasing, template_based_sum_test) {
    GTEST_ASSERT_EQ(333, sum(5, 2, 5, 321));
    GTEST_ASSERT_EQ(323, sum(0, 2, 0, 321));
    GTEST_ASSERT_EQ(-24, sum(-20, -20, 8, 5, 3));
    ASSERT_FLOAT_EQ(0.003f, sum(0.002f, 0.001f));
}

TEST(anti_aliasing, template_based_average_test) {
    ASSERT_FLOAT_EQ(2.0f, average<float>(2));
    ASSERT_FLOAT_EQ(83.25f, average<float>(5, 2, 5, 321));
    ASSERT_FLOAT_EQ(80.75f, average<float>(0, 2, 0, 321));
    ASSERT_FLOAT_EQ(-4.8f, average<float>(-20, -20, 8, 5, 3));
    ASSERT_DOUBLE_EQ(12.916265, average<double>(23.3, 2.53253));
}

TEST(anti_aliasing, average2x) {
    auto color1 = 0xff5eb390;
    auto color2 = 0xff432f00;
    auto color3 = 0xff3c9210;
    auto color4 = 0xff77e77e;
    ASSERT_EQ(color_average(color1, color2, color3, color4), 0xff559647);
}

TEST(anti_aliasing, simple_mixing_by_average2x) {
    std::uint32_t data[] = {0xff5eb390, 0xff432f00, 0xff3c9210, 0xff77e77e};
    std::vector<std::uint32_t> destination{};
    average2x2(std::span(data), std::back_inserter(destination), 1);
    ASSERT_EQ(destination[0], 0xff559647);
}

