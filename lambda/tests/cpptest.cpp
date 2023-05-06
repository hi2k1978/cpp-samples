#include "gtest/gtest.h"
#include "TestModules/TestModules.h"
#include"CppTestLib.h"

int main(int argc, char **argv) {

    CppTest::start_test();
    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
