#ifndef LAMBDA_SRC_INCLUDE_REQUEST_H_
#define LAMBDA_SRC_INCLUDE_REQUEST_H_

#include <aws/lambda-runtime/runtime.h>

#include<iostream>

namespace CppLambda {

    namespace HttpMethod {
        static constexpr auto GET = "GET";
        static constexpr auto POST = "POST";
    }  // namespace HttpMethod

    enum class RequestType {
        OTHERS = 0,
        GET = 1,
        POST = 2,
    };
    
    template<typename E, typename =
             typename std::enable_if<std::is_enum<E>::value, E>::type>
    inline std::ostream& operator << (std::ostream& os, E e ) {
        return os << static_cast<std::underlying_type<E>::type>(e);
    }
    
}  // namespace CppLambda
#endif  // LAMBDA_SRC_INCLUDE_REQUEST_H_

