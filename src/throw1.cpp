#include<iostream>
#define FMT_HEADER_ONLY
#include<fmt/core.h>

using namespace std;
using fmt::format;

void ff (int ii){
  const int size = 3;
  int ar[size];

  if(ii < 0 || size <= ii){
    throw out_of_range{format("out of range: {}", ii)};
  }
}

void try_exception(){

  ff(5);
  // try{
  //   ff(5);
  // }catch(const exception& error){
  //   const char* message = error.what();
  //   cerr << endl;
  //   cerr << typeid(error).name() << endl;
  //   cerr << message << endl;
  //   cerr << endl;
  //   throw;
  // }
}

int connect_to_server_api(){
  return 503;
};
int try_system_error() {
  if(connect_to_server_api() == 503){
    cerr << "server error" << endl;
    error_code ec = make_error_code(errc::network_down);
    throw system_error{ec};
  }else{
    cout << "ok" << endl;
  }
  return 1;
}

int main() {
  try{
    //try_exception();
    try_system_error();
  }catch(system_error& error){
    cerr << "system_error:" << endl;

    error_code ec = error.code();
    int error_value = ec.value();
    string code = to_string(error_value);
    string message = ec.message();

    cerr << format("{}: {}", code, message) << endl;
    cerr << endl;

  }catch(exception& error) {
    cerr << "exception_error:" << endl;

    const string code = typeid(error).name();
    const string message = error.what();

    cerr << format("{}: {}", code, message) << endl;
    cerr << endl;
  }
  return 0;
}
