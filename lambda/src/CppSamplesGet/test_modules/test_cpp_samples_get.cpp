#include"gtest/gtest.h"
#include"cpp_samples_get.h"

namespace CppSamplesGet {
    TEST(CppSamplesGet, hoge) {
        using namespace CppLambda;
        using namespace Aws::Utils::Json;
        std::cout << "\n\nhoge\n\n" << std::endl;
        JsonValue body;
        body.WithString(ResponseKey::MESSAGE, ResponseMessage::OK);
        body.WithString(ResponseKey::RESULT, "success???");
        std::cout << "body: " << body.View().WriteCompact() << std::endl;

        EXPECT_EQ(1, 1);
    }
}
