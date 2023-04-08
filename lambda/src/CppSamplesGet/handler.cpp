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

    EventValidationResult GetEventValidator::validate() const noexcept {
        std::vector<std::string_view> error_messages;
        error_messages.push_back(EventValidateErrorMessage::TEST);

        bool is_valid = true;
        EventValidationResult result(is_valid, std::move(error_messages));
        return result;
    }

    invocation_response GetHandler::get_response() const {
        using namespace Aws::Utils::Json;

        GetEventValidator event_validator(event);
        EventValidationResult event_validation_result = event_validator.validate();
        // TODO: additional coding is required. validator always returns true.
        if (!event_validation_result.is_valid) {
            std::cerr << ErrorMessage::EVENT_VALIDATION_ERROR << std::endl;
            event_validation_result.show();
            ErrorHandler handler(StatusCode::BAD_REQUEST, ResponseMessage::BAD_REQUEST);
            return handler.get_response();
        }
 
        JsonValue body;
        body.WithString("message", ResponseMessage::OK);
        body.WithString("result", "request(get): successful");

        Response response(StatusCode::OK, std::move(body));
        return response.get();
    }

    invocation_response handler(const invocation_request& request) {
        Event event(request);
        event.initialize();
        
        HandlerMap handler_map;
        handler_map.emplace(EventType::GET, std::make_unique<GetHandler>(event));
        handler_map.emplace(
            EventType::OTHERS,
            std::make_unique<ErrorHandler>(StatusCode::BAD_REQUEST, ResponseMessage::BAD_REQUEST)
            // std::make_unique<ErrorHandler>(StatusCode::BAD_REQUEST, ResponseMessage::NONE)
            );

        BaseHandler *target;
        if (handler_map.contains(event.type)) {
            target = (handler_map.at(event.type)).get();
        } else {
            target = (handler_map.at(EventType::OTHERS)).get();
        }
        return target->get_response();
    }
}  // namespace CppSamplesGet

int main() {
    run_handler(CppSamplesGet::handler);
    return 0;
}












