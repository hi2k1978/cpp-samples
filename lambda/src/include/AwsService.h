#ifndef AWS_SERVICE_H_
#define AWS_SERVICE_H_

#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <aws/core/client/ClientConfiguration.h>

#include <aws/core/Aws.h>
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/AttributeDefinition.h>
#include <aws/dynamodb/model/GetItemRequest.h>
#include <aws/dynamodb/model/PutItemRequest.h>
#include <aws/dynamodb/model/PutItemResult.h>
#include <iostream>

namespace AwsService {
    
    using namespace aws::lambda_runtime;
    using namespace Aws::Utils::Json;

    namespace DynamoDB {

        using Item = Aws::Map<Aws::String, Aws::DynamoDB::Model::AttributeValue>;
        using GetItemRequest = Aws::DynamoDB::Model::GetItemRequest;
        using PutItemRequest = Aws::DynamoDB::Model::PutItemRequest;

        struct Result {
            Result(const bool is_success, Aws::String&& error_message) noexcept;
            Result(const bool is_success) noexcept;
            
            const bool is_success;
            const Aws::String error_message;
        }; // struct Result
    
        template<class DynamoDBClient=Aws::DynamoDB::DynamoDBClient> class Client {
        public:
            Client(const Aws::Client::ClientConfiguration &clientConfig) // noexcept
                : client(DynamoDBClient(clientConfig)) {}
 
            
            auto get_item(const GetItemRequest& request) -> std::tuple<Result, Item> const {
                const Aws::DynamoDB::Model::GetItemOutcome &outcome = client.GetItem(request);
                if (outcome.IsSuccess()) {
                    return {Result(true), outcome.GetResult().GetItem()};
                } else {
                    return {Result(false, outcome.GetError().GetMessage()), Item()};
                }
            }
        
            auto put_item(const PutItemRequest& request) -> Result const {
                const Aws::DynamoDB::Model::PutItemOutcome outcome = client.PutItem(request);
                if (outcome.IsSuccess()) {
                    return Result(true);
                } else {
                    return Result(false, outcome.GetError().GetMessage());
                }
            }
         private:
            const DynamoDBClient client;
        }; // class DynamoDB

    } // namespace Dynamodb    
}  // namespace AwsService
#endif  // AWS_SERVICE_H_
