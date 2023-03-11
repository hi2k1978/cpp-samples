#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <aws/core/utils/memory/stl/SimpleStringStream.h>
#include<memory>
#include<iostream>
#include<vector>

#include "cpp_lambda.h"

using namespace aws::lambda_runtime;

namespace CppSamplesGet {
    using namespace CppLambda;
    
    // This class is hard-coded. Because it is only used in this source file.
    class GetRequest final : public BaseRequest {
    private:
	const Event& event;
    public:
	GetRequest(const Event& event_) : event(event_) {};
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

    invocation_response lambda_handler(const invocation_request& request)
    {
	Event event(request);
	// event.show();	
	RequestMap request_map;
	request_map.emplace(RequestType::GET, std::make_unique<GetRequest>(event));
	Main main(event.request_type, request_map);
	return main.handler();
    }
}

int main()
{
    run_handler(CppSamplesGet::lambda_handler);
    return 0;
}
