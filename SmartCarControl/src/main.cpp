#include <Arduino.h>
#include <carmanager.h>
#include <motor/motor.h>
CarManager * manager;
int timer1_counter;
// Motor motor(2,3);
uint16_t x=900;
long lastMs=millis();
void setup() {
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  digitalWrite(3,LOW); 
  // manager= new CarManager();
  //  noInterrupts();           // disable all interrupts
  // TCCR1A = 0;
  // TCCR1B = 0;

  // // Set timer1_counter to the correct value for our interrupt interval
  // //timer1_counter = 64911;   // preload timer 65536-16MHz/256/100Hz
  // //timer1_counter = 64286;   // preload timer 65536-16MHz/256/50Hz
  // timer1_counter = 34286;   // preload timer 65536-16MHz/256/2Hz
  
  // TCNT1 = timer1_counter;   // preload timer
  // TCCR1B |= (1 << CS12);    // 256 prescaler 
  // TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  // interrupts();             // enable all interrupts
}

// ISR(TIMER1_OVF_vect)        // interrupt service routine 
// {
//   TCNT1 = timer1_counter;   // preload timer
// }
void loop() {
  digitalWrite(2,HIGH);
  delayMicroseconds(x);
  digitalWrite(2,LOW);
  delayMicroseconds(1000-x);
  if(millis()-lastMs>1000){
    Serial.println(x);
    x+=100;
    lastMs=millis();
    if(x>1000)
      x=0;
  }
  // manager->loop();
}