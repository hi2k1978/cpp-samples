#include<iostream>
#define FMT_HEADER_ONLY
#include<fmt/core.h>

using namespace std;
using fmt::format;

struct MyPoint{
  int x, y;
};
template<typename CharT,typename Traits>
basic_istream<CharT, Traits>& operator>>(basic_istream<CharT, Traits>& is, MyPoint& pt){
  is >> pt.x >> pt.y;
  return is;
}

void input_point() {
  MyPoint pt{};
  cin >> pt;
  cout << format("pt: {},{}", pt.x, pt.y) << endl;
}
int main(){
  input_point();
  return 0;
}
  
