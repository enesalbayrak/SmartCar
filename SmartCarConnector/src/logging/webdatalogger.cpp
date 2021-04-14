#include "webdatalogger.h"
#include <Arduino.h>

WebDataLogger::WebDataLogger()
{
}
void WebDataLogger::log(WebData *data){
    Serial.println("****************WEB DATA****************");
    Serial.print("BackLight:");
    Serial.println(data->backLight);
    Serial.print("headLight:");
    Serial.println(data->headLight);
    Serial.print("longHeadLight:");
    Serial.println(data->longHeadLight);
    Serial.print("hornActivity:");
    Serial.println(data->hornActivity);
    Serial.print("movementDirection:");
    Serial.println(data->movementDirection);
    Serial.print("parkActivity:");
    Serial.println(data->parkActivity);
    Serial.print("signalStatus:");
    Serial.println(data->signalStatus);
    Serial.println("**************WEB DATA END**************");
    delay(2000);

}