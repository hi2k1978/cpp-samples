#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>
// #include <aws/core/utils/memory/stl/SimpleStringStream.h>

#include<iostream>
#include<memory>
#include<vector>

#include "CppSamplesPost.h"

using namespace aws::lambda_runtime;

namespace CppSamplesPost {
    using namespace CppLambda;

    GetEventValidator::GetEventValidator(const Event& event) noexcept
        : event(event) {}

    auto GetEventValidator::validate() const noexcept -> EventValidationResult {
        std::vector<std::string_view> error_messages;
        error_messages.push_back(EventValidationError::TEST);

        bool is_valid = true;
        EventValidationResult result(is_valid, ErrorCode::EVENT_VALIDATION_ERROR, std::move(error_messages));
        return result;
    }

    GetHandler::GetHandler(const Event& event) noexcept : event(event) {}

    auto GetHandler::create_response() const -> invocation_response {
        using namespace Aws::Utils::Json;

        GetEventValidator event_validator(event);
        EventValidationResult event_validation_result = event_validator.validate();
        // TODO: additional coding is required. validator always returns true.
        if (!event_validation_result.is_valid) {
            std::cerr << RunTimeError::EVENT_VALIDATION_ERROR << std::endl;
            event_validation_result.show();
            Response response(StatusCode::BAD_REQUEST, ResponseMessage::BAD_REQUEST);
            return response.create_response();
        }
 
        JsonValue body;
        body.WithString(ResponseKey::MESSAGE, ResponseMessage::OK);
        body.WithString(ResponseKey::RESULT, "success...");

        Response response(StatusCode::OK, std::move(body));
        return response.create_response();
    }

    inline auto create_target_handler(const Event& event) -> std::unique_ptr<BaseHandler> {
        switch(event.event_type) {
        case EventType::OPTIONS:
            return std::make_unique<DefaultHandler>(StatusCode::OK, ResponseMessage::NONE);
        case EventType::GET:
            return std::make_unique<GetHandler>(event);
        default:
            return std::make_unique<ErrorHandler>(StatusCode::BAD_REQUEST, ResponseMessage::BAD_REQUEST);
        }
    }
    
    auto handler(const invocation_request& request) -> invocation_response {
        Event event(request);
        event.initialize();
        std::unique_ptr<BaseHandler> target_handler = create_target_handler(event);
        return target_handler->create_response();
    }
}  // namespace CppSamplesPost
