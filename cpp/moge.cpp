#include<iostream>
#include<memory>

void child(std::string* p) {
    *p = "changed";
    
}

void parent() {
    // auto moge = std::make_unique<std::string>("moge");
    std::string moge = "moge";
    std::cout << "moge: " << moge << std::endl;
    child(&moge);
    std::cout << "moge: " << moge << std::endl;
}

int main() {
    parent();
    return 0;
}
