#include "papyMonitor.hpp"

// Some variables to monitor
// These are the declaration of the variables we want to monitor. They must be
// Declared before the "sVariables_t variables[]"
float myFloat;  
uint8_t myByte;

// In order for the library to work, we need to tell it what variable
// to monitor, this is done in the sVariables_t variables[]
// In the sVariables_t variables[] we put one line per variable
// Each line contains 4 fields
// 1. The variable pointer (simply put a & in front of your variable)
// 2. The variable type (see papyMonitor.hpp),
// 3. A flag that contains the reporting status (eNeverReport, eReportOff, eReportOn)
//    leave it at eReportOn for the moment
// 4. A Callback function, leave at NULL for the moment
sVariables_t variables[] = {
  { &myFloat, eComDataType_Float, eReportOn, NULL },  //index 0 in the .lua file
  { &myByte, eComDataType_U8, eReportOn, NULL },      //index 1 in the .lua file
};
// The variables[] is in fact an array whose elements have an index. This is
// very important to note since each index is related with a peculiar variable
// and will be required in the .lua configuration file for the papyMonitor-gui

/****************************************************************
 *****   Monitoring initialisation, do not modify this !!!  *****
 ****************************************************************/
const uint8_t nbVariables = sizeof( variables ) / sizeof( sVariables_t );
Monitoring myMonitor( &Serial, variables, nbVariables );
/****************************************************************
 ****************************************************************
 ****************************************************************/
// a variable not monitored
uint8_t counter;

void setup() {
  // Initialization of the variables
  myFloat = 0.0f;
  myByte = 0;

  counter = 0;
}

void loop() {

    // Main program
    if (++counter==10)
    {
      // We increment the myByte value from 0 to 255 forever
      myByte++;

      counter = 0;
    }

    
    // We increment the myFloat value from 0 to 100 forever
    // in step of 0.01
    myFloat += 0.01f;
    if (myFloat >= 100.0f)
      myFloat = 0.0f;


    // You need only this for the monitoring to work :)
    // This is a call to the library. For simplicity, call
    // act like a timer, it is blocking and unblock every 1ms
    // Further behaviour will be available if requested
    myMonitor.update();
}
