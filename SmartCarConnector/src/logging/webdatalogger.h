#ifndef WEBDATALOGGER_H
#define WEBDATALOGGER_H
#include <client/webdata.h>
class WebDataLogger
{
private:
    /* data */
    WebDataLogger(/* args */);
public:
    static void log(WebData *data);        
};


#endif