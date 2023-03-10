#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>

#include "response.h"

using namespace aws::lambda_runtime;

namespace CppLambda {

    using namespace Aws::Utils::Json;

    Event::Event(invocation_request const& request_){
	JsonValue payload(request_.payload);
	if (!payload.WasParseSuccessful()) {
	    std::cerr << "InvalidJSON: Failed to parse input JSON" << std::endl;
	    return;
	}
	JsonView pv = payload.View();

	if (pv.ValueExists("httpMethod")) {
	    std::string http_method_ = pv.GetString("httpMethod");
	    std::transform(http_method_.cbegin(), http_method_.cend(), http_method_.begin(), toupper);
	    http_method = http_method_;
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
    }

    void Event::show() const {
	std::cout << std::endl << std::endl;
	std::cout << "Event Parameters" << std::endl;
	std::cout << "================" << std::endl;
	std::cout << "httpMethod: " << http_method << std::endl;
	std::cout << "path: " << path << std::endl;
	std::cout << "headers: " << headers.WriteCompact() << std::endl;
	std::cout << "body: " << body.WriteCompact() << std::endl;
	std::cout << "query: " << query.WriteCompact() << std::endl;
	std::cout << std::endl << std::endl;
	return;
    }
    
    Response::Response(StatusCode status_code_, JsonValue body_)
	: status_code(std::move(status_code_)), body(std::move(body_)) {}

    invocation_response Response::get() const {
	
	JsonValue response;
	response.WithInteger("statusCode", static_cast<int>(status_code));
	response.WithString("body", body.View().WriteCompact());
	return invocation_response::success(response.View().WriteCompact(), CONTENT_TYPE_APPLICATION_JSON);	
    }


    invocation_response InvalidRequest::handler() const {
	JsonValue body;
	body.WithString("error_message", error_message);

	auto response = std::make_unique<CppLambda::Response>(std::move(status_code), std::move(body));
	return response->get();	
    }
}
