#ifndef LAMBDA_SRC_CPP_SAMPLES_GET_HANDLER_H_
#define LAMBDA_SRC_CPP_SAMPLES_GET_HANDLER_H_

#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>

#include<iostream>

#include "CppLambda.h"

namespace CppSamplesGet {
    using namespace CppLambda;

    class GetEventValidator final : public BaseEventValidator {
    public:
        explicit GetEventValidator(const Event& event) noexcept
            : event(event) {}
        EventValidationResult validate() const noexcept override;

    private:
        const Event& event;        
    };

    class GetHandler final : public BaseHandler {
    public:
        GetHandler(const Event& event) noexcept : event(event) {}
        invocation_response create_response() const override;

    private:
        const Event& event;
    };

    invocation_response handler(const invocation_request& request);
}
#endif  // LAMBDA_SRC_CPP_SAMPLES_GET_HANDLER_H_
