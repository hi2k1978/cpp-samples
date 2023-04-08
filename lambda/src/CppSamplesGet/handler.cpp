// Copyright 2023 hi2k1978
#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <aws/core/utils/memory/stl/SimpleStringStream.h>

#include<memory>
#include<iostream>
#include<vector>

#include "request_types.h"
#include "response_types.h"
#include "cpp_lambda.h"

using namespace aws::lambda_runtime;

namespace CppSamplesGet {
    using namespace CppLambda;

    // This class is hard-coded. Because it is only used in this source file.
    class GetRequestHandler final : public BaseRequestHandler {
    private:
        const Event& event;
    public:
        GetRequestHandler(const Event& event) noexcept : event(event) {}
        invocation_response getResponse() const noexcept override;
    };

    invocation_response GetRequestHandler::getResponse() const noexcept{
        using namespace Aws::Utils::Json;

        JsonValue body;
        body.WithString("message", ResponseMessage::OK);
        body.WithString("result", "request(get): successful");

        Response response(StatusCode::OK, std::move(body));
        return response.get();
    }

    invocation_response lambda_handler(const invocation_request& request) {
        Event event(request);
        RequestHandlerMap request_handler_map;
        request_handler_map.emplace(RequestType::GET, std::make_unique<GetRequestHandler>(event));
        request_handler_map.emplace(
            RequestType::OTHERS,
            std::make_unique<InvalidRequestHandler>(StatusCode::BAD_REQUEST, ResponseMessage::BAD_REQUEST));

        BaseRequestHandler *target;
        if (request_handler_map.contains(event.request_type)) {
            target = (request_handler_map.at(event.request_type)).get();
        } else {
            target = (request_handler_map.at(RequestType::OTHERS)).get();
        }
        return target->getResponse();
    }
}  // namespace CppSamplesGet

int main() {
    run_handler(CppSamplesGet::lambda_handler);
    return 0;
}












