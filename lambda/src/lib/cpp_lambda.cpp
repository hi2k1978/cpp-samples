#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>

#include "request_types.h"
#include "response_types.h"
#include "cpp_lambda.h"

namespace CppLambda {

    using namespace aws::lambda_runtime;
    using namespace Aws::Utils::Json;

    Event::Event(invocation_request const& request) {
        JsonValue payload(request.payload);
        if (!payload.WasParseSuccessful()) {
            std::cerr << "InvalidJSON: Failed to parse input JSON" << std::endl;
            return;
        }
        JsonView pv = payload.View();

        if (pv.ValueExists("httpMethod")) {
            http_method = pv.GetString("httpMethod");
            std::transform(http_method.cbegin(), http_method.cend(), http_method.begin(), toupper);
            if (http_method ==  HttpMethod::GET) {
                request_type = RequestType::GET;
            } else if (http_method == HttpMethod::POST) {
                request_type = RequestType::POST;
            } else {
                request_type = RequestType::OTHERS;
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

    void Event::show() const {
        std::cout << std::endl;
        std::cout << "Event Parameters" << std::endl;
        std::cout << "================" << std::endl;
        std::cout << "httpMethod: " << http_method
                  << "(request_type: " << request_type << ")" << std::endl;
        std::cout << "path: " << path << std::endl;
        std::cout << "headers: " << headers.WriteCompact() << std::endl;
        std::cout << "body: " << body.WriteCompact() << std::endl;
        std::cout << "query: " << query.WriteCompact() << std::endl;
        std::cout << std::endl;
        return;
    }

    invocation_response Response::get() const {
        JsonValue response;
        response.WithInteger("statusCode", static_cast<int>(status_code));
        response.WithString("body", body.View().WriteCompact());
        return invocation_response::success(response.View().WriteCompact(),
                                            ContentType::APPLICATION_JSON);
    }

    invocation_response InvalidRequestHandler::getResponse() const {
        JsonValue body;
        body.WithString("message", message);
        Response response(status_code, std::move(body));
        return response.get();
    }
}  // namespace CppLambda
