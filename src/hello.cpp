#include<iostream>

#define FMT_HEADER_ONLY
#include<fmt/core.h>

#include<nlohmann/json.hpp>

#include<Poco/URI.h>
#include<Poco/Net/HTTPClientSession.h>
#include<Poco/Net/HTTPRequest.h>
#include<Poco/Net/HTTPResponse.h>
#include<Poco/StreamCopier.h>
#include<Poco/Path.h>
#include<Poco/Exception.h>
#include<Poco/RegularExpression.h>

using namespace std;
using namespace Poco::Net;
using namespace Poco;
using json = nlohmann::json;

int main() {
  try{
    const string zipcode = "1130021";
    const string url = fmt::format("http://zipcloud.ibsnet.co.jp/api/search?zipcode={}", zipcode);

    unique_ptr<URI> moge;
    cout << fmt::format("url={}, zipcode={}",url, zipcode) << endl;
    auto hoge = make_unique<URI>(url);
    cout << hoge -> getHost() << endl;;
    moge = move(hoge);
    cout << moge -> getHost() << endl;;
    cout << endl;
    // URI uri2(url);
    // unique_ptr<URI> pp= nullptr;
    // pp(new uri2);

    URI uri(url);    
    HTTPClientSession session(uri.getHost(), uri.getPort());

    string path(uri.getPathAndQuery());
    if (path.empty()){
      error_code ec = make_error_code(errc::network_down);
      throw system_error{ec};
    }

    HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
    session.sendRequest(req);

    HTTPResponse res;
    const int status = res.getStatus();
    const string reason = res.getReason();
    cout << fmt::format("{}, {}", status, reason)<<endl;

    if (200 <= status && status <= 299){
      istream &is = session.receiveResponse(res);
      string data, buf;
      while(is >> buf){
	// cout << fmt::format("buf = {}", buf) << endl;
	data += buf;
      }
      cout << fmt::format("data = {}", data) << endl;
      json jdata = json::parse(data);
      string result = fmt::format("{}{}{}",
				  jdata["results"][0]["address1"],
				  jdata["results"][0]["address2"],
				  jdata["results"][0]["address3"]);
      cout << fmt::format("result = {}", result) << endl;;
    }
  }catch(system_error &ex){
    error_code ec = ex.code();
    cout << ec.message() << endl;
    return -1;
  }catch(Exception &ex){
    cerr << ex.displayText() << endl;
    return -1;
  }
  return 0;
  
}


