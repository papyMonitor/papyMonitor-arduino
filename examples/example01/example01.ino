//////////////////////////////////////
// See "The Target files" documentation
//////////////////////////////////////

#include "papyMonitor.hpp"

float myFloat;  
uint8_t myByte;

sVariables_t variables[] = {
  { &myFloat, eComDataType_Float, eReportOn, NULL },  //index 0 in the .lua file
  { &myByte, eComDataType_U8, eReportOn, NULL },      //index 1 in the .lua file
};

const uint8_t nbVariables = sizeof( variables ) / sizeof( sVariables_t );
Monitoring myMonitor( &Serial, variables, nbVariables );

uint8_t counter;

void setup() {
  myFloat = 0.0f;
  myByte = 0;
  counter = 0;
}

void loop() {

    // Other code here

    if (++counter==10) {
      myByte++;
      counter = 0;
    }

    myFloat += 0.01f;
    if (myFloat >= 100.0f)
      myFloat = 0.0f;

    myMonitor.update();
}
