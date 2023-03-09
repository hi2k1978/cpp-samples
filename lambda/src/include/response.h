#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>

#define CONTENT_TYPE_JSON "application/json"

using namespace aws::lambda_runtime;

namespace CppLambda {

    using namespace Aws::Utils::Json;
    
    class Response{
    private:
	JsonValue&& body;
	
    public:
	Response(JsonValue&& body_);
	invocation_response get() const;
	
    };
}
