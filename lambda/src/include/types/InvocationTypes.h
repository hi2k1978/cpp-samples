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
        OPTIONS = 0,
        GET = 1,
        POST = 2,
        OTHERS = 254,
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

    namespace ResponseKey {
        static constexpr auto STATUS_CODE = "statusCode";
        static constexpr auto HEADERS = "headers";
        static constexpr auto BODY = "body";
        static constexpr auto MESSAGE = "message";
        static constexpr auto RESULT = "result";
    }

    namespace ResponseMessage {
        static constexpr auto NONE = "";
        static constexpr auto OK = "OK";
        static constexpr auto BAD_REQUEST = "bad request.";
    }  // namespace ErrorMessage

    namespace CorsKey {
        static constexpr auto ACCESS_CONTROL_ALLOW_ORIGIN = "Access-Control-Allow-Origin";
        static constexpr auto ACCESS_CONTROL_ALLOW_METHODS = "Access-Control-Allow-Methods";
        static constexpr auto ACCESS_CONTROL_ALLOW_HEADERS = "Access-Control-Allow-Headers";
        static constexpr auto ACCESS_CONTROL_EXPOSE_HEADERS = "Access-Control-Expose-Headers";
        static constexpr auto ACCESS_CONTROL_ALLOW_CREDENTIALS = "Access-Control-Allow-Credentials";
        static constexpr auto ACCESS_CONTROL_MAX_AGE = "Access-Control-Max-Age";
    }

    namespace CorsValue {
        // static constexpr auto ACCESS_CONTROL_ALLOW_ORIGIN = "*";
        static constexpr auto ACCESS_CONTROL_ALLOW_ORIGIN = Stage::ACCESS_CONTROL_ALLOW_ORIGIN;
        static constexpr auto ACCESS_CONTROL_ALLOW_METHODS = Stage::ACCESS_CONTROL_ALLOW_METHODS;
        static constexpr auto ACCESS_CONTROL_ALLOW_HEADERS = Stage::ACCESS_CONTROL_ALLOW_HEADERS;
        static constexpr auto ACCESS_CONTROL_EXPOSE_HEADERS = Stage::ACCESS_CONTROL_EXPOSE_HEADERS;
        static constexpr auto ACCESS_CONTROL_ALLOW_CREDENTIALS = Stage::ACCESS_CONTROL_ALLOW_CREDENTIALS;
        static int MAX_AGE = Stage::ACCESS_CONTROL_MAX_AGE;
    }

}  // namespace CppLambda
#endif  // LAMBDA_SRC_INCLUDE_TYPES_INVOCATION_TYPES_H_
