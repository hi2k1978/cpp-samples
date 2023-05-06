#ifndef LAMBDA_SRC_INCLUDE_TYPES_ERROR_TYPES_H_
#define LAMBDA_SRC_INCLUDE_TYPES_ERROR_TYPES_H_

#include<iostream>

namespace CppLambda {

    namespace EventValidationError {
        static constexpr auto TEST = "This is a test error message.";
    } // namespace VALIDATE_ERROR

    namespace RunTimeError {
        static constexpr auto EVENT_VALIDATION_ERROR = "Event validation is failed.";
    }  // namespace HttpMethod
    
}  // namespace CppLambda
#endif  // LAMBDA_SRC_INCLUDE_TYPES_ERROR_TYPES_H_
