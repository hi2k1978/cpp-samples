// Copyright 2023 hi2k1978
#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <aws/core/utils/memory/stl/SimpleStringStream.h>
#include<memory>
#include<iostream>
#include<vector>

#include "cpp_lambda.h"

using namespace aws::lambda_runtime;

namespace CppSamplesGet {
    using namespace CppLambda;

    // This class is hard-coded. Because it is only used in this source file.
    class GetRequestHandler final : public BaseRequestHandler {
    private:
        const Event& event;
    public:
        GetRequestHandler(const Event& event_) : event(event_) {}
        invocation_response getResponse() const override;
    };

    invocation_response GetRequestHandler::getResponse() const {
        using namespace Aws::Utils::Json;

        StatusCode status_code = StatusCode::OK;
        JsonValue body;
        body.WithString("message", "ok");
        body.WithString("httpMethod", "get");
        // body.WithString("httpMethod", "get");

        Response response(status_code, body);
        return response.get();
    }

    invocation_response lambda_handler(const invocation_request& request) {
        Event event(request);
        RequestHandlerMap request_handler_map;
        request_handler_map.emplace(RequestType::GET, std::make_unique<GetRequestHandler>(event));
        RequestHandlerSelector selector(request_handler_map);
        return selector.getResponse(event.request_type);
    }
}  // namespace CppSamplesGet

int main() {
    run_handler(CppSamplesGet::lambda_handler);
    return 0;
}
