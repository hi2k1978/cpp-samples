#include<iostream>
#include<vector>
#include<concepts>

#define FMT_HEADER_ONLY
#include<fmt/core.h>

using namespace std;
using fmt::format;

template<class T> auto vdouble(vector<T> && data) -> vector<T>;


template <class T>
concept Arithmetic = requires(T x){
  x * 2 + 100;
};

template<class T> requires Arithmetic<T>
auto vdouble(vector<T> && data) -> vector<T> {
  static_assert(is_arithmetic<T>::value, "hoge");
  const int kk = 2;
  const int vv = 200;

  auto calc = [kk, vv](T xx) -> T {
    return kk * xx + vv;
  };
  for (int i=0, j=100; T& val: data) {
    //val = val * 2 + 100;
    val = calc(val);
    cout << format("i: {}, j: {}, val: {}", i, j, val) << endl;
    ++i; ++j;
  }
  return data;
}

int main() {
  cout << format("this is a vector hoge") << endl;
  vector<int> data = {1, 2, 3};
  vector<int> data2 = vdouble(move(data));
  cout << "int:" << endl;
  for(auto val: data2) cout << val << endl;
  cout << endl;

  vector<double> ddata = {1.9, 2.2, 3.3};
  vector<double> ddata2 = vdouble(move(ddata));
  cout << "double:" << endl;
  for(auto val: ddata2) cout << val << endl;
  cout << endl;

#ifdef IGNOREED
  vector<string> sdata = {"hoge", "moge"};
  vector<string> sdata2 = vdouble(move(sdata));
  cout << "string:" << endl;
  for(auto val: sdata2) cout << val << endl;
  cout << endl;
#endif
}
