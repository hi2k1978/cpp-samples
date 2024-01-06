#ifndef AWS_SERVICE_H_
#define AWS_SERVICE_H_

#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <aws/core/client/ClientConfiguration.h>

#include <aws/core/Aws.h>
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/AttributeDefinition.h>
#include <aws/dynamodb/model/GetItemRequest.h>
#include <aws/dynamodb/model/GetItemResult.h>
#include <aws/dynamodb/model/PutItemRequest.h>
#include <aws/dynamodb/model/PutItemResult.h>
#include <iostream>

namespace AwsService {
    
    namespace DynamoDB {

        using Item = Aws::Map<Aws::String, Aws::DynamoDB::Model::AttributeValue>;
        using DynamoDBClient = Aws::DynamoDB::DynamoDBClient;
        using GetItemRequest = Aws::DynamoDB::Model::GetItemRequest;
        using PutItemRequest = Aws::DynamoDB::Model::PutItemRequest;

        struct Result {
            Result(const bool is_success, Aws::String&& error_message) noexcept;
            Result(const bool is_success) noexcept;
            
            const bool is_success;
            const Aws::String error_message;
        }; // struct Result
        
        class Client {
        public:
            Client(const DynamoDBClient &client) noexcept;
            auto get_item(const GetItemRequest& request) -> std::tuple<Result, Item> const;
            auto put_item(const PutItemRequest& request) -> Result const;

        private:
            const Aws::DynamoDB::DynamoDBClient& client_;
        }; // class DynamoDB

    } // namespace Dynamodb    
}  // namespace AwsService
#endif  // AWS_SERVICE_H_
