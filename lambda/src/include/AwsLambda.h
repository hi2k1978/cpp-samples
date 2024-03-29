#ifndef LAMBDA_SRC_INCLUDE_CPP_LAMBDA_H_
#define LAMBDA_SRC_INCLUDE_CPP_LAMBDA_H_

#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>

#include<iostream>
#include<map>
#include<memory>
#include<string>
#include<utility>
#include<type_traits>

#ifdef BUILD_TYPE_RELEASE // build_type: Release
#include "build_types/BuildTypeRelease.h"
#else // build_type: Debug
#include "build_types/BuildTypeDebug.h"
#endif

#include "types/ErrorTypes.h"
#include "types/InvocationTypes.h"


namespace AwsLambda {
    
    using namespace aws::lambda_runtime;
    using namespace Aws::Utils::Json;

    struct DefaultResult {
        explicit DefaultResult(const bool is_success,
                                  std::string_view&& error_code,
                                  std::string_view&& error_message) noexcept;
        DefaultResult(const bool is_success) noexcept;
        
        const bool is_success;
        const std::string_view error_code;
        const std::string_view  error_message;
    };  // struct DefaultResult


    struct Event {
        explicit Event(const invocation_request& request) noexcept;
        DefaultResult initialize() noexcept;
        void show() const noexcept;

        EventType event_type;
        std::string http_method;
        std::string path;
        JsonValue headers;
        JsonValue body;
        JsonValue query;

    private:
        const invocation_request& request;
    };

    class BaseEventValidator {
    public:
        virtual std::tuple<DefaultResult, std::vector<std::string_view>> validate() const noexcept = 0;
    };

    class Response {
    public:
        Response(const StatusCode status_code, JsonValue&& body) noexcept;
        Response(const StatusCode status_code, std::string&& message) noexcept;
        Response(const StatusCode status_code) noexcept;
        invocation_response create_response() const noexcept;        

    private:
        inline JsonValue create_body(std::string&& message);
        JsonValue create_headers() const noexcept;

        const StatusCode status_code;
        const JsonValue body;
    };
    
    class BaseEventHandler {
    public:
        virtual invocation_response create_response() const = 0;
    };

    class DefaultEventHandler : public BaseEventHandler {
    public:
        DefaultEventHandler(const StatusCode status_code, JsonValue&& body) noexcept;
        DefaultEventHandler(const StatusCode status_code, std::string&& message) noexcept;
        DefaultEventHandler(const StatusCode status_code) noexcept;
        invocation_response create_response() const noexcept override;
    private:
        inline JsonValue create_body(std::string&& message);

        const StatusCode status_code;
        const JsonValue body;
    };
    using ErrorEventHandler = DefaultEventHandler;

}  // namespace AwsLambda
#endif  // LAMBDA_SRC_INCLUDE_CPP_LAMBDA_H_
