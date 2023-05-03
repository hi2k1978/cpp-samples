#include "gtest/gtest.h"
#include "sample2.h"

namespace Sample2 {
    TEST(Sample2, mymin1) {
        EXPECT_EQ(mymin(10, 5), 5);
        EXPECT_EQ(mymin(5, 10), 5);
        EXPECT_EQ(mymin(-10, -5), -10);
        EXPECT_EQ(mymin(-5, -10), -10);
        EXPECT_EQ(mymin(5, 5), 5);
        EXPECT_EQ(mymin(-5, -5), -5);
    }
}
