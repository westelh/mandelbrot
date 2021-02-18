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
    auto mixed = average2x(color1, color2);
    ASSERT_EQ(mixed, 0xff507148);
}

TEST(anti_aliasing, simple_mixing_by_average2x) {
    std::uint32_t data[] = {0xff5eb390, 0xff432f00};
    std::uint32_t destination[1];
    mix_for_every<2>(std::span(data), std::span(destination), average2x);
    ASSERT_EQ(destination[0], 0xff507148);
}

