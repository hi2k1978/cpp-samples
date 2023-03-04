#include<iostream>
#include<map>
// #include<utility>

#include "aws_lambda_handler.h"

AwsLambdaResponse get_response__template () {
    AwsLambdaResponse res{405, "res_header", "res_body"};
    return res;
}

AwsLambdaOptionsHandler::AwsLambdaOptionsHandler(AwsLambdaEvent *event_) {
    event = event_;
    std::cout << __func__ << ": " << event->http_method << ", " << event->header << ", " << event->body << std::endl;
}

AwsLambdaResponse AwsLambdaOptionsHandler::make_response() {
    AwsLambdaResponse res{204, "res_options_header", "res_options_body"};
    return res;
};

AwsLambdaGetHandler::AwsLambdaGetHandler(AwsLambdaEvent *event_) {
    event = event_;
    std::cout << __func__ << ": " << event->http_method << ", " << event->header << ", " << event->body << std::endl;
}

AwsLambdaResponse AwsLambdaGetHandler::make_response() {
    AwsLambdaResponse res{200, "res_get_header", "res_get_body"};
    return res;
};

BaseAwsLambdaMainHandler::BaseAwsLambdaMainHandler(std::string http_method_, std::string header_, std::string body_) {

    event = std::make_unique<AwsLambdaEvent>(http_method_, header_, body_);

    options_handler = std::make_unique<AwsLambdaOptionsHandler>(event.get());
    get_handler = std::make_unique<AwsLambdaGetHandler>(event.get());
    handler_map[HTTP_METHOD_OPTIONS] = dynamic_cast<BaseAwsLambdaHandler*>(options_handler.get());
    handler_map[HTTP_METHOD_GET] = dynamic_cast<BaseAwsLambdaHandler*>(get_handler.get());
};

AwsLambdaResponse BaseAwsLambdaMainHandler::make_response() {
    std::cout << __func__ << ": " << event->http_method << ", " << event->header << ", " << event->body << std::endl;
    BaseAwsLambdaHandler *handler = handler_map[event->http_method];
    return handler->make_response();
};
