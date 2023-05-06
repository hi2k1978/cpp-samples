#include "gtest/gtest.h"
#include "test_modules/test_cpp_samples_get.cpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
