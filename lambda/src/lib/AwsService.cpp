#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>

#include "AwsService.h"

namespace AwsService {

    namespace DynamoDB {
        
        Result::Result(const bool is_success, Aws::String&& error_message) noexcept
            : is_success(is_success), error_message(std::move(error_message)) {}

        Result::Result(const bool is_success) noexcept
            : Result(is_success, Aws::String()) {}

        Client::Client(const DynamoDBClient& client) noexcept
                : client_(client) {}

        auto Client::get_item(const GetItemRequest& request) -> std::tuple<Result, Item> const {
            const Aws::DynamoDB::Model::GetItemOutcome &outcome = client_.GetItem(request);
            if (outcome.IsSuccess()) {
                return {Result(true), outcome.GetResult().GetItem()};
            } else {
                Aws::String error_message = Aws::String(outcome.GetError().GetMessage());
                return {Result(false, std::move(error_message)), Item()};
            }
        }

        auto Client::put_item(const PutItemRequest& request) -> Result const {
            const Aws::DynamoDB::Model::PutItemOutcome outcome = client_.PutItem(request);
            if (outcome.IsSuccess()) {
                return Result(true);
            } else {
                Aws::String error_message = Aws::String(outcome.GetError().GetMessage());
                return Result(false, std::move(error_message));
            }
        }
    } // namespace Dynamodb    
}  // namespace AwsService
        
