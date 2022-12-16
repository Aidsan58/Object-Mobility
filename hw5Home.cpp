
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

// JSON RPC part
//#include "hw5client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

using namespace jsonrpc;
using namespace std;

int main(){

  Person girl2;
  girl2.setDescription("a dear little girl");
  Person girl("little red riding hood", "dear little girl", "young");

  Thing cap("cap", "huge", "red velvet");
  //cap.setName("cap");
  //cap.setDescription("little, red velvet");
  Thing wine("wine", "big box", "wet");


  HttpClient httpclient("http://127.0.0.1:7375");
  hw5Client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value myv;
  Json::Value gps;
  gps["location"] = "forest";

  try {
    //cout<<"try entered"<<endl;
    /*myv = myClient.move("move", "Person",
			girl.dump2Json(),
			gps,
			"girl");*/
      myv = myClient.move("move", "person", girl.dump2Json(), gps, "girl");
      //cout<<"move successful"<<endl;
      //cout<<myv["name"].asString() << " sent to "<< gps["location"].asString()<<endl;
      cout<<"sent "<< myv["name"].asString()<< " to " << gps["location"].asString()<<endl;
    } catch (JsonRpcException &e) {
      cout<<"catch entered"<<endl;
    cerr << e.what() << endl;
  }
  //std::cout << myv.toStyledString() << std::endl;

  
  try {
    //cout<<"try entered"<<endl;
    /*myv = myClient.move("move", "Person",
			girl.dump2Json(),
			gps,
			"girl");*/
      myv = myClient.move("move", "thing", cap.dump2Json(), gps, "cap");
      //cout<<"move successful"<<endl;
      //cout<<myv["name"].asString() << " sent to "<< gps["location"].asString()<<endl;
      cout<<"sent "<< myv["name"].asString()<< " to " << gps["location"].asString()<<endl;

    } catch (JsonRpcException &e) {
      cout<<"catch entered"<<endl;
    cerr << e.what() << endl;
  }


try {
    //cout<<"try entered"<<endl;
      myv = myClient.move("move", "thing", wine.dump2Json(), gps, "wine");
      //cout<<myv["name"].asString() << " sent to "<< gps["location"].asString()<<endl;
      cout<<"sent "<< myv["name"].asString()<< " to " << gps["location"].asString()<<endl;
    } catch (JsonRpcException &e) {
      cout<<"catch entered"<<endl;
    cerr << e.what() << endl;
  }


  Json::Value finish;

  try {
    finish = myClient.done();
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  //std::cout << finish.toStyledString() << std::endl;

  HttpServer httpserver(7374);
  Myhw5Server s(httpserver,
		JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  std::cout << "Hit enter to stop the server" << endl;
  getchar();

  s.StopListening();
  return 0;



}
