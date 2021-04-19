#include"serialdataconnector.h"
#include<Arduino.h>
using namespace std;
String* split(String s,char seperator,int &count,int from=0)
{
    vector<String> *v= new vector<String>();
    String item;
    bool _continue=true;
    int index;
    String str;
    while (_continue)
    {
        index=s.indexOf(seperator,from);
        
        if(index<0)
        {
            index=s.length()-1;
            _continue=false;
        }
        str=s.substring(from,index);
        from=index+1;
        if(str.length()==0)
            continue;
        // Serial.print("from:");
        // Serial.print(from);
        // Serial.print("\tindex:");
        // Serial.print(index);
        // Serial.print("\t str:");
        // Serial.println(str);
             v->push_back(str);
    }
     count=v->size();
     
    return &((*v)[0]);
}
SerialDataConnector::SerialDataConnector(IDataConnector *connector)
{
    this->connector=connector;
    this->data=connector->getData();
    Serial.print("\n\n\r");
    Serial.println("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*");
    Serial.println("Welcome to SmartCar project Serial Communication");
    Serial.println("You can use management commands");
}
void writeError(){
    Serial.println("unknown command");
}
void SerialDataConnector::read(){
    if(!Serial)
        return;
    bool exit=false;
    String *command;
    int count=0;
        if(Serial.available() > 0) {
            command=split(Serial.readString(),' ',count);
            if(count==0)
                return;
          if(command[0].equals("set"))
          {
              if(count<3)
              {
                  writeError();
                  return;
              }
              if(command[1].equals("ssid"))
              {
                 this->data.ssid=command[2];
              }
              else if(command[1].equals("pswd"))
              {
                 this->data.password=command[2];
              }
              else if(command[1].equals("ckey"))
              {
                 this->data.carKey=command[2];
              }
              connector->dataChanged(this->data);
              Serial.println("OK");

          }
          else if(command[0].equals("get"))
          {
              if(count<2)
              {
                  writeError();
                  return;
              }
              if(command[1].equals("ssid"))
              {
                  Serial.println(data.ssid);
              }
              else if(command[1].equals("pswd"))
              {
                  Serial.println(data.password);
              }
              else if(command[1].equals("ckey"))
              {
                  Serial.println(data.carKey);
              }

          }
          else if(command[0].equals("connect"))
          {
              connector->connect();
          }
          else if(command[0].equals("exit"))
          {

          }
          else if(command[0].equals("save"))
          {

          }
          else{
              writeError();
              return;
          }
        }
}