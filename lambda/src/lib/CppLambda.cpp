#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>

#include "iostream"
#include "iomanip"

#include "CppLambda.h"

namespace CppLambda {

    using namespace aws::lambda_runtime;
    using JsonValue = Aws::Utils::Json::JsonValue;
    using JsonView = Aws::Utils::Json::JsonView;
    // using namespace Aws::Utils::Json;

    DefaultResult::DefaultResult(const bool is_success,
                                std::string_view&& error_code,
                                std::string_view&& error_message) noexcept
        : is_success(is_success), error_code(std::move(error_code)), error_message(std::move(error_message)) {}

    DefaultResult::DefaultResult(const bool is_success) noexcept
        : DefaultResult(is_success, ErrorCode::NONE, ErrorMessage::NONE) {}

    Event::Event(const invocation_request& request) noexcept 
            : request(request) {};

    DefaultResult Event::initialize() noexcept {
        JsonValue payload(request.payload);
        if (!payload.WasParseSuccessful()) {
            std::cerr << "InvalidJSON: Failed to parse input JSON" << std::endl;
            return DefaultResult(false,
                                             ErrorCode::EVENT_INITIALIZATION_ERROR,
                                             ErrorMessage::EVENT_INITIALIZATION_ERROR);
        }
        JsonView pv = payload.View();

        if (pv.ValueExists("httpMethod")) {
            http_method = pv.GetString("httpMethod");
            std::transform(http_method.cbegin(), http_method.cend(), http_method.begin(), toupper);
            if (http_method ==  HttpMethod::OPTIONS) {
                event_type = EventType::OPTIONS;
            } else if (http_method ==  HttpMethod::GET) {
                event_type = EventType::GET;
            } else if (http_method == HttpMethod::POST) {
                event_type = EventType::POST;
            } else {
                event_type = EventType::OTHERS;
            }
        } else {
            std::cerr << "InvalidJSON: httpMethod does not exist." << std::endl;
            return DefaultResult(false,
                                 ErrorCode::EVENT_INITIALIZATION_ERROR,
                                 ErrorMessage::EVENT_INITIALIZATION_ERROR);
        }
        if (pv.ValueExists("path")) {
            path = pv.GetString("path");
        }
        if (pv.ValueExists("headers")) {
            headers = pv.GetObject("headers").Materialize();
        }
        if (pv.ValueExists("body")) {
            if (pv.GetObject("body").IsString()) {
                std::string body_string = pv.GetString("body");
                JsonValue body_json_value(body_string);
                if (body_json_value.WasParseSuccessful()) {
                    body = body_json_value;
                }
            } else {
                body = pv.GetObject("body").Materialize();
            }
        }
        if (pv.ValueExists("queryStringParameters")) {
            query = pv.GetObject("queryStringParameters").Materialize();
        }
        // show();
        return DefaultResult(true, ErrorCode::NONE, ErrorMessage::NONE);
   }

    void Event::show() const noexcept {
        std::cout << std::endl;
        std::cout << "Event Parameters" << std::endl;
        std::cout << "================" << std::endl;
        std::cout << "httpMethod: " << http_method
                  << "(type: " << event_type << ")" << std::endl;
        std::cout << "path: " << path << std::endl;
        std::cout << "headers: " << headers.View().WriteCompact() << std::endl;
        std::cout << "body: " << body.View().WriteCompact() << std::endl;
        std::cout << "query: " << query.View().WriteCompact() << std::endl;
        std::cout << std::endl;
        return;
    }
    
    Response::Response(const StatusCode status_code, JsonValue&& body) noexcept
        : status_code(status_code), body(std::move(body)) {}

    Response::Response(const StatusCode status_code, std::string&& message) noexcept
        : Response(status_code, create_body(std::move(message))) {}

    Response::Response(const StatusCode status_code) noexcept
        : Response(status_code, JsonValue()) {}

    invocation_response Response::create_response() const noexcept {
        JsonValue headers = create_headers();
        JsonValue response;
        response.WithInteger(ResponseKey::STATUS_CODE, static_cast<int>(status_code));
        response.WithString(ResponseKey::HEADERS, headers.View().WriteCompact());
        response.WithString(ResponseKey::BODY, body.View().WriteCompact());
        return invocation_response::success(response.View().WriteCompact(),
                                            ContentType::APPLICATION_JSON);
    }

    inline JsonValue Response::create_body(std::string&& message) {
        JsonValue new_body;
        if (message.size() > 0) {
            new_body.WithString(ResponseKey::MESSAGE, std::move(message));
        }
        return new_body;
    }

    JsonValue Response::create_headers() const noexcept {
        JsonValue new_headers;
        new_headers.WithString(CorsKey::ACCESS_CONTROL_ALLOW_ORIGIN, CorsValue::ACCESS_CONTROL_ALLOW_ORIGIN);
        new_headers.WithString(CorsKey::ACCESS_CONTROL_ALLOW_METHODS, CorsValue::ACCESS_CONTROL_ALLOW_METHODS);
        new_headers.WithString(CorsKey::ACCESS_CONTROL_ALLOW_HEADERS, CorsValue::ACCESS_CONTROL_ALLOW_HEADERS);
        return new_headers;
    }
    
    DefaultEventHandler::DefaultEventHandler(const StatusCode status_code, JsonValue&& body) noexcept
        : status_code(status_code), body(std::move(body)) {}

    DefaultEventHandler::DefaultEventHandler(const StatusCode status_code, std::string&& message) noexcept
        : DefaultEventHandler(status_code, create_body(std::move(message))) {}

    DefaultEventHandler::DefaultEventHandler(const StatusCode status_code) noexcept
        : DefaultEventHandler(status_code, JsonValue()) {}

    invocation_response DefaultEventHandler::create_response() const noexcept {
        Response response(status_code, JsonValue(body));
        return response.create_response();
    }

    inline JsonValue DefaultEventHandler::create_body(std::string&& message) {
        JsonValue new_body;
        if (message.size() > 0) {
            new_body.WithString(ResponseKey::MESSAGE, std::move(message));
        }
        return new_body;
    }


}  // namespace CppLambda
