#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>

#include <aws/core/Aws.h>
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/AttributeDefinition.h>
#include <aws/dynamodb/model/GetItemRequest.h>
#include <iostream>

#include "AwsDynamoDB.h"

namespace AwsService {

    namespace DynamoDB {
        
        Result::Result(const bool is_success, Aws::String&& error_message) noexcept
            : is_success(is_success), error_message(std::move(error_message)) {}
        
        Result::Result(const bool is_success) noexcept
            : Result(is_success, Aws::String()) {}

        Client::Client(const Aws::Client::ClientConfiguration &config) noexcept {
            Aws::DynamoDB::DynamoDBClient client(config);
        }
            
        auto Client::get_item(GetItemRequest& request) -> std::tuple<Result, Item> {
            const Aws::DynamoDB::Model::GetItemOutcome &outcome = client.GetItem(request);
            bool is_success = outcome.IsSuccess();
            if (is_success) {
                return {Result(true), outcome.GetResult().GetItem()};
            } else {
                Aws::String error_message = outcome.GetError().GetMessage();
                return {Result(false, std::move(error_message)), Item()};
            }
        }
        
        auto Client::put_item(PutItemRequest& request) -> Result {
            const Aws::DynamoDB::Model::PutItemOutcome outcome = client.PutItem(request);
            bool is_success = outcome.IsSuccess();
            if (is_success) {
                return Result(true);
            } else {
                Aws::String error_message = outcome.GetError().GetMessage();
                return Result(false, std::move(error_message));
            }
        }
    } // namespace Dynamodb    
}  // namespace AwsService
        
