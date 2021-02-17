#include <gtest/gtest.h>
#include "utils.h"

TEST(utils, rgb_packing_test) {
    GTEST_ASSERT_EQ(0xffffffff, pack_rgb(0xff, 0xff, 0xff));
    GTEST_ASSERT_EQ(0xff000000, pack_rgb(0x00, 0x00, 0x00));
    GTEST_ASSERT_EQ(0xff6c2f92, pack_rgb(0x6c, 0x2f, 0x92));
}

TEST(utils, argb_splitting_test) {
    constexpr auto black = 0xffffffff;
    constexpr auto white = 0xff000000;
    constexpr auto color = 0x806c2f92;
    // alpha
    GTEST_ASSERT_EQ(0xff, pick<argb::alpha>(black));
    GTEST_ASSERT_EQ(0xff, pick<argb::alpha>(white));
    GTEST_ASSERT_EQ(0x80, pick<argb::alpha>(color));
    // red
    GTEST_ASSERT_EQ(0xff, pick<argb::red>(black));
    GTEST_ASSERT_EQ(0x00, pick<argb::red>(white));
    GTEST_ASSERT_EQ(0x6c, pick<argb::red>(color));
    // green
    GTEST_ASSERT_EQ(0xff, pick<argb::green>(black));
    GTEST_ASSERT_EQ(0x00, pick<argb::green>(white));
    GTEST_ASSERT_EQ(0x2f, pick<argb::green>(color));
    // blue
    GTEST_ASSERT_EQ(0xff, pick<argb::blue>(black));
    GTEST_ASSERT_EQ(0x00, pick<argb::blue>(white));
    GTEST_ASSERT_EQ(0x92, pick<argb::blue>(color));
}
