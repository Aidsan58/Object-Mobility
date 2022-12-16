#ifndef _THING_H_
#define _THING_H_
#include "ecs36b_Common.h"

class Thing 
{
private:     

    std::string name;
    std::string size;
    std::string description;

public:
    
    string getName();
    void setName(string name);
    string getSize();
    void setSize(string size);
    string getDescription();
    void setDescription(string description);

    Thing();
    Thing(string name, string size, string description);
    virtual Json::Value dump2Json();
    //Commenting this out as a reminder in case I need Json2object
   virtual bool JSON2Object(Json::Value);
    

    
};
#endif