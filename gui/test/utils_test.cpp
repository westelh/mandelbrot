#include <gtest/gtest.h>
#include "utils.h"

TEST(utils, rgb_packing_test) {
    GTEST_ASSERT_EQ(0xffffffff, pack_rgb(0xff, 0xff, 0xff));
    GTEST_ASSERT_EQ(0xff000000, pack_rgb(0x00, 0x00, 0x00));
    GTEST_ASSERT_EQ(0xff6c2f92, pack_rgb(0x6c, 0x2f, 0x92));
}
