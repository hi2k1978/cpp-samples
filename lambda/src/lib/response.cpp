#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <sstream>
#include "response.h"

using namespace aws::lambda_runtime;
using namespace aws::http;

namespace CppLambda {

    using namespace Aws::Utils::Json;
    
    Response::Response(int status_code_, JsonValue body_)
	: status_code(std::move(status_code_)), body(std::move(body_)) {}

    invocation_response Response::get() const {
	
	std::ostringstream status_code_stream;
	status_code_stream << status_code;
	
	JsonValue response;
	response.WithString("statusCode", status_code_stream.str());
	response.WithString("body", body.View().WriteCompact());
	return invocation_response::success(response.View().WriteCompact(), CONTENT_TYPE_JSON);	
    }

}
