#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>

#include "response.h"

using namespace aws::lambda_runtime;

namespace CppLambda {

    using namespace Aws::Utils::Json;
    
    Response::Response(JsonValue&& body_) : body(std::move(body_)) {}

    invocation_response Response::get() const {
	return invocation_response::success(body.View().WriteCompact(), CONTENT_TYPE_JSON);	
    }

}
