// #include "sample1.h"
// #include "sample2.h"

#include "gtest/gtest.h"
#include "test_modules/test_sample1.cpp"
#include "test_modules/test_sample2.cpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
