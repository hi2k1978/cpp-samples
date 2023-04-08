#ifndef LAMBDA_SRC_INCLUDE_TYPES_INVOCATION_TYPES_H_
#define LAMBDA_SRC_INCLUDE_TYPES_INVOCATION_TYPES_H_

#include <aws/lambda-runtime/runtime.h>

namespace CppLambda {

    namespace HttpMethod {
        static constexpr auto GET = "GET";
        static constexpr auto POST = "POST";
    }  // namespace HttpMethod

    enum class EventType {
        OTHERS = 0,
        GET = 1,
        POST = 2,
    };
    
    template<typename E, typename =
             typename std::enable_if<std::is_enum<E>::value, E>::type>
    inline std::ostream& operator << (std::ostream& os, E e ) {
        return os << static_cast<std::underlying_type<E>::type>(e);
    }
    
    namespace ContentType {
        static constexpr auto APPLICATION_JSON = "application/json";
    }  // namespace ContentType

    using StatusCode = aws::http::response_code;

    namespace ResponseMessage {
        static std::string NONE = "";
        static std::string OK = "OK";
        static std::string BAD_REQUEST = "bad request.";
    }  // namespace ErrorMessage
}  // namespace CppLambda
#endif  // LAMBDA_SRC_INCLUDE_TYPES_INVOCATION_TYPES_H_
