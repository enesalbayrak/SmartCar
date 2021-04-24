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
    Serial.println(data->headLightPercent);
    Serial.print("Buzzer:");
    Serial.println(data->buzzerStatus);
    Serial.print("hornActivity:");
    Serial.println(data->movementDirection);
    Serial.print("signalStatus:");
    Serial.println(data->signalStatus);
    Serial.println("**************WEB DATA END**************");
    delay(2000);

}