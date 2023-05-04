#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>

#include "iostream"
#include "iomanip"

#include "cpp_lambda.h"

namespace CppLambda {

    using namespace aws::lambda_runtime;
    using namespace Aws::Utils::Json;

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
            headers = pv.GetObject("headers");
        }
        if (pv.ValueExists("body")) {
            if (pv.GetObject("body").IsString()) {
                std::string body_string = pv.GetString("body");
                JsonValue body_json_value(body_string);
                if (body_json_value.WasParseSuccessful()) {
                    body = body_json_value.View();
                }
            } else {
                body = pv.GetObject("body");
            }
        }
        if (pv.ValueExists("queryStringParameters")) {
            query = pv.GetObject("queryStringParameters");
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
        std::cout << "headers: " << headers.WriteCompact() << std::endl;
        std::cout << "body: " << body.WriteCompact() << std::endl;
        std::cout << "query: " << query.WriteCompact() << std::endl;
        std::cout << std::endl;
        return;
    }

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
    
   invocation_response Response::create_response() const noexcept {
        JsonValue headers;
        headers.WithString(CorsKey::ALLOW_ORIGIN, CorsValue::ALLOW_ORIGIN);
        headers.WithString(CorsKey::ALLOW_METHODS, CorsValue::ALLOW_METHODS);
        headers.WithString(CorsKey::ALLOW_HEADERS, CorsValue::ALLOW_HEADERS);
        
        JsonValue response;
        response.WithInteger(ResponseKey::STATUS_CODE, static_cast<int>(status_code));
        response.WithString(ResponseKey::HEADERS, headers.View().WriteCompact());
        response.WithString(ResponseKey::BODY, body.View().WriteCompact());
        return invocation_response::success(response.View().WriteCompact(),
                                            ContentType::APPLICATION_JSON);
    }

    invocation_response DefaultHandler::create_response() const noexcept {
        JsonValue body;
        if (message.size() > 0) {
            body.WithString(ResponseKey::MESSAGE, message);
        }
        Response response(status_code, std::move(body));
        return response.create_response();
    }

    invocation_response ErrorHandler::create_response() const noexcept {
        JsonValue body;
        if (message.size() > 0) {
            body.WithString(ResponseKey::MESSAGE, message);
        }
        Response response(status_code, std::move(body));
        return response.create_response();
    }

}  // namespace CppLambda
