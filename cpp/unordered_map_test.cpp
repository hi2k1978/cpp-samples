#include<iostream>
#include<functional>
#include<unordered_map>

#define HOGE_PTR(x) std::bind(&Hoge::x, this)

enum class HogeType
{
    Hoge1,
    Hoge2,
    Hoge3,
};
using HogeFunction = std::function<void()>;
using HogeFunctionMap = std::unordered_map<HogeType, HogeFunction>;



class HogeStore
{
public:
    HogeStore(HogeFunctionMap&& hogeFunctionMap)
         :hogeFunctionMap_(std::move(hogeFunctionMap))
    {}

    HogeFunction findHogeFunction(HogeType hogeType)
    {
        auto item = hogeFunctionMap_.find(hogeType);
        if (item != hogeFunctionMap_.end()) {
            return item->second;
        } else {
            return nullptr;
        }
    }
private:
    HogeFunctionMap hogeFunctionMap_;
};

class Hoge
{
public:
    Hoge()
        :hogeStore_(initHogeFunctionMap())
    {}
    void print(HogeType hogeType)
    {
        // HogeFunction hogeFunction = find(HogeType::Hoge1);
        HogeFunction hogeFunction = hogeStore_.findHogeFunction(hogeType);
        if (hogeFunction != nullptr) {
            hogeFunction();
        } else {
            std::cout << "no match" << std::endl;
        }
    }
private:
    HogeFunctionMap initHogeFunctionMap()
    {
        HogeFunctionMap hogeFunctionMap = {
            {HogeType::Hoge1, HOGE_PTR(hoge1)},
            {HogeType::Hoge2, HOGE_PTR(hoge2)},
        };
        return hogeFunctionMap;
    }

    void hoge1()
    {
        std::cout << "msg: hoge1" << std::endl;
    }
    void hoge2()
    {
        std::cout << "msg: hoge2" << std::endl;
    }
    HogeStore hogeStore_;
    
};

int main() {
    Hoge hoge;
    hoge.print(HogeType::Hoge1);
    return 0;
}

