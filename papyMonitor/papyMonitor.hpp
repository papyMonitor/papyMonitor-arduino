/*
 * monitoringArdu.hpp
 *
 *  Created on: 22 dec. 2021
 *      Author: papyDoctor
 */

#ifndef PAPYMONITOR_H_
#define PAPYMONITOR_H_

#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"
#include "string.h"

#include "Arduino.h"
#include "HardwareSerial.h"

// Meaning codes
typedef enum {
    // Commands from monitor to target;
    eSetValue = '#',
    eReportValueOn = '?',
    eReportValueOff = '!',

    // Messages from target to monitor
    eIReportValue =        ':',
    eIReportTextConsole =  '>',
} eHostMonitoringCmd_t;

typedef enum {
	eComDataType_Float		= 'f', // 8 chars
	eComDataType_U32 		= 'W', // 8 chars
	eComDataType_I32 		= 'w', // 8 chars
	eComDataType_U16 		= 'I', // 4 chars
	eComDataType_I16 		= 'i', // 4 chars
	eComDataType_U8 		= 'B', // 2 chars
	eComDataType_I8 		= 'b', // 2 chars
} eDataType_t;

typedef enum {
	eNeverReport,
	eReportOn,
	eReportOff,
} eReportType_t;

typedef struct {
	void* data;
	eDataType_t type;
	bool report;
	void (*cb)(uint8_t); // Callback with index of the variable in the table as argument
} sVariables_t;


#define  MAXCHARBUFARRIVED	20

class Monitoring {
	/*****************************************************************************
	 * Private functions
	 ****************************************************************************/
	private:
		bool firstPass;
		uint8_t nbVariables;
		sVariables_t* variables;
		HardwareSerial* Serial;
		uint32_t baudrate;
		char msgFromHost[MAXCHARBUFARRIVED];
		char internBuff[MAXCHARBUFARRIVED];
		uint8_t idxInternBuff;
		unsigned long currentMillis, previousMillis, interval;

		void getValueFromHex( eDataType_t varType, void* value, char* dataRx );

		void setValue( char* dataRx );
		void variablesSend( uint32_t index );
		void variablesSendNext( void );
		void setVariablesReporting( char* dataRx, bool set );

		bool parseInBuffer( char * inBuffer, uint8_t nbChar );

	public:
	/*****************************************************************************
	 * Public function must be called every X microsecond
	 ****************************************************************************/
		/*
		* Every X microsecond
		* 1. Report variables every report period (if requested)
		*  OR
		* 2. Interpret and execute command from host
		*/
		void update( void );
		void print( const char* msg );

		// Optional helper functions
		bool setVariablesReportingAllOn( uint8_t dummy );
		bool setVariablesReportingAllOff( uint8_t dummy );

		Monitoring( HardwareSerial* _Serial, 
			sVariables_t* _variables, uint8_t _nbVariables,
			uint32_t _baudrate = 230000 );
};

#endif /* PAPYMONITOR_H_ */
