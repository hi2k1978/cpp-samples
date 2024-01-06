#include<iostream>
#include<vector>
#include<memory>
#include<type_traits>
#include<chrono>

constexpr int nmax = 10;

struct Hoge {
    int id;
    int val;
    int set(int id_, int val_) noexcept {
        id = id_;
        val = val_;
        return 0;
    };
};

int set_hoge(Hoge* hoge, int size) noexcept {
    for (int i = 0; i < size; i++) {
        hoge[i].set(i, i*3);
    }
    return 0;
}

int print_vector_hoge(std::vector<Hoge> hoge) {
    for (auto vec : hoge) {
        std::cout << vec.val << ",";
    }
    std::cout << std::endl;
    return 0;
}


int print_hoge(Hoge* hoge, int size) noexcept {
    for (int i = 0; i < size; i++) {
        std::cout << hoge[i].val << ",";
    }
    std::cout << std::endl;
    return 0;
}

int set_hoge2(std::vector<Hoge>* hoge2) noexcept {
    for(int n = 0; auto &itr : *hoge2) {
        itr.set(n, n * 30);
        n++;
    }
    return 0;
}

int print_hoge2_1(std::vector<Hoge>* hoge2) noexcept {
    for(auto itr = hoge2->begin(); itr != hoge2->end(); itr++) {
        std::cout << itr->val << ",";
    }
    std::cout << std::endl;
    return 0;
}

int print_hoge2_2(std::unique_ptr<std::vector<Hoge>>&& hoge2) noexcept {
    for(auto itr = hoge2->begin(); itr != hoge2->end(); itr++) {
        std::cout << itr->val << ",";
    }
    std::cout << std::endl;
    return 0;
}

std::tuple<int*, int*> fugafuga(int* p) {
    std::cout << *p << std::endl;
    *p = 20;
    std::cout << *p << std::endl;
    
    return {p, p};
}


int hoge() {
    std::vector<Hoge> hoge(10);
    std::cout << hoge.size() << std::endl;
    set_hoge(hoge.data(), hoge.size());
    print_vector_hoge(hoge);
    hoge.resize(5);
    print_hoge(hoge.data(), hoge.size());

    auto hoge2 = std::make_unique<std::vector<Hoge>>(10);
    set_hoge2(hoge2.get());
    print_hoge2_1(hoge2.get());
    print_hoge2_2(std::move(hoge2));

    int p = 10;
    int *pp1, *pp2;
    auto result = fugafuga(&p);
    std::tie(pp1, pp2) = result;
    std::cout << *pp1 << std::endl;
    return 0;
}

class Moge {
public:
    Moge(int nn) noexcept : pp(std::make_unique<int>(nn)) {};
    int show() {
        std::cout << *pp << std::endl;
        return 0;
    };
private:
    const std::unique_ptr<int> pp;
    
    
};

int moge1() {
    Moge moge(10);
    // moge.show();
    
    return 0;
}

int moge2() {
    auto pp = std::make_unique<int>(10);
    // std::cout << *pp << std::endl;
    return 0;
}
int main() {
    
    std::cout << "## start ####" << std::endl;
    // hoge();
    auto start = std::chrono::system_clock::now();
    for (int i = 0 ; i < 1'000'000; i++) {
        moge1();
    }
    auto end = std::chrono::system_clock::now();
    auto elapsed = end - start;
    std::cout << elapsed.count() / 1.0e9 << std::endl;
    start = std::chrono::system_clock::now();
    for (int i = 0 ; i < 1'000'000; i++) {
        moge2();
    }
    end = std::chrono::system_clock::now();
    elapsed = end - start;
    std::cout << elapsed.count() / 1.0e9 << std::endl;
    // std::cout << end - start << std::endl;
    return 0;
}

