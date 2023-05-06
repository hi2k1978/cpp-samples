#include "gtest/gtest.h"
#include "TestModules/TestModules.h"
#include"CppTestLib.h"

int main(int argc, char **argv) {
    CppTest::hoge();
    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
