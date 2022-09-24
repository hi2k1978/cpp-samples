#include<iostream>
using namespace std;
#define  FMT_HEADER_ONLY
#include<fmt/core.h>
using fmt::format;

#include<thread>
#include<memory>
#include<chrono>

mutex printMutex_;
void print(const string& s){
  lock_guard<mutex> lock{printMutex_};
  cout << s << endl;
}

void f(stop_token s, string title){
  while(!s.stop_requested()){
    print(title + "...");
    this_thread::sleep_for(chrono::seconds{1});
  }
  print(title+": stopped.");
}


int main(){
  thread th{f, "[Thread A]"};
  this_thread::sleep_for(chrono::seconds{3});
  th.request_stop();
  return 0;
}
