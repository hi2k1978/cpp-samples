#include<iostream>
#include<string>
#include<sstream>
#include<cstdio>
#include<exception>

namespace Util {
    
    class Exception: public std::exception {
    public:
        Exception(const int32_t code, const char* message) noexcept
            : code_(code), message_(std::string(message)) {};
        int32_t code() {
            return code_;  
        };
    private:
        const int32_t code_;
        const std::string message_;
    };
}

void h() {
    // throw Util::Exception(10, "hoge");
    throw std::exception();
    return;
}

int main(){
    char c = 0xfd;
    printf("\nC: %d%c\n", c, c);
    std::stringstream ss;
    std::string cc = { c };
    ss << cc;
    ss << std::string({c});
    std::cout << "C++:" << ss.str() << std::endl;
    std::string hoge;
    std::cout << "debug" << std::endl;
    std::cout << hoge.c_str() << std::endl;
    std::cout << "debug" << std::endl;

    try {
        h();
    } catch(Util::Exception& e) {
        std::cout << e.code() << std::endl;
        std::cout << "Util::Exception" << std::endl;
        
    } catch(std::exception& e) {
        std::cout << "std::exception" << std::endl;
    }
}
