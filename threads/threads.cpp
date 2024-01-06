#include<iostream>
#include<memory>
#include<thread>
#include<mutex>
#include<atomic>
#include<queue>
#include<cassert>
#include<future>
#include<chrono>

int main() {
    int x=0, y=0;
    std::thread t([&]{++x;});
    --y;
    t.join();
    assert(x == 1 && y == -1);
    std::cout << "moge" << std::endl;
    return 0;
}
