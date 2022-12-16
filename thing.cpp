#include "thing.h"
#include <iostream>

Thing::Thing(){}
Thing::Thing(string name, string size, string description){
    this->name = name;
    this->size = size;
    this->description = description;
}
string Thing::getName()
{
    return name;
};
void Thing::setName(string name)
{
    this->name = name;
};
string Thing::getSize()
{
    return size;
};
void Thing::setSize(string size)
{
    this->size = size;
};
string Thing::getDescription()
{
    return description;
};
void Thing::setDescription(string name)
{
    this->description = description;
};

Json::Value Thing::dump2Json()
{
    //std::cout<<"Thing Dump 2 json entered"<<endl;
    Json::Value result;
    if (this->name != "")
    {
        result["name"] = this->name ;
    }
    if (this->size != "")
    {
        result["size"] = this->size;
    }
    if (this->description != "")
    {
        result["description"] = this->description; 
    }
    if(result.isNull()){
        cout<<"thing dump 2 json is null"<<endl;
        cout<<result["name"].asString();
        cout<<result["size"].asString();
        cout<<result["description"].asString();
    }
    //std::cout<<result.toStyledString()<<endl;

    return result;

}
bool Thing::JSON2Object(Json::Value n){
        if(n["name"].isNull() || !n["name"].isString()){
            return false;
        }
        if(n["size"].isNull() || !n["size"].isString()){
            return false;
        }
        if(n["description"].isNull() || !n["description"].isString()){
            return false;
        }
        
        this->name = n["name"].asString();
        this->size = n["size"].asString();
        this->description = n["description"].asString();

        return true;
    }