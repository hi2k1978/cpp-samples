#include"gtest/gtest.h"
#include "sample1.h"

namespace Sample1 {
    TEST(Sample1, mymax) {
        EXPECT_EQ(mymax(10, 5), 10);
        EXPECT_EQ(mymax(5, 10), 10);
        EXPECT_EQ(mymax(-10, -5), -5);
        EXPECT_EQ(mymax(-5, -10), -5);
        EXPECT_EQ(mymax(5, 5), 5);
        EXPECT_EQ(mymax(-5, -5), -5);
    }
}
