#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <aws/core/utils/memory/stl/SimpleStringStream.h>
#include<memory>
#include<iostream>

#include "response.h"

using namespace aws::lambda_runtime;

invocation_response lambda_handler(invocation_request const& request)
{

    using namespace Aws::Utils::Json;

    auto event = std::make_unique<CppLambda::Event>(request);
    std::cout << event->http_method << std::endl;

    CppLambda::StatusCode status_code = CppLambda::StatusCode::OK;
    JsonValue body;
    body.WithString("message", "ok");
    body.WithString("result", "nothing");

    auto response = std::make_unique<CppLambda::Response>(std::move(status_code), std::move(body));
    return response->get();
}


int main()
{
    run_handler(lambda_handler);
    return 0;
}
