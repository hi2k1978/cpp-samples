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

#ifdef STAGE_MAIN // stage: main
#include "stages/StageMain.h"
#else // stage: develop
#include "stages/StageDevelop.h"
#endif

#include "types/ErrorTypes.h"
#include "types/InvocationTypes.h"


namespace CppLambda {
    
    using namespace aws::lambda_runtime;
    using namespace Aws::Utils::Json;

    struct BaseReturnResult {
        explicit BaseReturnResult(const bool is_valid,
                                  std::string_view&& error_code,
                                  std::string_view&& error_message) noexcept;
        const bool is_valid;
        const std::string_view error_code;
        const std::string_view  error_message;
    };  // struct BaseReturnResult

    using EventInitializationResult = BaseReturnResult;

    struct Event {
        explicit Event(const invocation_request& request) noexcept;
        EventInitializationResult initialize() noexcept;
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

    struct EventValidationResult {
        explicit EventValidationResult(const bool is_valid,
                                  std::string_view&& error_code,
                                  std::string_view&& error_message,
                                  std::vector<std::string_view>&& validation_error_messages) noexcept;
        const bool is_valid;
        const std::string_view error_code;
        const std::string_view error_message;
        const std::vector<std::string_view>  validation_error_messages;
    };  // struct EventValidateResult
    
    class BaseEventValidator {
    public:
        virtual EventValidationResult validate() const noexcept = 0;
    };

    class Response {
    public:
        Response(StatusCode status_code, JsonValue&& body) noexcept;
        Response(StatusCode status_code, const std::string& message) noexcept;
        invocation_response create_response() const noexcept;        

    private:
        inline JsonValue create_body(const std::string& message);
        JsonValue create_headers() const noexcept;

        const StatusCode status_code;
        const JsonValue body;
    };
    
    class BaseHandler {
    public:
        virtual invocation_response create_response() const = 0;
    };

    class DefaultHandler : public BaseHandler {
    public:
        DefaultHandler(StatusCode status_code, JsonValue&& body) noexcept;
        DefaultHandler(StatusCode status_code, const std::string& message) noexcept;
        invocation_response create_response() const noexcept override;
    private:
        inline JsonValue create_body(const std::string& message);

        const StatusCode status_code;
        const JsonValue body;
    };
    using ErrorHandler = DefaultHandler;

}  // namespace CppLambda
#endif  // LAMBDA_SRC_INCLUDE_CPP_LAMBDA_H_
