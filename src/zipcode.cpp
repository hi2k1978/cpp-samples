#include<iostream>

#define FMT_HEADER_ONLY
#include<fmt/format.h>

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
using fmt::format;



struct AddressInquiryResult {
  bool success;
  string zipcode;
  string address;
};

class AddressInquiry {

  const string inquiry_url = "http://zipcloud.ibsnet.co.jp/api/search?zipcode=";
  AddressInquiryResult failed {false, "", ""};

public:
  AddressInquiryResult search(string zipcode){

    using namespace Poco::Net;
    using namespace Poco;
    using json = nlohmann::json;
    try{
      const string url = inquiry_url + zipcode;
      
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
      // cout << fmt::format("{}, {}", status, reason)<<endl;
      if (200 <= status && status <= 299){
	istream &is = session.receiveResponse(res);
	string data, buf;
	while(is >> buf){
	  data += buf;
	}
	// cout << fmt::format("data = {}", data) << endl;
	json jdata = json::parse(data);
	string address = fmt::format("{}{}{}",
				     jdata["results"][0]["address1"],
				     jdata["results"][0]["address2"],
				     jdata["results"][0]["address3"]);
	AddressInquiryResult result {true, zipcode, address};
	return result;
      }
      return failed;

    }catch(system_error &ex){
      error_code ec = ex.code();
      cerr << ec.message() << endl;
      return failed;
    }catch(Exception &ex){
      cerr << ex.displayText() << endl;
      return failed;
    };
  }
};

int main() {
  auto inquiry = make_unique<AddressInquiry>();
  string zipcode_list[] = {"1500032"};
  // string zipcode_list[] = {"1500032", "4040001", "0010013"};

  cout << endl << "zipcode -> address:" << endl;
  for (auto zipcode: zipcode_list){
    AddressInquiryResult result = inquiry->search(zipcode);
    cout << format("{} -> {}", result.zipcode, result.address) << endl;
  }
  return 0;
 
}


