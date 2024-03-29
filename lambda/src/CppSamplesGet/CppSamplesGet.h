#ifndef LAMBDA_SRC_CPP_SAMPLES_GET_HANDLER_H_
#define LAMBDA_SRC_CPP_SAMPLES_GET_HANDLER_H_

#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>

#include<iostream>

#include "AwsLambda.h"
#include "AwsService.h"

namespace CppSamplesGet {
    using namespace AwsLambda;

    class EventValidator final : public BaseEventValidator {
    public:
        explicit EventValidator(const Event& event) noexcept;
        std::tuple<DefaultResult, std::vector<std::string_view>> validate() const noexcept override;

    private:
        const Event& event;        
    };

    class EventHandler final : public BaseEventHandler {
    public:
        EventHandler(const Event& event) noexcept;
        invocation_response create_response() const override;

    private:
        const Event& event;
    };

    invocation_response handler(const invocation_request& request);
}
#endif  // LAMBDA_SRC_CPP_SAMPLES_GET_HANDLER_H_
