#ifndef TEST_MODULES_H_
#define TEST_MODULES_H_

#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>

#include<iostream>


namespace CppTest {

    using namespace aws::lambda_runtime;
    using namespace Aws::Utils::Json;

    JsonValue create_default_headers();
    JsonValue create_default_body();
    JsonValue create_default_query();
    
    class Request {
    public: 
        Request(const std::string& http_method, const std::string& path,
                const JsonValue& headers, const JsonValue& body, const JsonValue& query) noexcept
            : http_method(http_method), path(path), headers(headers), body(body), query(query) {};

        invocation_request create_invocation_request();
        void show();
    private:
        const std::string http_method;
        const std::string path;
        const JsonValue headers;
        const JsonValue body;
        const JsonValue query;

    };
}
#endif
