#ifndef __CPP_SAMPLES_CPP_LAMBDA_H_
#define __CPP_SAMPLES_CPP_LAMBDA_H_

#include <aws/lambda-runtime/runtime.h>
#include <aws/core/utils/json/JsonSerializer.h>

#include<iostream>
#include<map>
#include<memory>


using namespace aws::lambda_runtime;


namespace CppLambda {

    using namespace Aws::Utils::Json;

    using StatusCode = aws::http::response_code;
    
    const std::string CONTENT_TYPE_APPLICATION_JSON = "application/json";
    const std::string_view HTTP_METHOD_GET = "GET";
    const std::string_view HTTP_METHOD_POST = "POST";
    
    enum class RequestType {
	NONE = 0,
	GET = 1,
	POST = 2,
    };
    
    struct Event {
	RequestType request_type;
	std::string http_method;
	std::string path;
	JsonView headers;
	JsonView body;
	JsonView query;
	
	Event(invocation_request const& request_);
	void show() const;
	int get_request_type() const;
    };

    class Response final {
    private:
	StatusCode status_code;
	JsonValue body;
	
    public:
	Response(StatusCode status_code_, JsonValue body_)
	    : status_code(std::move(status_code_)), body(std::move(body_)) {};
	invocation_response get() const;
    };

    class BaseRequest {
    public:
	virtual invocation_response handler() const = 0;
    };

    class InvalidRequest final : public BaseRequest {
    private:
	StatusCode status_code;
	std::string error_message;
    public:
	InvalidRequest(StatusCode status_code_, std::string error_message_)
	    : status_code(std::move(status_code_)), error_message(std::move(error_message_)) {};
	invocation_response handler() const override;
    };

    using RequestMap = std::map<RequestType, std::unique_ptr<BaseRequest>>;

    class Main final {
    private:
	const RequestType& request_type;
	const RequestMap& request_map;
    public:
	Main(const RequestType& request_type_, const RequestMap& request_map_) noexcept
	    : request_type(request_type_), request_map(request_map_) {};
	invocation_response handler() const;
    };
}

#endif

/*
  enum class response_code {
  REQUEST_NOT_MADE = -1,
  CONTINUE = 100,
  SWITCHING_PROTOCOLS = 101,
  PROCESSING = 102,
  OK = 200,
  CREATED = 201,
  ACCEPTED = 202,
  NON_AUTHORITATIVE_INFORMATION = 203,
  NO_CONTENT = 204,
  RESET_CONTENT = 205,
  PARTIAL_CONTENT = 206,
  MULTI_STATUS = 207,
  ALREADY_REPORTED = 208,
  IM_USED = 226,
  MULTIPLE_CHOICES = 300,
  MOVED_PERMANENTLY = 301,
  FOUND = 302,
  SEE_OTHER = 303,
  NOT_MODIFIED = 304,
  USE_PROXY = 305,
  SWITCH_PROXY = 306,
  TEMPORARY_REDIRECT = 307,
  PERMANENT_REDIRECT = 308,
  BAD_REQUEST = 400,
  UNAUTHORIZED = 401,
  PAYMENT_REQUIRED = 402,
  FORBIDDEN = 403,
  NOT_FOUND = 404,
  METHOD_NOT_ALLOWED = 405,
  NOT_ACCEPTABLE = 406,
  PROXY_AUTHENTICATION_REQUIRED = 407,
  REQUEST_TIMEOUT = 408,
  CONFLICT = 409,
  GONE = 410,
  LENGTH_REQUIRED = 411,
  PRECONDITION_FAILED = 412,
  REQUEST_ENTITY_TOO_LARGE = 413,
  REQUEST_URI_TOO_LONG = 414,
  UNSUPPORTED_MEDIA_TYPE = 415,
  REQUESTED_RANGE_NOT_SATISFIABLE = 416,
  EXPECTATION_FAILED = 417,
  IM_A_TEAPOT = 418,
  AUTHENTICATION_TIMEOUT = 419,
  METHOD_FAILURE = 420,
  UNPROC_ENTITY = 422,
  LOCKED = 423,
  FAILED_DEPENDENCY = 424,
  UPGRADE_REQUIRED = 426,
  PRECONDITION_REQUIRED = 427,
  TOO_MANY_REQUESTS = 429,
  REQUEST_HEADER_FIELDS_TOO_LARGE = 431,
  LOGIN_TIMEOUT = 440,
  NO_RESPONSE = 444,
  RETRY_WITH = 449,
  BLOCKED = 450,
  REDIRECT = 451,
  REQUEST_HEADER_TOO_LARGE = 494,
  CERT_ERROR = 495,
  NO_CERT = 496,
  HTTP_TO_HTTPS = 497,
  CLIENT_CLOSED_TO_REQUEST = 499,
  INTERNAL_SERVER_ERROR = 500,
  NOT_IMPLEMENTED = 501,
  BAD_GATEWAY = 502,
  SERVICE_UNAVAILABLE = 503,
  GATEWAY_TIMEOUT = 504,
  HTTP_VERSION_NOT_SUPPORTED = 505,
  VARIANT_ALSO_NEGOTIATES = 506,
  INSUFFICIENT_STORAGE = 507,
  LOOP_DETECTED = 508,
  BANDWIDTH_LIMIT_EXCEEDED = 509,
  NOT_EXTENDED = 510,
  NETWORK_AUTHENTICATION_REQUIRED = 511,
  NETWORK_READ_TIMEOUT = 598,
  NETWORK_CONNECT_TIMEOUT = 599
  };
*/
