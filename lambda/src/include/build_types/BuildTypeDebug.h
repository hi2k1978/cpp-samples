#ifndef BUILD_TYPE_DEFINED_
#define BUILD_TYPE_DEFINED_

#include<iostream>

namespace CppLambda {    
    namespace Env {
        // CORS
        static constexpr auto ACCESS_CONTROL_ALLOW_ORIGIN = "*";
        static constexpr auto ACCESS_CONTROL_ALLOW_METHODS = "GET,POST,OPTIONS";
        static constexpr auto ACCESS_CONTROL_ALLOW_HEADERS = "*";
        static constexpr auto ACCESS_CONTROL_EXPOSE_HEADERS = "*";
        static constexpr auto ACCESS_CONTROL_ALLOW_CREDENTIALS = "*";
        static constexpr auto ACCESS_CONTROL_MAX_AGE = 86400;
    }
}
#endif
