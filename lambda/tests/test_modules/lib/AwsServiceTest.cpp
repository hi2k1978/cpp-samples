#include<iostream>

#include"gmock/gmock.h"
#include"gtest/gtest.h"
#include"AwsService.h"
#include"TestLambda.h"
using ::testing::AtLeast;

namespace AwsService {
    class MockDynamoDBClient : public Aws::DynamoDB::DynamoDBClient{
    public:
        MockDynamoDBClient(const Aws::Client::ClientConfiguration &clientConfig) {};
        
        MOCK_METHOD(Aws::DynamoDB::Model::GetItemOutcome, GetItem, (const DynamoDB::GetItemRequest& request), (const, override));
        MOCK_METHOD(Aws::DynamoDB::Model::PutItemOutcome, PutItem, (const DynamoDB::PutItemRequest& request), (const, override));
    };
        
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

    TEST(lib_AwsService, N_DynamoDB_Client_TestConstructor) {
        Aws::SDKOptions options;
        Aws::InitAPI(options);
        Aws::Client::ClientConfiguration clientConfig;
        DynamoDB::Client<MockDynamoDBClient> client(clientConfig);
        EXPECT_EQ(1, 1);
    }
}
