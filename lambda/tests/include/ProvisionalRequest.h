#ifndef PROVISIONAL_REQUEST_H_
#define PROVISIONAL_REQUEST_H_

#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>

#include<iostream>


namespace TestLambda {

    using namespace aws::lambda_runtime;
    using namespace Aws::Utils::Json;

    JsonValue create_default_headers();
    JsonValue create_default_body();
    JsonValue create_default_query();
    
    class Request {
    public: 
        Request(const std::string& http_method, const std::string& path,
                const JsonValue& headers, const JsonValue& body, const JsonValue& query) noexcept;
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
