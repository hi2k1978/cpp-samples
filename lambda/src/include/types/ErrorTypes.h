#ifndef LAMBDA_SRC_INCLUDE_TYPES_ERROR_TYPES_H_
#define LAMBDA_SRC_INCLUDE_TYPES_ERROR_TYPES_H_

#include<iostream>

namespace CppLambda {

    namespace ErrorCode {
        static constexpr auto EVENT_VALIDATION_ERROR = "E000001"; 
        static constexpr auto ERROR = "E999999"; 
    }
    
    namespace EventValidationError {
        static constexpr auto TEST = "This is an error test.";
    }

    namespace RunTimeError {
        static constexpr auto EVENT_VALIDATION_ERROR = "Event validation is failed.";
    }
    
}  // namespace CppLambda
#endif  // LAMBDA_SRC_INCLUDE_TYPES_ERROR_TYPES_H_
