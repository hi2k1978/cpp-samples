// Copyright 2023 hi2k1978
#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>

#include<iostream>
#include<memory>
#include<vector>

#include "CppSamplesPost.h"

using namespace aws::lambda_runtime;

int main() {
    run_handler(CppSamplesPost::handler);
    return 0;
}












