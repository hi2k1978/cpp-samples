#include<iostream>
#include<cstring>
#include<typeinfo>

typedef struct hoge_ {
    int32_t id;
    union {
        char cc;
        char ccs[64];
    } u;
} Hoge;
template <typename T>
Hoge create_hoge(int32_t id, T cc) {
    // std::cout << std::type_info(cc) << std::endl;
    
    Hoge h;
    if (typeid(T) == typeid(char)) {
        h.id = id;
        h.u.cc = cc;        
    } else {
        h.id = 0;
        h.u.cc = 0;                
    }
    return h;
}
template <typename T>
Hoge create_hoge(int32_t id, T* ccs) {
    // std::cout << std::type_info(cc) << std::endl;
    
    Hoge h;
    if (typeid(T) == typeid(char)) {
        h.id = id;
        strcpy(h.u.ccs,ccs);        
    } else {
        h.id = 0;
        strcpy(h.u.ccs, "");        
    }
    return h;
}
int main() {
    Hoge hoge = create_hoge<const char>(10, 'a');
    Hoge hoge2 = create_hoge<const char>(10, "abcde");
    
    // strcpy(h.u.ccs, "hoge");
    std::cout << "zzz" << std::endl;
    std::cout << hoge.id << ": " << hoge.u.cc << std::endl;
    std::cout << hoge.id << ": " << hoge.u.ccs << std::endl;
    return 0;
}
