//////////////////////////////////////
// See "The Target files" documentation
//////////////////////////////////////

#include "papyMonitor.hpp"

uint8_t inputStates;
uint8_t outputStates;

sVariables_t variables[] = {
  { &outputStates, eComDataType_U8, eReportOn, NULL }, // index 0 in the .lua file
  { &inputStates, eComDataType_U8, eReportOn, NULL },  // index 1 in the .lua file
};

const uint8_t nbVariables = sizeof( variables ) / sizeof( sVariables_t );
Monitoring myMonitor( &Serial, variables, nbVariables );

void setup() {
  for (uint8_t i=2; i<8; i++) {
    pinMode(i, OUTPUT);
  }
  for (uint8_t i=8; i<14; i++) {
    pinMode(i, INPUT);
  }  
  outputStates = 0;
}

void loop() {

    // Other code here

    for (uint8_t i=2; i<8; i++) {
      digitalWrite(i, (outputStates & (1<<i)) >> i );
    }

    inputStates = 0;
    for (uint8_t i=8; i<14; i++) {
      bitWrite(inputStates, i-8, digitalRead(i));
    }   

    myMonitor.update();
}
