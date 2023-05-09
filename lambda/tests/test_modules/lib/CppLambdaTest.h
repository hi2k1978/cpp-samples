#include<iostream>
#include<vector>

#include"gtest/gtest.h"
#include"CppLambda.h"
#include"TestMod.h"

// N: Normal, Q: Ouasi-normal, A: Abnormal
namespace CppLambda {
    TEST(N__lib_CppLambda, BaseReturnResult__test_constructor) {
        BaseReturnResult target(true, ErrorCode::EVENT_INITIALIZATION_ERROR, ErrorMessage::EVENT_INITIALIZATION_ERROR);
        // test
        EXPECT_EQ(target.result, true);
        EXPECT_EQ(target.error_code, ErrorCode::EVENT_INITIALIZATION_ERROR);
        EXPECT_EQ(target.error_message,  ErrorMessage::EVENT_INITIALIZATION_ERROR);
    }

    TEST(N__lib_CppLambda, Event__test_constructor_initialize__only_httpMethod_has_value) {
        JsonValue request_body;
        request_body.WithString("httpMethod", "GET");
        invocation_request request;
        request.payload = request_body.View().WriteCompact();
        Event event(request);
        EventInitializationResult result = event.initialize();
        
        EXPECT_EQ(result.result, true);
        EXPECT_EQ(event.event_type, EventType::GET);
        EXPECT_EQ(event.http_method, "GET");
        EXPECT_EQ(event.path, "");
        EXPECT_EQ(event.headers.View().WriteCompact(), "{}");
        EXPECT_EQ(event.body.View().WriteCompact(), "{}");
        EXPECT_EQ(event.query.View().WriteCompact(), "{}");
    }

    TEST(N__lib_CppLambda, Event__test_constructor_initialize__every_member_variable_has_value) {
        JsonValue request_body;
        request_body.WithString("httpMethod", "GET");
        invocation_request request;
        request.payload = request_body.View().WriteCompact();
        Event event(request);
        EventInitializationResult result = event.initialize();
        
        EXPECT_EQ(result.result, true);
        EXPECT_EQ(event.event_type, EventType::GET);
        EXPECT_EQ(event.http_method, "GET");
        EXPECT_EQ(event.path, "");
        EXPECT_EQ(event.headers.View().WriteCompact(), "{}");
        EXPECT_EQ(event.body.View().WriteCompact(), "{}");
        EXPECT_EQ(event.query.View().WriteCompact(), "{}");
    }

    TEST(N__lib_CppLambda, EventValidationResult__test_constructor) {
        std::vector<std::string_view> validation_error_messages { EventValidationError::TEST, EventValidationError::EXAMPLE};
        EventValidationResult target(true, ErrorCode::EVENT_VALIDATION_ERROR, ErrorMessage::EVENT_VALIDATION_ERROR, std::move(validation_error_messages));
        // test
        EXPECT_EQ(target.result, true);
        EXPECT_EQ(target.error_code, ErrorCode::EVENT_VALIDATION_ERROR);
        EXPECT_EQ(target.error_message,  ErrorMessage::EVENT_VALIDATION_ERROR);
        EXPECT_EQ(target.validation_error_messages.at(0), EventValidationError::TEST);
        EXPECT_EQ(target.validation_error_messages.at(1), EventValidationError::EXAMPLE);
    }

    TEST(N__lib_CppLambda, Response__test_constructor_001__main_constructor_create_response) {
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

    TEST(N__lib_CppLambda, Response__test_constructor_002__delegating_constructor) {
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
        EXPECT_EQ(res_status_code, 400);
        // both stirngs are "{"message":"bad request."}" or some kind.
        EXPECT_EQ(res_body_string, expect_body_string);
    }

    TEST(N__lib_CppLambda, Response__test_constructor_003__delegating_constructor) {
        // StatusCode::OK == 200
        Response response(StatusCode::OK);
        invocation_response target = response.create_response();
        
        const JsonValue payload = JsonValue(target.get_payload());
        const auto payload_view = payload.View();
        const int res_status_code = static_cast<int>(payload_view.GetInteger("statusCode"));
        const JsonValue res_body(payload_view.GetString("body"));
        const std::string res_body_string = res_body.View().WriteCompact();

        // test
        EXPECT_EQ(res_status_code, 200);
        EXPECT_EQ(res_body_string, "{}");
    }

    TEST(N__lib_CppLambda, Response__test_response_headers) {
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

    TEST(N__lib_CppLambda, DefaultHandler__test_constructor_001__main_constructor_create_response) {
        JsonValue body;
        body.WithString("message", "test_constructor_001");
        body.WithString("result", "successful");

        // StatusCode::OK == 200
        DefaultHandler default_handler(StatusCode::OK, std::move(body));
        invocation_response target = default_handler.create_response();

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

    TEST(N__lib_CppLambda, DefaultHandler__test_constructor_002__delegating_constructor) {
        // StatusCode::BAD_REQUEST == 400
        DefaultHandler default_handler(StatusCode::BAD_REQUEST, ResponseMessage::BAD_REQUEST);
        invocation_response target = default_handler.create_response();

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
        EXPECT_EQ(res_status_code, 400);
        // both stirngs are "{"message":"bad request."}" or some kind.
        EXPECT_EQ(res_body_string, expect_body_string);
    }

    TEST(N__lib_CppLambda, DefaultHandler__test_constructor_003__delegating_constructor) {
        // StatusCode::OK == 200
        DefaultHandler default_handler(StatusCode::OK);
        invocation_response target = default_handler.create_response();
        
        const JsonValue payload = JsonValue(target.get_payload());
        const auto payload_view = payload.View();
        const int res_status_code = static_cast<int>(payload_view.GetInteger("statusCode"));
        const JsonValue res_body(payload_view.GetString("body"));
        const std::string res_body_string = res_body.View().WriteCompact();

        // test
        EXPECT_EQ(res_status_code, 200);
        EXPECT_EQ(res_body_string, "{}");
    }

    TEST(N__lib_CppLambda, DefaultHandler__test_response_headers) {
        // StatusCode::BAD_REQUEST == 400
        DefaultHandler default_handler(StatusCode::OK);
        invocation_response target = default_handler.create_response();

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
