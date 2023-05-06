#include "gtest/gtest.h"
#include "test_modules/CppSamplesGetTest.cpp"
#include "test_modules/CppSamplesPostTest.cpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
