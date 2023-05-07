#include<iostream>
#include<vector>

#include"gtest/gtest.h"
#include"CppLambda.h"
#include"TestMod.h"


namespace CppLambda {
    TEST(lib__CppLambda, BaseReturnResult__test_constructor) {
        BaseReturnResult target(true, ErrorCode::EVENT_INITIALIZATION_ERROR, ErrorMessage::EVENT_INITIALIZATION_ERROR);
        // dry test
        EXPECT_EQ(target.result, true);
        EXPECT_EQ(target.error_code, ErrorCode::EVENT_INITIALIZATION_ERROR);
        EXPECT_EQ(target.error_message,  ErrorMessage::EVENT_INITIALIZATION_ERROR);
    }

    TEST(lib__CppLambda, Response__test_constructor_001) {
        JsonValue body;
        body.WithString("message", "test_constructor_001");
        body.WithString("result", "successful");

        // StatusCode::OK == 200
        Response response(StatusCode::OK, std::move(body));
        invocation_response target = response.create_response();

        const JsonValue payload = JsonValue(target.get_payload());
        const auto payload_view = payload.View();
        const int res_status_code = static_cast<int>(payload_view.GetInteger("statusCode"));
        const JsonValue res_body(payload_view.GetString("body"));
        const std::string res_body_string = res_body.View().WriteCompact();

        // create expect
        JsonValue expect_body;
        expect_body.WithString("message", "test_constructor_001");
        expect_body.WithString("result", "successful");
        const std::string expect_body_string = expect_body.View().WriteCompact();

        // test
        EXPECT_EQ(res_status_code, 200);
        EXPECT_EQ(res_body_string, expect_body_string);
    }

    TEST(lib__CppLambda, Response__test_constructor_002) {
        // StatusCode::BAD_REQUEST == 400
        Response response(StatusCode::BAD_REQUEST, ResponseMessage::BAD_REQUEST);
        invocation_response target = response.create_response();

        const JsonValue payload = JsonValue(target.get_payload());
        const auto payload_view = payload.View();
        const int res_status_code = static_cast<int>(payload_view.GetInteger("statusCode"));
        const JsonValue res_body(payload_view.GetString("body"));
        const std::string res_body_string = res_body.View().WriteCompact();

        // create expect
        JsonValue expect_body;
        expect_body.WithString("message", "bad request.");
        const std::string expect_body_string = expect_body.View().WriteCompact();

        // test
        // EXPECT_EQ(static_cast<StatusCode>(res_status_code), static_cast<StatusCode>(400));
        EXPECT_EQ(res_status_code, 400);
        // both stirngs are "{"message":"bad request."}" or some kind.
        EXPECT_EQ(res_body_string, expect_body_string);
    }

    TEST(lib__CppLambda, Response__test_constructor_003) {
        // StatusCode::OK == 200
        Response response(StatusCode::OK);
        invocation_response target = response.create_response();
        
        const JsonValue payload = JsonValue(target.get_payload());
        const auto payload_view = payload.View();
        const int res_status_code = static_cast<int>(payload_view.GetInteger("statusCode"));
        const std::string res_body_string = payload_view.GetString("body");

        // test
        EXPECT_EQ(res_status_code, 200);
        EXPECT_EQ(res_body_string, "{}");
    }

    TEST(lib__CppLambda, Response__test_headers) {
        // StatusCode::BAD_REQUEST == 400
        Response response(StatusCode::OK);
        invocation_response target = response.create_response();

        const JsonValue payload = JsonValue(target.get_payload());
        const auto payload_view = payload.View();
        const JsonValue res_headers(payload_view.GetString("headers"));
        const std::string res_headers_string = res_headers.View().WriteCompact();

        // create expect
        JsonValue expect_headers;
        expect_headers.WithString(CorsKey::ACCESS_CONTROL_ALLOW_ORIGIN, CorsValue::ACCESS_CONTROL_ALLOW_ORIGIN);
        expect_headers.WithString(CorsKey::ACCESS_CONTROL_ALLOW_METHODS, CorsValue::ACCESS_CONTROL_ALLOW_METHODS);
        expect_headers.WithString(CorsKey::ACCESS_CONTROL_ALLOW_HEADERS, CorsValue::ACCESS_CONTROL_ALLOW_HEADERS);
        const std::string expect_headers_string = expect_headers.View().WriteCompact();

        // test
        EXPECT_EQ(res_headers_string, expect_headers_string);
    }

}
