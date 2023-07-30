#ifndef AWS_SERVICE_MOCK_H_
#define AWS_SERVICE_MOCK_H_

#include"gmock/gmock.h"
#include"AwsService.h"

namespace AwsService {
    namespace DynamoDB {
        
        class MockDynamoDBClient : public Aws::DynamoDB::DynamoDBClient{
        public:
            MockDynamoDBClient(const Aws::Client::ClientConfiguration &clientConfig) {};
            
            MOCK_METHOD(Aws::DynamoDB::Model::GetItemOutcome, GetItem, (const DynamoDB::GetItemRequest& request), (const, override));
            MOCK_METHOD(Aws::DynamoDB::Model::PutItemOutcome, PutItem, (const DynamoDB::PutItemRequest& request), (const, override));
        };        
    }
}
#endif
