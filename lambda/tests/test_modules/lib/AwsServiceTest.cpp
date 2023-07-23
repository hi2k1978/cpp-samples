#include<iostream>

#include"gmock/gmock.h"
#include"gtest/gtest.h"
#include"AwsService.h"
#include"TestLambda.h"
using ::testing::AtLeast;

namespace AwsService {
    TEST(lib_AwsService, N_Test_Hello_World) {
        EXPECT_EQ("hello world", "ohhelo world");
    }
    
    // TEST(lib_AwsService, N_DynamoDB_Result_TestConstructor001) {
    //     bool is_success = true;
    //     Aws::String error_message = "some error occured.";
    //     DynamoDB::Result result(true, "some error occured.");
    //     EXPECT_EQ(result.is_success, false);
    //     EXPECT_EQ(result.error_message, "some error occured.");
    // }
    
}
