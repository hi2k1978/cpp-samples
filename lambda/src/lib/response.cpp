#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>

#include "response.h"

using namespace aws::lambda_runtime;

namespace CppLambda {

    using namespace Aws::Utils::Json;
    
    Response::Response(StatusCode status_code_, JsonValue body_)
	: status_code(std::move(status_code_)), body(std::move(body_)) {}

    invocation_response Response::get() const {
	
	JsonValue response;
	response.WithInteger("statusCode", static_cast<int>(status_code));
	response.WithString("body", body.View().WriteCompact());
	return invocation_response::success(response.View().WriteCompact(), CONTENT_TYPE_APPLICATION_JSON);	
    }

}
