#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/event_groups.h"

#define DEBUG 0

#if DEBUG == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif

volatile int stopSignal = 0;
volatile int received_num = 0;

void counter(){
  int count = 0;
  debug("received value:");
  debug(received_num);
  while(count < 100 && stopSignal != 1){
    received_num++;
    count++;
    vTaskDelay(1000/portTICK_PERIOD_MS);
    debugln("counter:");
    debug(received_num);
  }
}

void setup(){
  Serial.begin(115200);
}

void loop(){
  if(Serial.available()){
    String input = Serial.readString();
    if(input == "stop"){
      stopSignal = 1;
    } else if(isNumeric(input)){
      received_num = input.toInt();
      stopSignal = 0;
      counter();
    }
  }
}

bool isNumeric(String str){
  for(byte i = 0; i<str.length(); i++){
    if(!isDigit(str[i])){
      return false;
    }
  }
  return true;
}
