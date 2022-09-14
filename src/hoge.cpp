#include<iostream>
#define  FMT_HEADER_ONLY
#include<fmt/core.h>

using namespace std;
using fmt::format;

template<typename T1, typename T2>
auto moge(T1 x, T2 y) -> decltype(x+y) {
  return x + y;
}

int main() {
  auto xx = 3;
  auto yy = 8.0;
  auto zz = moge(xx, yy);
  cout << format("zz={}", zz) << endl; 
  cout << format("zz={}", static_cast<char>(65)) << endl;
  cout << R"(ho"ge)" << endl;
  return 0;
}
