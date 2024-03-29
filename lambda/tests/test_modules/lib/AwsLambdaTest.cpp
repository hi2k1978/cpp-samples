// -*- mode: cc-mode; compile-command: "make -C ../../../ build test ARGS=--gtest_filter=lib_AwsLambda.*" -*-
#include<iostream>
// #include<vector>

#include"gmock/gmock.h"
#include"gtest/gtest.h"
#include"AwsLambda.h"
#include"TestLambda.h"
using ::testing::AtLeast;

namespace AwsLambda {
    TEST(lib_AwsLambda, N_DefaultResult_TestConstructor) {
        DefaultResult result(true, ErrorCode::EVENT_INITIALIZATION_ERROR, ErrorMessage::EVENT_INITIALIZATION_ERROR);
        // test
        EXPECT_EQ(result.is_success, true);
        EXPECT_EQ(result.error_code, ErrorCode::EVENT_INITIALIZATION_ERROR);
        EXPECT_EQ(result.error_message,  ErrorMessage::EVENT_INITIALIZATION_ERROR);
    }

    TEST(lib_AwsLambda, N_Event_TestConstructorInit_OnlyHttpMethodHasValue) {
        JsonValue request_body;
        request_body.WithString("httpMethod", "GET");
        invocation_request request;
        request.payload = request_body.View().WriteCompact();
        Event event(request);
        DefaultResult result = event.initialize();
        
        EXPECT_EQ(result.is_success, true);
        EXPECT_EQ(event.event_type, EventType::GET);
        EXPECT_EQ(event.http_method, "GET");
        EXPECT_EQ(event.path, "");
        EXPECT_EQ(event.headers.View().WriteCompact(), "{}");
        EXPECT_EQ(event.body.View().WriteCompact(), "{}");
        EXPECT_EQ(event.query.View().WriteCompact(), "{}");
    }

    // WIP
    TEST(lib_AwsLambda, N_Event_TestConstructorInitialize_EveryMemberVariableHasValue) {
        JsonValue request_body;
        request_body.WithString("httpMethod", "GET");
        invocation_request request;
        request.payload = request_body.View().WriteCompact();
        Event event(request);
        DefaultResult result = event.initialize();
        
        EXPECT_EQ(result.is_success, true);
        EXPECT_EQ(event.event_type, EventType::GET);
        EXPECT_EQ(event.http_method, "GET");
        EXPECT_EQ(event.path, "");
        EXPECT_EQ(event.headers.View().WriteCompact(), "{}");
        EXPECT_EQ(event.body.View().WriteCompact(), "{}");
        EXPECT_EQ(event.query.View().WriteCompact(), "{}");
    }

    TEST(lib_AwsLambda, Q_Event_TestConstructorInit_InvalidPayload_RequestPayloadIsNotJsonFormatString) {
        invocation_request request;
        request.payload = "invalid payload: not a json format";
        Event event(request);
        DefaultResult result = event.initialize();
        
        EXPECT_EQ(result.is_success, false);
        EXPECT_EQ(result.error_code, ErrorCode::EVENT_INITIALIZATION_ERROR);
        EXPECT_EQ(result.error_message, ErrorMessage::EVENT_INITIALIZATION_ERROR);
    }

    TEST(lib_AwsLambda, Q_Event_TestConstructorInit_InvalidPayload_RequestPayloadHasNoHttpMethodKey) {
        JsonValue request_body;
        invocation_request request;
        request.payload = request_body.View().WriteCompact();
        Event event(request);
        DefaultResult result = event.initialize();
        
        EXPECT_EQ(result.is_success, false);
        EXPECT_EQ(result.error_code, ErrorCode::EVENT_INITIALIZATION_ERROR);
        EXPECT_EQ(result.error_message, ErrorMessage::EVENT_INITIALIZATION_ERROR);
    }

    TEST(lib_AwsLambda, N_Response_TestConstructor_MainConstructorAndCreateResponse) {
        JsonValue body;
        body.WithString("message", "test_main_constructor");
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
        expect_body.WithString("message", "test_main_constructor");
        expect_body.WithString("result", "successful");
        const std::string expect_body_string = expect_body.View().WriteCompact();

        // test
        EXPECT_EQ(res_status_code, 200);
        EXPECT_EQ(res_body_string, expect_body_string);
    }

    TEST(lib_AwsLambda, N_Response_TestConstructor_DelegatingConstructor001) {
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

    TEST(lib_AwsLambda, N_Response_TestConstructor_DelegatingConstructor002) {
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

    TEST(lib_AwsLambda, N_Response_TestResponseHeaders) {
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

    TEST(lib_AwsLambda, N_DefaultEventHandler_TestConstructor_MainConstructorAndCreateResponse) {
        JsonValue body;
        body.WithString("message", "test_main_constructor");
        body.WithString("result", "successful");

        // StatusCode::OK == 200
        DefaultEventHandler default_handler(StatusCode::OK, std::move(body));
        invocation_response target = default_handler.create_response();

        const JsonValue payload = JsonValue(target.get_payload());
        const auto payload_view = payload.View();
        const int res_status_code = static_cast<int>(payload_view.GetInteger("statusCode"));
        const JsonValue res_body(payload_view.GetString("body"));
        const std::string res_body_string = res_body.View().WriteCompact();

        // create expect
        JsonValue expect_body;
        expect_body.WithString("message", "test_main_constructor");
        expect_body.WithString("result", "successful");
        const std::string expect_body_string = expect_body.View().WriteCompact();

        // test
        EXPECT_EQ(res_status_code, 200);
        EXPECT_EQ(res_body_string, expect_body_string);
    }

    TEST(lib_AwsLambda, N_DefaultEventHandler_TestConstructor_DelegatingConstructor001) {
        // StatusCode::BAD_REQUEST == 400
        DefaultEventHandler default_handler(StatusCode::BAD_REQUEST, ResponseMessage::BAD_REQUEST);
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

    TEST(lib_AwsLambda, N_DefaultEventHandler_TestConstructor_DelegatingConstructor002) {
        // StatusCode::OK == 200
        DefaultEventHandler default_handler(StatusCode::OK);
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

    TEST(lib_AwsLambda, N_DefaultEventHandler_TestResponseHeaders) {
        // StatusCode::BAD_REQUEST == 400
        DefaultEventHandler default_handler(StatusCode::OK);
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
