// Copyright 2023 hi2k1978
#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <aws/core/utils/memory/stl/SimpleStringStream.h>

#include<iostream>
#include<memory>
#include<vector>

#include "cpp_lambda.h"
#include "handler.h"

using namespace aws::lambda_runtime;

namespace CppSamplesGet {
    using namespace CppLambda;


    EventValidationResult EventValidator::validate() const {
        std::vector<std::string> error_messages;
        error_messages.push_back(EventValidateErrorMessage::TEST);

        bool is_valid = true;
        EventValidationResult result(is_valid, std::move(error_messages));
        return result;
    }

    invocation_response GetRequestHandler::get_response() const noexcept{
        using namespace Aws::Utils::Json;

        JsonValue body;
        body.WithString("message", ResponseMessage::OK);
        body.WithString("result", "request(get): successful");

        Response response(StatusCode::OK, std::move(body));
        return response.get();
    }

    invocation_response handler(const invocation_request& request) {
        Event event(request);
        event.initialize();

        EventValidator event_validator(event);
        EventValidationResult event_validation_result = event_validator.validate();
        // TODO: additional coding is required. validator always returns true.
        if (!event_validation_result.is_valid) {
            std::cerr << ErrorMessage::EVENT_VALIDATION_ERROR << std::endl;
            event_validation_result.show();
            InvalidRequestHandler handler(StatusCode::BAD_REQUEST, ResponseMessage::BAD_REQUEST);
            return handler.get_response();
        }
        
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
        return target->get_response();
    }
}  // namespace CppSamplesGet

int main() {
    run_handler(CppSamplesGet::handler);
    return 0;
}












