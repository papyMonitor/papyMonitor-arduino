# papyMonitor Arduino examples

This folder contains various examples in order to understand the tool. The example numbers (exampleXX) are related with the complexity of the sketchs. 

## Installation

Copy each exampleXX to a folder of your choice. You **must** have put the library **papyMonitor** to your sketch location (see README in the "papyMonitor-arduino" folder)

## Usage/Documentation

Each stetch has some mandatory lines, the minimal sketch to use the library is given here after

```cpp
// Mandatory include
#include "papyMonitor.hpp"

/***********************************************
 * VARIABLES TO MONITOR HERE
 ***********************************************/
// ...
// ...
// ...

sVariables_t variables[] = {

  // ...
  // ...
  // ...
};

/****************************************************************
 *****   Monitoring initialization, DO NOT MODIFY THIS !!!  *****
 ****************************************************************/
const uint8_t nbVariables = sizeof( variables ) / sizeof( sVariables_t );
Monitoring myMonitor( &Serial, variables, nbVariables );
/****************************************************************
 *****   End of Monitoring initialization                    *****
 ****************************************************************/

void setup() {

  // ...
  // ...
  // ...
}

void loop() {

  // ...
  // ...
  // ...

  // You need to add this line on each sketch you make
  // This line call the monitoring engine for the communication
  // with the papyMonitor-gui application
  myMonitor.update();
}
```

Of course, this code is useless but shows what is absolutelly necessary in your sketch.


Let see the example01.ino:

```cpp
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
```

