#ifndef LAMBDA_SRC_INCLUDE_TYPES_RESPONSE_TYPES_H_
#define LAMBDA_SRC_INCLUDE_TYPES_RESPONSE_TYPES_H_

#include <aws/lambda-runtime/runtime.h>

namespace CppLambda {

    
    using StatusCode = aws::http::response_code;

    namespace ContentType {
        static constexpr auto APPLICATION_JSON = "application/json";
    }  // namespace ContentType
    
    namespace ResponseMessage {
        static std::string OK = "OK";
        static std::string BAD_REQUEST = "bad request.";
    }  // namespace ErrorMessage
}  // namespace CppLambda
#endif  // LAMBDA_SRC_INCLUDE_TYPES_RESPONSE_TYPES_H_
