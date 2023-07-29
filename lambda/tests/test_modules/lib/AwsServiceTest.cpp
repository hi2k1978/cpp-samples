#include<iostream>

#include"gmock/gmock.h"
#include"gtest/gtest.h"
#include"AwsService.h"
#include"TestLambda.h"
using ::testing::AtLeast;

namespace AwsService {
    TEST(lib_AwsService, N_DynamoDB_Result_TestConstructor_Success) {
        DynamoDB::Result result(true);
        EXPECT_EQ(result.is_success, true);
        EXPECT_EQ(result.error_message, "");
    }
    
    TEST(lib_AwsService, N_DynamoDB_Result_TestConstructor_Failure) {
        DynamoDB::Result result(false, "some error occured.");
        EXPECT_EQ(result.is_success, false);
        EXPECT_EQ(result.error_message, "some error occured.");
    }
}
