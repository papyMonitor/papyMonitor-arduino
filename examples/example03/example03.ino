
/*
 * Example that
 * 
 * read analog port A0 to A5
 * 
 * To papyMonitor
 */
#include "papyMonitor.hpp"

float analogValues[6];

sVariables_t variables[] = {
  { &analogValues[0], eComDataType_Float, eReportOn, NULL }, // index 0 in the .lua file
  { &analogValues[1], eComDataType_Float, eReportOn, NULL },
  { &analogValues[2], eComDataType_Float, eReportOn, NULL },
  { &analogValues[3], eComDataType_Float, eReportOn, NULL },
  { &analogValues[4], eComDataType_Float, eReportOn, NULL },
  { &analogValues[5], eComDataType_Float, eReportOn, NULL }, // index 5 in the .lua file
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

}

void loop() {

    analogValues[0] = (float)analogRead(A0);
    analogValues[1] = (float)analogRead(A1);
    analogValues[2] = (float)analogRead(A2);
    analogValues[3] = (float)analogRead(A3);
    analogValues[4] = (float)analogRead(A4);
    analogValues[5] = (float)analogRead(A5);

    myMonitor.update();
}
