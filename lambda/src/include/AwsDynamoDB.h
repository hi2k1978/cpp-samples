#ifndef AWS_DYNAMODB_H_
#define AWS_DYNAMODB_H_

#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>

#include <aws/core/Aws.h>
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/AttributeDefinition.h>
#include <aws/dynamodb/model/GetItemRequest.h>
#include <iostream>

namespace AwsService {
    
    using namespace aws::lambda_runtime;
    using namespace Aws::Utils::Json;

    namespace DynamoDB {

        using Item = Aws::Map<Aws::String, Aws::DynamoDB::Model::AttributeValue>;
        using GetItemRequest = Aws::DynamoDB::Model::GetItemRequest;
        using PutItemRequest = Aws::DynamoDB::Model::PutItemRequest;

        struct Result {
            Result(const bool is_success, Aws::String&& error_message, Item&& item) noexcept;
            Result(const bool is_success) noexcept;
            Result(const bool is_success, Item&& item) noexcept;
            Result(const bool is_success, Aws::String&& error_message) noexcept;
            
            const bool is_success;
            const Aws::String error_message;
            const Item item;
        }; // struct Result
    
        class Client {
        public:
            Client(const Aws::Client::ClientConfiguration &config) noexcept;
            auto get_item(GetItemRequest& request) -> Result;
            auto put_item(PutItemRequest& request) -> Result;
        private:
            Aws::DynamoDB::DynamoDBClient client;
        }; // class DynamoDB

    } // namespace Dynamodb    
}  // namespace AwsService
#endif  // AWS_DYNAMODB_H_
