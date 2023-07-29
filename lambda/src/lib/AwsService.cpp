#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>

#include "AwsService.h"

namespace AwsService {

    namespace DynamoDB {
        
        Result::Result(const bool is_success, Aws::String&& error_message) noexcept
            : is_success(is_success), error_message(std::move(error_message)) {}
        
        Result::Result(const bool is_success) noexcept
            : Result(is_success, Aws::String()) {}

    } // namespace Dynamodb    
}  // namespace AwsService
        
