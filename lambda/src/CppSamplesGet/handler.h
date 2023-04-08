#ifndef LAMBDA_SRC_CPP_SAMPLES_GET_HANDLER_H_
#define LAMBDA_SRC_CPP_SAMPLES_GET_HANDLER_H_

#include<iostream>

#include "cpp_lambda.h"

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

    class GetEventHandler final : public BaseEventHandler {
    public:
        GetEventHandler(const Event& event) noexcept : event(event) {}
        invocation_response get_response() const noexcept override;

    private:
        const Event& event;
    };
}
#endif  // LAMBDA_SRC_CPP_SAMPLES_GET_HANDLER_H_
