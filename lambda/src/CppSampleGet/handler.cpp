#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <aws/core/utils/memory/stl/SimpleStringStream.h>
#include<memory>
#include<iostream>
#include<vector>
#include "response.h"

using namespace aws::lambda_runtime;

namespace CppLambda {

    class GetRequest final : public BaseRequest {
    private:
	Event* event;
    public:
	GetRequest(Event* event_) : event(event_) {};
	invocation_response handler() const override;
    };

    invocation_response GetRequest::handler() const {

	using namespace Aws::Utils::Json;

	StatusCode status_code = StatusCode::OK;
	JsonValue body;
	body.WithString("message", "ok");
	body.WithString("httpMethod", "get");

	Response response(std::move(status_code), std::move(body));
	return response.get();
    }
}

invocation_response lambda_handler(invocation_request const& request)
{
    auto event = std::make_unique<CppLambda::Event>(request);
	
    std::map<std::string, std::unique_ptr<CppLambda::BaseRequest>> request_map;
    request_map.emplace(HTTP_METHOD_GET, std::make_unique<CppLambda::GetRequest>(event.get()));

    CppLambda::BaseRequest *target = request_map.contains(event->http_method)
	? (request_map.at(event->http_method)).get()
	: nullptr;

    if (target == nullptr){
	// 例外を搬送に書き変える。
	auto invalid_request = std::make_unique<CppLambda::InvalidRequest>(
	    CppLambda::StatusCode::BAD_REQUEST, "httpMethod is not found.");
	target = dynamic_cast<CppLambda::BaseRequest*>(invalid_request.get());
    }
    return target->handler();
}


int main()
{
    run_handler(lambda_handler);
    return 0;
}
