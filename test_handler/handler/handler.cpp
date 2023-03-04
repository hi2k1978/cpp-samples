#include "aws_lambda_handler.h"

int main(int argc, char **argv) {

    // BaseAwsLambdaMainHandler main_handler("OPTIONS", "options_header", "options_body");
    BaseAwsLambdaMainHandler main_handler("GET", "get_header", "get_body");
    AwsLambdaResponse response = main_handler.make_response();
    std::cout << "status_code: " << response.status_code << std::endl;
    std::cout << "header     : " << response.header << std::endl;
    std::cout << "body       : " << response.body << std::endl;
}
