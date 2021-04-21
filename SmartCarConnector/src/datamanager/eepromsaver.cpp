#include"eepromsaver.h"
#include<EEPROM.h>
#define EEPROM_MAX_SIZE 4096
EEPROMSaver::EEPROMSaver()
{
}

EEPROMSaver::~EEPROMSaver()
{
}

char * readEEPROMData(uint16_t &cursor)
{
    size_t size=EEPROM.read(cursor++);
    if(size== 0)
        return "";
    char *values=(char*)calloc(size+2,(sizeof(char)));
    for (size_t i = 0; i < size; i++)
    {
        values[i]=EEPROM.read(cursor++);
    }
    values[size]='\0';
    return values;
}

void writeEEPROMData(uint16_t &cursor,String s)
{
    size_t size=s.length();
    EEPROM.write(cursor++,size);
    for (size_t i = 0; i < size; i++)
    {
        EEPROM.write(cursor++,s.charAt(i));
    }
}

ConnectData *EEPROMSaver::read(){
    EEPROM.begin(EEPROM_MAX_SIZE);
    uint16_t cursor=0;
    if(EEPROM.read(cursor++)!=0xff)
        return nullptr;
    
    // cursor++;
    ConnectData *data= new ConnectData();
    
    data->ssid=readEEPROMData(cursor);
    data->password=readEEPROMData(cursor);
    data->carKey=readEEPROMData(cursor);
    EEPROM.end();
    return data;
}

void EEPROMSaver::write(ConnectData *data)
{
    EEPROM.begin(EEPROM_MAX_SIZE);
    uint16_t cursor=0;
    EEPROM.write(cursor,0xff);
    cursor++;
    writeEEPROMData(cursor,data->ssid);
    writeEEPROMData(cursor,data->password);
    writeEEPROMData(cursor,data->carKey);
    EEPROM.commit();
    EEPROM.end();
}