#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>
// #include <aws/core/utils/memory/stl/SimpleStringStream.h>

#include<iostream>
#include<memory>
#include<vector>

#include "CppSamplesPost.h"

using namespace aws::lambda_runtime;

namespace CppSamplesPost {
    using namespace AwsLambda;

    EventValidator::EventValidator(const Event& event) noexcept
        : event(event) {}

    auto EventValidator::validate() const noexcept -> std::tuple<DefaultResult, std::vector<std::string_view>> {
        std::vector<std::string_view> validation_error_messages;
        // TODO: remove after test is finished.
        validation_error_messages.push_back(EventValidationError::TEST);
        validation_error_messages.push_back(EventValidationError::TEST);
        validation_error_messages.push_back(EventValidationError::TEST);

        bool is_success = true;
        DefaultResult result = is_success
            ? DefaultResult(true)
            : DefaultResult(false, ErrorCode::EVENT_VALIDATION_ERROR, ErrorMessage::EVENT_VALIDATION_ERROR);
        return {result, validation_error_messages};
    }

    EventHandler::EventHandler(const Event& event) noexcept : event(event) {}

    auto EventHandler::create_response() const -> invocation_response {
        using namespace Aws::Utils::Json;

        EventValidator event_validator(event);
        std::tuple<DefaultResult, std::vector<std::string_view>> valid = event_validator.validate();
        auto& [result, verrors] = valid;
        // TODO: additional coding is required. validator always returns true.
        if (!result.is_success) {
            // TODO: replace logger
            std::cerr << result.error_code << ": "
                      << result.error_message << std::endl;
            Response response(StatusCode::BAD_REQUEST, ResponseMessage::BAD_REQUEST);
            return response.create_response();
        }
 
        JsonValue body;
        body.WithString(ResponseKey::MESSAGE, ResponseMessage::OK);
        body.WithString(ResponseKey::RESULT, "success...");

        Response response(StatusCode::OK, std::move(body));
        return response.create_response();
    }

    inline auto create_event_handler(const Event& event) -> std::unique_ptr<BaseEventHandler> {
        switch(event.event_type) {
        case EventType::OPTIONS:
            return std::make_unique<DefaultEventHandler>(StatusCode::OK);
        case EventType::POST:
            return std::make_unique<EventHandler>(event);
        case EventType::GET: // health check
            return std::make_unique<DefaultEventHandler>(StatusCode::OK);
        default:
            return std::make_unique<ErrorEventHandler>(StatusCode::BAD_REQUEST, ResponseMessage::BAD_REQUEST);
        }
    }
    
    auto handler(const invocation_request& request) -> invocation_response {
        Event event(request);
        DefaultResult result = event.initialize();
        if (!result.is_success) {
            // TODO: replace logger
            std::cerr << result.error_code << ": "
                      <<  result.error_message << std::endl;
            Response response(StatusCode::BAD_REQUEST, ResponseMessage::BAD_REQUEST);
            return response.create_response();
        }

        std::unique_ptr<BaseEventHandler> event_handler = create_event_handler(event);
        return event_handler->create_response();
    }
}  // namespace CppSamplesPost
