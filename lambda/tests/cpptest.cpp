#include "gtest/gtest.h"
#include "TestModules/TestModules.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
