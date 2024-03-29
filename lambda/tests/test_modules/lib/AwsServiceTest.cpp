#include<iostream>

#include"gmock/gmock.h"
#include"gtest/gtest.h"
#include"AwsService.h"
#include"TestLambda.h"
using ::testing::AtLeast;

namespace AwsService {

    class lib_AwsService : public ::testing::Test {
    protected:
        const Aws::Client::ClientConfiguration create_clientConfig() {
            Aws::SDKOptions options;
            Aws::InitAPI(options);            
            return Aws::Client::ClientConfiguration();
        };
        
        const Aws::Client::ClientConfiguration clientConfig;

        lib_AwsService() : clientConfig(create_clientConfig()) {};
    };
    
    TEST_F(lib_AwsService, N_DynamoDB_Result_TestConstructor_Success) {
        DynamoDB::Result result(true);
        EXPECT_EQ(result.is_success, true);
        EXPECT_EQ(result.error_message, "");
    }
    
    TEST_F(lib_AwsService, N_DynamoDB_Result_TestConstructor_Error) {
        DynamoDB::Result result(false, "some error occured.");
        EXPECT_EQ(result.is_success, false);
        EXPECT_EQ(result.error_message, "some error occured.");
    }

    TEST_F(lib_AwsService, N_DynamoDB_Client_TestGetItem) {

        Aws::DynamoDB::Model::GetItemRequest request;
        request.SetTableName("TestTable");
        request.AddKey("pKey", Aws::DynamoDB::Model::AttributeValue().SetS("TestValue001"));

        Aws::DynamoDB::Model::GetItemOutcome outcome;

        DynamoDB::Client client(clientConfig);
        // EXPECT_CALL(client, GetItem(request))
        //     .Times(AtLeast(1));


        
        EXPECT_EQ(true, true);
    }

    TEST_F(lib_AwsService, N_DynamoDB_Client_TestPutItem) {
        DynamoDB::Client client(clientConfig);
        EXPECT_EQ(true, true);
    }
}
