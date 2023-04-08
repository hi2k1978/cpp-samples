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

    auto GetEventValidator::validate() const noexcept -> EventValidationResult {
        std::vector<std::string_view> error_messages;
        error_messages.push_back(EventValidationError::TEST);

        bool is_valid = true;
        EventValidationResult result(is_valid, std::move(error_messages));
        return result;
    }

    auto GetHandler::get_response() const -> invocation_response {
        using namespace Aws::Utils::Json;

        GetEventValidator event_validator(event);
        EventValidationResult event_validation_result = event_validator.validate();
        // TODO: additional coding is required. validator always returns true.
        if (!event_validation_result.is_valid) {
            std::cerr << RunTimeError::EVENT_VALIDATION_ERROR << std::endl;
            event_validation_result.show();
            Response response(StatusCode::BAD_REQUEST, ResponseMessage::BAD_REQUEST);
            return response.get();
        }
 
        JsonValue body;
        body.WithString(ResponseKey::MESSAGE, ResponseMessage::OK);
        body.WithString(ResponseKey::RESULT, "success.");

        Response response(StatusCode::OK, std::move(body));
        return response.get();
    }

    auto main_handler(const invocation_request& request) -> invocation_response {
        Event event(request);
        event.initialize();

        HandlerMap handler_map;
        handler_map.emplace(EventType::OPTIONS, std::make_unique<DefaultHandler>(StatusCode::OK, ResponseMessage::NONE));
        handler_map.emplace(EventType::GET, std::make_unique<GetHandler>(event));
        handler_map.emplace(EventType::OTHERS, std::make_unique<ErrorHandler>(StatusCode::BAD_REQUEST, ResponseMessage::BAD_REQUEST));

        BaseHandler *handler;
        if (handler_map.contains(event.type)) {
            handler = (handler_map.at(event.type)).get();
        } else {
            handler = (handler_map.at(EventType::OTHERS)).get();
        }
        return handler->get_response();
    }
}  // namespace CppSamplesGet

int main() {
    run_handler(CppSamplesGet::main_handler);
    return 0;
}












