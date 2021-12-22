#include "papyMonitor.hpp"

/***********************************************
 * VARIABLES TO MONITOR HERE
 ***********************************************/
float myFloat;
uint8_t myByte;

sVariables_t variables[] = {
  // FOUR fields for each line:
  // 1. Your variable pointer (simply put a & in front of your variable)
  // 2. The variable type (see .lua file or papyMonitor.hpp),
  // 3. Monitoring internal value, always set to false, 
  // 4. Callback function (set to NULL if no callback)
  { &myFloat, eComDataType_Float, eReportOn, NULL },  //index 0 in the .lua file
  { &myByte, eComDataType_U8, eReportOn, NULL },      //index 1 in the .lua file
};

/****************************************************************
 *****   Monitoring initialisation, do not modify this !!!  *****
 ****************************************************************/
const uint8_t nbVariables = sizeof( variables ) / sizeof( sVariables_t );
Monitoring myMonitor( &Serial, variables, nbVariables );
/****************************************************************
 ****************************************************************
 ****************************************************************/

void setup() {

  myFloat = 0.0f;
  myByte = 0;
}


void loop() {

    myFloat += 0.01f;
    if (myFloat >= 100.0f)
      myFloat = 0.0f;

    myByte++;

    // You need only this for the monitoring to work :)
    myMonitor.update();
}
