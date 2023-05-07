#include "gtest/gtest.h"
#include "test_modules/TestModules.h"
#include"TestMod.h"

int main(int argc, char **argv) {

    TestMod::start_test();
    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
