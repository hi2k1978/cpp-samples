#ifndef __HOGE__
#define __HOGE__

#include<iostream>
#include<map>
#include<memory>

#define HTTP_METHOD_OPTIONS "OPTIONS"
#define HTTP_METHOD_GET "GET"
#define HTTP_METHOD_POST "POST"
#define HTTP_METHOD_PUT "PUT"
#define HTTP_METHOD_PATCH "PATCH"
#define HTTP_METHOD_DELETE "DELETE"

struct AwsLambdaEvent {
    std::string http_method;
    std::string header;
    std::string body;
    AwsLambdaEvent(std::string http_method_, std::string header_, std::string body_) {
	http_method = http_method_;
	header = header_;
	body = body_;
    };
};

struct AwsLambdaResponse {
    int status_code;
    std::string header;
    std::string body;
};

class BaseAwsLambdaHandler {
protected:
    AwsLambdaEvent *event;
public:
    // BaseAwsLambdaHandlerByHttpMethod(AwsLambdaEvent *event_);
    virtual AwsLambdaResponse make_response() = 0;
};

class AwsLambdaOptionsHandler : public BaseAwsLambdaHandler {
public:
    AwsLambdaOptionsHandler(AwsLambdaEvent *event_);
    AwsLambdaResponse make_response() override;
};

class AwsLambdaGetHandler : public BaseAwsLambdaHandler {
public:
    AwsLambdaGetHandler(AwsLambdaEvent *event_);
    AwsLambdaResponse make_response() override;
};

class BaseAwsLambdaMainHandler{
protected:
    std::unique_ptr<AwsLambdaEvent> event = nullptr;

    std::unique_ptr<AwsLambdaOptionsHandler> options_handler = nullptr;
    std::unique_ptr<AwsLambdaGetHandler> get_handler = nullptr;
    std::map<std::string, BaseAwsLambdaHandler*> handler_map;

public:
    BaseAwsLambdaMainHandler(std::string http_method_, std::string header_, std::string body_);
    virtual AwsLambdaResponse make_response();
};

#endif

