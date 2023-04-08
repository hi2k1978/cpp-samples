#ifndef LAMBDA_SRC_INCLUDE_TYPES_INVOCATION_TYPES_H_
#define LAMBDA_SRC_INCLUDE_TYPES_INVOCATION_TYPES_H_

#include <aws/lambda-runtime/runtime.h>

namespace CppLambda {

    namespace HttpMethod {
        static constexpr auto OPTIONS = "OPTIONS";
        static constexpr auto GET = "GET";
        static constexpr auto POST = "POST";
    }  // namespace HttpMethod

    enum class EventType {
        OTHERS = 0,
        OPTIONS = 1,
        GET = 2,
        POST = 3,
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

    namespace CorsKey {
        static std::string ALLOW_ORIGIN = "Access-Control-Allow-Origin";
        static std::string ALLOW_METHODS = "Access-Control-Allow-Methods";
        static std::string ALLOW_HEADERS = "Access-Control-Allow-Headers";
        static std::string EXPOSE_HEADERS = "Access-Control-Expose-Headers";
        static std::string ALLOW_CREDENTIALS = "Access-Control-Allow-Credentials";
        static std::string MAX_AGE = "Access-Control-Max-Age";
    }

    namespace CorsValue {
        static std::string ALLOW_ORIGIN = "*";
        static std::string ALLOW_METHODS = "GET,POST,OPTIONS";
        static std::string ALLOW_HEADERS = "*";
        static std::string EXPOSE_HEADERS = "*";
        static std::string ALLOW_CREDENTIALS = "*";
        static int MAX_AGE = 86400;
    }

    namespace ResponseKey {
        static std::string STATUS_CODE = "statusCode";
        static std::string HEADERS = "headers";
        static std::string BODY = "body";
        static std::string MESSAGE = "message";
        static std::string RESULT = "result";
    }
}  // namespace CppLambda
#endif  // LAMBDA_SRC_INCLUDE_TYPES_INVOCATION_TYPES_H_
