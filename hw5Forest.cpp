
// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

// for JsonRPCCPP
#include <iostream>
#include "hw5server.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
//#include "hw5client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <stdio.h>

// ecs36b

#include "person.h"
#include "thing.h"
#include <time.h>
#include "hw5server.cpp"
#include "hw5client.h"

using namespace jsonrpc;
using namespace std;

int main(){
  HttpClient httpclient("http://127.0.0.1:7376");
  hw5Client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value myv;
  Json::Value gps;
  gps["location"] = "grandma";

  
  HttpServer httpserver(7375);
  Myhw5Server s(httpserver,
		JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)


  while (s.is_done == false){
  s.StartListening();
  }
  std::cout << "Hit enter to stop the server" << endl;
  s.StopListening();

  //access every value in person map

  for (auto it = s.Person_Map.begin(); it != s.Person_Map.end(); it++) {
   try {
    myv = myClient.move("move", "Person",
      s.Person_Map[it->first]->dump2Json(),
			gps,
			"girl");
      //cout<<myv["name"].asString() << " sent to "<< gps["location"].asString()<<endl;
      cout<<"sent "<< myv["name"].asString()<< " to " << gps["location"].asString()<<endl;
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  //std::cout << myv.toStyledString() << std::endl;
  }


 for (auto it = s.Thing_Map.begin(); it != s.Thing_Map.end(); it++) {
  //cout<<"for loop entered"<<endl;
   try {
    //cout<<"Forest Thing try entered"<<endl;
    myv = myClient.move("move", "Thing",
      s.Thing_Map[it->first]->dump2Json(),
			gps,
			"cap");
      //cout<<"Thing move from forest to grandma successful"<<endl;
      //cout<<myv["name"].asString() << " sent to "<< gps["location"].asString()<<endl;
      cout<<"sent "<< myv["name"].asString()<< " to " << gps["location"].asString()<<endl;
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
    //cout<<"Forest server thing catch entered"<<endl;
  }
  //std::cout << myv.toStyledString() << std::endl;
  }


  return 0;
}



 
  

