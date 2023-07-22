#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>
// #include <aws/core/utils/memory/stl/SimpleStringStream.h>

#include<iostream>
#include<memory>
#include<vector>

#include "CppSamplesGet.h"

using namespace aws::lambda_runtime;

namespace CppSamplesGet {
    using namespace CppLambda;

    EventValidator::EventValidator(const Event& event) noexcept
        : event(event) {}
    
    auto EventValidator::validate() const noexcept -> EventValidationResult {
        std::vector<std::string_view> validation_error_messages;
        // TODO: remove after test is finished.
        validation_error_messages.push_back(EventValidationError::TEST);
        validation_error_messages.push_back(EventValidationError::TEST);
        validation_error_messages.push_back(EventValidationError::TEST);

        bool result = true;
        if (result) {
            return EventValidationResult(true, ErrorCode::NONE, ErrorMessage::NONE, std::move(validation_error_messages));
        } else {
            return EventValidationResult(false,
                                         ErrorCode::EVENT_VALIDATION_ERROR,
                                         ErrorMessage::EVENT_VALIDATION_ERROR,
                                         std::move(validation_error_messages));
            
        }
    }

    EventHandler::EventHandler(const Event& event) noexcept : event(event) {}

    auto EventHandler::create_response() const -> invocation_response {
        using namespace Aws::Utils::Json;

        EventValidator event_validator(event);
        EventValidationResult event_validation_result = event_validator.validate();
        // TODO: additional coding is required. validator always returns true.
        if (!event_validation_result.result) {
            // TODO: replace logger
            std::cerr << event_validation_result.error_code << ": "
                      <<  event_validation_result.error_message << std::endl;
            Response response(StatusCode::BAD_REQUEST, ResponseMessage::BAD_REQUEST);
            return response.create_response();
        }
 
        JsonValue body;
        body.WithString(ResponseKey::MESSAGE, ResponseMessage::OK);
        body.WithString(ResponseKey::RESULT, "success...");

        Response response(StatusCode::OK, std::move(body));
        return response.create_response();
    }

    inline auto create_target_handler(const Event& event) -> std::unique_ptr<BaseEventHandler> {
        switch(event.event_type) {
        case EventType::OPTIONS:
            return std::make_unique<DefaultEventHandler>(StatusCode::OK);
        case EventType::GET:
            return std::make_unique<EventHandler>(event);
        default:
            return std::make_unique<ErrorEventHandler>(StatusCode::BAD_REQUEST, ResponseMessage::BAD_REQUEST);
        }
    }
    
    auto handler(const invocation_request& request) -> invocation_response {
        Event event(request);
        EventInitializationResult event_initialization_result = event.initialize();
        if (!event_initialization_result.result) {
            // TODO: replace logger
            std::cerr << event_initialization_result.error_code << ": "
                      <<  event_initialization_result.error_message << std::endl;
            Response response(StatusCode::BAD_REQUEST, ResponseMessage::BAD_REQUEST);
            return response.create_response();
        }
        
        std::unique_ptr<BaseEventHandler> target_handler = create_target_handler(event);
        return target_handler->create_response();
    }
}  // namespace CppSamplesGet
