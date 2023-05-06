#include"gtest/gtest.h"
#include"CppSamplesPost.h"

namespace CppSamplesPost {
    TEST(CppSamplesPost, test2) {
        using namespace CppLambda;
        using namespace Aws::Utils::Json;
        JsonValue body;
        body.WithString(ResponseKey::MESSAGE, ResponseMessage::OK);
        body.WithString(ResponseKey::RESULT, "success???");
        std::cout << "body: " << body.View().WriteCompact() << std::endl;

        EXPECT_EQ(1, 1);
    }
}
