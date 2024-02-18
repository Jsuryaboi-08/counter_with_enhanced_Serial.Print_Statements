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

void counter(int received_num){
  debug("received value:");
  debug(received_num);
  int hundredcount = received_num;
  while(stopSignal != 1){
    received_num++;
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
      int num = input.toInt();
      stopSignal = 0;
      counter(num);
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
