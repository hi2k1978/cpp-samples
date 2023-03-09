#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>
#include <aws/core/utils/memory/stl/SimpleStringStream.h>
#include<memory>

#include "response.h"

using namespace aws::lambda_runtime;


invocation_response lambda_handler(invocation_request const& request)
{

    using namespace Aws::Utils::Json;

    JsonValue json(request.payload);
    if (!json.WasParseSuccessful()) {
        return invocation_response::failure("Failed to parse input JSON", "InvalidJSON");
    }

    auto v = json.View();
    Aws::SimpleStringStream ss;

    if (v.ValueExists("body") && v.GetObject("body").IsString()) {
        auto body = v.GetString("body");
        JsonValue body_json(body);

        if (body_json.WasParseSuccessful()) {
            auto body_v = body_json.View();
            ss << (body_v.ValueExists("time") && body_v.GetObject("time").IsString() ? body_v.GetString("time") : "");
        }
    }
    ss << ", ";

    if (v.ValueExists("queryStringParameters")) {
        auto query_params = v.GetObject("queryStringParameters");
        ss << (query_params.ValueExists("name") && query_params.GetObject("name").IsString()
                   ? query_params.GetString("name")
                   : "")
           << " of ";
        ss << (query_params.ValueExists("city") && query_params.GetObject("city").IsString()
                   ? query_params.GetString("city")
                   : "")
           << ". ";
    }

    if (v.ValueExists("headers")) {
        auto headers = v.GetObject("headers");
        ss << "Happy "
           << (headers.ValueExists("day") && headers.GetObject("day").IsString() ? headers.GetString("day") : "")
           << "!";
    }


    JsonValue body, bodyJsonValue;

    body.WithString("statusCode", "200");

    bodyJsonValue.WithString("message", "ok");
    bodyJsonValue.WithString("result", ss.str());
    body.WithString("body", bodyJsonValue.View().WriteCompact());

    auto response = std::make_unique<CppLambda::Response>(std::move(body));
    return response->get();
}


int main()
{
    run_handler(lambda_handler);
    return 0;
}
