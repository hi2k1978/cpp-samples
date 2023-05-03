#include<iostream>

#include"sample1.h"
#include"sample2.h"

int main(int argc, char** argv) {
    std::cout << "max: " << Sample1::mymax(10, 5) << std::endl;
    std::cout << "min: " << Sample2::mymin(10, 5) << std::endl;
    return 0;
}
