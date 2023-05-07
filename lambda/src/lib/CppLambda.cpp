#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>

#include "iostream"
#include "iomanip"

#include "CppLambda.h"

namespace CppLambda {

    using namespace aws::lambda_runtime;
    using namespace Aws::Utils::Json;

    Event::Event(const invocation_request& request) noexcept 
            : request(request) {};

    void Event::initialize() noexcept {
        JsonValue payload(request.payload);
        if (!payload.WasParseSuccessful()) {
            std::cerr << "InvalidJSON: Failed to parse input JSON" << std::endl;
            return;
        }
        JsonView pv = payload.View();

        if (pv.ValueExists("httpMethod")) {
            http_method = pv.GetString("httpMethod");
            std::transform(http_method.cbegin(), http_method.cend(), http_method.begin(), toupper);
            if (http_method ==  HttpMethod::OPTIONS) {
                type = EventType::OPTIONS;
            } else if (http_method ==  HttpMethod::GET) {
                type = EventType::GET;
            } else if (http_method == HttpMethod::POST) {
                type = EventType::POST;
            } else {
                type = EventType::OTHERS;
            }
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
    }

    void Event::show() const noexcept {
        std::cout << std::endl;
        std::cout << "Event Parameters" << std::endl;
        std::cout << "================" << std::endl;
        std::cout << "httpMethod: " << http_method
                  << "(type: " << type << ")" << std::endl;
        std::cout << "path: " << path << std::endl;
        std::cout << "headers: " << headers.View().WriteCompact() << std::endl;
        std::cout << "body: " << body.View().WriteCompact() << std::endl;
        std::cout << "query: " << query.View().WriteCompact() << std::endl;
        std::cout << std::endl;
        return;
    }

    EventValidationResult::EventValidationResult(const bool is_valid, std::vector<std::string_view>&& error_messages) noexcept
        : is_valid(is_valid), error_messages(std::move(error_messages)) {}

    void EventValidationResult::show() const noexcept {
        std::cout << std::endl;
        std::cout << "Event Validate Errors" << std::endl;
        std::cout << "=====================" << std::endl;
        std::cout << "     is_valid: " << is_valid << std::endl;
        for (int ii = 0; auto error_message : error_messages) {
            std::cout << std::right << std::setw(3) << ii;
            std::cout << ": ";
            std::cout << error_message << std::endl;
            ii++;
        }
        std::cout << std::endl;
    }
    
    Response::Response(StatusCode status_code, JsonValue&& body) noexcept
        : status_code(status_code), body(std::move(body)) {}

    Response::Response(StatusCode status_code, const std::string& message) noexcept
        : Response(status_code, create_body(message)) {}

    invocation_response Response::create_response() const noexcept {
        JsonValue headers = create_headers();
        JsonValue response;
        response.WithInteger(ResponseKey::STATUS_CODE, static_cast<int>(status_code));
        response.WithString(ResponseKey::HEADERS, headers.View().WriteCompact());
        response.WithString(ResponseKey::BODY, body.View().WriteCompact());
        return invocation_response::success(response.View().WriteCompact(),
                                            ContentType::APPLICATION_JSON);
    }

    inline JsonValue Response::create_body(const std::string& message) {
        JsonValue new_body;
        if (message.size() > 0) {
            new_body.WithString(ResponseKey::MESSAGE, message);
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
    
    DefaultHandler::DefaultHandler(StatusCode status_code, JsonValue&& body) noexcept
        : status_code(status_code), body(std::move(body)) {}

    DefaultHandler::DefaultHandler(StatusCode status_code, const std::string& message) noexcept
        : DefaultHandler(status_code, create_body(message)) {}

    invocation_response DefaultHandler::create_response() const noexcept {
        Response response(status_code, JsonValue(body));
        return response.create_response();
    }

    inline JsonValue DefaultHandler::create_body(const std::string& message) {
        JsonValue new_body;
        if (message.size() > 0) {
            new_body.WithString(ResponseKey::MESSAGE, message);
        }
        return new_body;
    }


}  // namespace CppLambda
