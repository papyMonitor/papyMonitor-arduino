/*
 * papyMonitor.cpp
 *
 *  Created on: 22 dec. 2021
 *      Author: papyDoctor
 */

#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"
#include "string.h"
#include "math.h"

#include "papyMonitor.hpp"

#include "Arduino.h"
#include "HardwareSerial.h"

// mapping of ASCII characters to hex values
static const uint8_t hashmap[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, //  !"#$%&'
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ()*+,-./
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, // 01234567
  0x08, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 89:;<=>?
  0x00, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00, // @ABCDEFG
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // HIJKLMNO
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // PQRSTUVW
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // XYZ[\]^_
  0x00, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x00, // `abcdefg
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // hijklmno
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // pqrstuvw
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // xyz{|}~.
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ........
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // ........
};

void Monitoring::getValueFromHex( eDataType_t varType, void* value, char* dataRx ) {

	uint8_t var1;
	uint8_t pVar2[2];
	uint8_t pVar4[4];

	switch ( varType ) {

		// mem: 4 bytes types
		case eComDataType_Float:
		case eComDataType_U32:
		case eComDataType_I32:
			// form of '?XXYWWWWWWWW\0' only
			if ( (dataRx[12] == '\0')) {
				pVar4[0] = (uint8_t)(hashmap[(uint8_t)dataRx[4]] << 4) | hashmap[(uint8_t)dataRx[5]];
				pVar4[1] = (uint8_t)(hashmap[(uint8_t)dataRx[6]] << 4) | hashmap[(uint8_t)dataRx[7]];
				pVar4[2] = (uint8_t)(hashmap[(uint8_t)dataRx[8]] << 4) | hashmap[(uint8_t)dataRx[9]];
				pVar4[3] = (uint8_t)(hashmap[(uint8_t)dataRx[10]] << 4) | hashmap[(uint8_t)dataRx[11]];
				// Store the variable
				memcpy( value, pVar4, 4 );
			}
			break;

		// mem: 2 bytes types
		case eComDataType_U16:
		case eComDataType_I16:
			// form of '?XXYWWWW\0' only
			if ( (dataRx[8] == '\0') ) {
				pVar2[0] = (uint8_t)(hashmap[(uint8_t)dataRx[4]] << 4) | hashmap[(uint8_t)dataRx[5]];
				pVar2[1] = (uint8_t)(hashmap[(uint8_t)dataRx[6]] << 4) | hashmap[(uint8_t)dataRx[7]];
				// Store the variable
				memcpy( value, pVar2, 2 );
			}
			break;

		// mem: 1 byte types A
		case eComDataType_U8:
		case eComDataType_I8:
			// form of '?XXYWW\0' only
			if ( (dataRx[6] == '\0') ) {
				var1 = (uint8_t)(hashmap[(uint8_t)dataRx[4]] << 4) | hashmap[(uint8_t)dataRx[5]];
				*((uint8_t *)value) = var1;
			}
			break;
	}
}

/*****************************************************************************
* Private functions
****************************************************************************/
void Monitoring::setValue( char* dataRx ) {

	uint8_t varIdx;
	eDataType_t varType;

	varIdx = (uint8_t)(hashmap[(uint8_t)dataRx[1]] << 4) | hashmap[(uint8_t)dataRx[2]];

	if ( varIdx < nbVariables ) {

		varType = (eDataType_t)dataRx[3];

		// Value type to store must be the same as the data type
		if ( varType == variables[varIdx].type ) {
			// GetnStore
			getValueFromHex(varType, variables[varIdx].data, dataRx);
			// Call the callback if any
			if ( variables[varIdx].cb != NULL )
				variables[varIdx].cb(varIdx);
		}
	}
}

void Monitoring::variablesSend( uint32_t index ) {

	char msgString[15];

	uint8_t var1;
	uint8_t pVar2[2];
	uint8_t pVar4[4];

	msgString[0] = eIReportValue;
	sprintf( &msgString[1], "%02X", index );
	msgString[3] = variables[index].type;

	switch ( variables[index].type ) {

		// mem: 4 bytes types
		case eComDataType_Float:
		case eComDataType_U32:
		case eComDataType_I32:
			memcpy( pVar4, variables[index].data, 4 );
			sprintf( &msgString[4], "%02X", pVar4[0] );
			sprintf( &msgString[6], "%02X", pVar4[1] );
			sprintf( &msgString[8], "%02X", pVar4[2] );
			sprintf( &msgString[10], "%02X", pVar4[3] );
			msgString[12] = '\n';
			msgString[13] = '\0';
			break;

		// mem: 2 bytes types
		case eComDataType_U16:
		case eComDataType_I16:
			memcpy( pVar2, variables[index].data, 2 );
			sprintf( &msgString[4], "%02X", pVar2[0] );
			sprintf( &msgString[6], "%02X", pVar2[1] );
			msgString[8] = '\n';
			msgString[9] = '\0';
			break;

		// mem: 1 byte types A
		case eComDataType_U8:
		case eComDataType_I8:
			var1 = *((uint8_t *)variables[index].data);
			sprintf( &msgString[4], "%02X", var1 );
			msgString[6] = '\n';
			msgString[7] = '\0';
			break;
	}

	// Send result
	Serial->write( msgString );
}

/*
* Seek and send from the sVariables_t struct for the next variable to report.
* Each time this function is called, the index is set to the next variable
* whose report bit is set to true and send it. When arrived at the end of struct, go
* to the beginning as a loop.
* Detect is no variables have their report bit to true (no endless loop)
*/
void Monitoring::variablesSendNext( void ) {

	static uint32_t index = 0;
	static uint32_t lastIndex = 0;
	bool indexFound = false;

	// Find next index
	while ( true ) {

		if ( ++index == nbVariables )
			index = 0;

		if ( variables[index].report ) {
			indexFound = true;
			break;
		}

		if ( index == lastIndex )
			break;
	}

	if ( indexFound ) {
		lastIndex = index;
		variablesSend( index );
	}
}

void Monitoring::setVariablesReporting( char* dataRx, bool set ) {

	uint8_t varIdx = (uint8_t)(hashmap[(uint8_t)dataRx[1]] << 4) | hashmap[(uint8_t)dataRx[2]];
	uint8_t nbIndexes = (uint8_t)(hashmap[(uint8_t)dataRx[4]] << 4) | hashmap[(uint8_t)dataRx[5]];

	for (uint32_t i=varIdx; i<varIdx+nbIndexes; i++)
	if ( i < nbVariables )
		if (variables[i].report != eNeverReport)
			variables[i].report = set ? eReportOn : eReportOff;
}

bool Monitoring::setVariablesReportingAllOn( uint8_t dummy ) {

	for (uint32_t i=0; i<nbVariables; i++)
		if (variables[i].report == eReportOff)
			variables[i].report = eReportOn;

	return false;
}

bool Monitoring::setVariablesReportingAllOff( uint8_t dummy ) {

	for (uint32_t i=0; i<nbVariables; i++)
		if (variables[i].report != eNeverReport)
			variables[i].report = eReportOff;

	return false;
}


bool Monitoring::parseInBuffer( char * receivedCharsBuffer, uint8_t nbChar ) {
		
	uint8_t idx;
	bool messagePending = false;

	for ( idx = 0; idx<nbChar; idx++ ) {
		if ( receivedCharsBuffer[idx] == '\n' )
			break; // '\n' means complete message arrived
	}
	
	if (idx < nbChar) {
		// A complete line is arrived
		// Create the msgFromHost by concatening elements of internalBuff
		// with the ones of inBuffer until '\n'

		// 1. Copy char (if any) of internBuff to msgFromHost
		for ( uint8_t i = 0; i<idxInternBuff; i++ )
			msgFromHost[i] = internBuff[i];

		// 2. Concatenate inBuffer chars to msgFromHost until '\n'
		for ( uint8_t i = 0; i<idx; i++ )
			msgFromHost[idxInternBuff+i] = receivedCharsBuffer[i];

		// 3. End the msgFromHost buffer with a '\0' (null terminated string
		msgFromHost[idxInternBuff+idx] = 0;

		// 4. Copy the remaining chars (if any) of the inBuffer to internal buffer
		idxInternBuff = 0;
		for ( uint8_t i = idx+1; i<nbChar; i++ )
			internBuff[idxInternBuff++] = receivedCharsBuffer[i];

		// 5. Detect an empty message (we don't deal this)
		if ( msgFromHost[0] != 0 )
			messagePending = true;

	} else {
		// No \n encountered in the inBuffer, add the content to internBuff
		for ( idx = 0; idx<nbChar; idx++ ) {
			internBuff[idxInternBuff++] = receivedCharsBuffer[idx];
			// Check overflow
			if ( idxInternBuff == MAXCHARBUFARRIVED )
				idxInternBuff = 0;
		}
	}
	return messagePending;
}

void Monitoring::print( const char* msg ) {
	Serial->write( eIReportTextConsole );
	Serial->write( msg );
	Serial->write( "\n" );
}

/*****************************************************************************
	* Public function must be called every X microsecond
	****************************************************************************/
/*
* Every X microsecond
* 1. Report variables every report period (if requested)
*  OR
* 2. Interpret and execute command from host
*/
void Monitoring::update( void ) {

	char incomingBuffer[64];
	uint8_t mem[4];
	uint32_t varIdx;
	uint8_t nbBytesArrived;

	bool messagePending = false;

	// If first time update is called, init serial port
	if ( firstPass ) {
		firstPass = false;
			Serial->begin(230400); // 230400 is enought for 1ms variable sample time (max 13 chars per sample)
			while (!Serial); // wait for serial port to connect. Needed for native USB port only
	}
	currentMillis = millis();

	if (currentMillis - previousMillis >= interval) {
		previousMillis = currentMillis;

		// Read if some bytes are arrived
		nbBytesArrived = Serial->available();
		if ( nbBytesArrived > 0) {
			// get allthe bytes arrived
			Serial->readBytes( incomingBuffer, nbBytesArrived );
			// Detect in message
			messagePending = parseInBuffer( incomingBuffer, nbBytesArrived );
		}

		// If a msg received, execute it
		if ( messagePending ) {

			messagePending = false;

			switch ( (eHostMonitoringCmd_t)msgFromHost[0] ) {

				case eSetValue:
					setValue( msgFromHost );
					break;

				case eReportValueOn:
					setVariablesReporting( msgFromHost, true );
					break;

				case eReportValueOff:
					setVariablesReporting( msgFromHost, false );
					break;

				default:
					break;
			}
		}

		// Send next monitoring variable
		variablesSendNext();
	}
}

Monitoring::Monitoring( HardwareSerial* _Serial, 
					sVariables_t* _variables, uint8_t _nbVariables, 
					uint32_t _baudrate ) {

	firstPass = true;
	Serial = _Serial;
	baudrate = _baudrate;
	nbVariables = _nbVariables;
	variables = _variables;

	idxInternBuff = 0;

	previousMillis = 0;
	interval = 1; // 1 millisecond
}
