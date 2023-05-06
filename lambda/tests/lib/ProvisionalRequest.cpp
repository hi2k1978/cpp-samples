#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>

#include<iostream>

#include"ProvisionalRequest.h"

namespace CppTest {

    void hoge() {
        std::cout << "\n\nhoge\n\n" << std::endl;
    }
    
    using namespace aws::lambda_runtime;
    using namespace Aws::Utils::Json;

    auto create_default_headers() -> JsonValue {
        JsonValue headers;
        headers.WithString("Content-Type", "application/json");
        return headers;
    }

    auto create_default_body() -> JsonValue {
        JsonValue body;
        return body;
    }

    auto create_default_query() -> JsonValue {
        JsonValue query;
        return query;
        
    }

    // auto Request::create_invocation_request -> invocation_request {}

    // auto Request::show() -> void {}
}
