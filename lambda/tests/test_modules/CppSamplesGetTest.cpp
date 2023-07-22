// -*- mode: cc-mode; compile-command: "make -C ../../ build test ARGS=--gtest_filter=*_CppSamplesGet*.*" -*-
#include"gtest/gtest.h"
#include"CppSamplesGet.h"

namespace CppSamplesGet {
    TEST(CppSamplesGet, hoge) {
        using namespace CppLambda;
        using namespace Aws::Utils::Json;
        JsonValue body;
        body.WithString(ResponseKey::MESSAGE, ResponseMessage::OK);
        body.WithString(ResponseKey::RESULT, "success???");
        // std::cout << "body: " << body.View().WriteCompact() << std::endl;

        EXPECT_EQ(1, 1);
    }
}
