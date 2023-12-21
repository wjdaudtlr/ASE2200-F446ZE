/*
 * ih_telemetry.h
 *
 *  Created on: Dec 21, 2023
 *      Author: SURFACE
 */

#ifndef INC_IH_TELEMETRY_H_
#define INC_IH_TELEMETRY_H_

// includes
#include <stdint.h>
#include <stdio.h>
#include <string.h>
// typedefs
typedef struct _IH_UTCTimeTypeDef{
	// hh:mm:ss;
	uint8_t HOUR;
	uint8_t MINUTE;
	uint8_t SECOND;
}IH_UTCTimeTypeDef;

#define DEF_TELEMETRY_TEAM_ID 				2036
#define DEF_TELEMETRY_STATE_STRING_SIZE 	20
#define DEF_TELEMETRY_CMD_STRING_SIZE 		8
#define DEF_TELEMETRY_STRING_SIZE 			128
#define DEF_TELEMETRY_FIELD_STRING_SIZE 	20

typedef struct _IH_TelemetryDataTypeDef{
	// must included ---------------------------------------------------------
	uint16_t TEAM_ID;
	IH_UTCTimeTypeDef MISSION_TIME;
	uint16_t PACKET_COUNT;
	uint8_t MODE;
	char STATE[DEF_TELEMETRY_STATE_STRING_SIZE];
	float ALTITUDE;
	float AIR_SPEED;
	uint8_t HS_DEPLOYED;
	uint8_t PC_DEPLOYED;
	float TEMPERATURE;
	float VOLTAGE;
	float PRESSURE;
	IH_UTCTimeTypeDef GPS_TIME;
	float GPS_ALTITUDE;
	float GPS_LATITUDE;
	float GPS_LONGITUDE;
	uint8_t GPS_SATS;
	float TILT_X;
	float TILT_Y;
	float ROT_Z;
	char CMD_ECHO[DEF_TELEMETRY_CMD_STRING_SIZE];
	// optional data ---------------------------------------------------------

}IH_TelemetryDataTypeDef;

// defines

// prototypes
// UTC time
void IH_UTCTime_AddSecond(IH_UTCTimeTypeDef *IH_UTCTime);
// void IH_UTCTime_AddMinute(IH_UTCTimeTypeDef *IH_UTCTime, uint8_t minutes);
// void IH_UTCTime_AddHour(IH_UTCTimeTypeDef *IH_UTCTime, uint8_t hours);
void IH_UTCTime_SetTime(IH_UTCTimeTypeDef *IH_UTCTime, uint8_t hour, uint8_t minute, uint8_t second);
void IH_UTCTime_CopyTime(IH_UTCTimeTypeDef *IH_UTCTime_dest, IH_UTCTimeTypeDef *IH_UTCTime_source);
void IH_UTCTime_GetString(char* str, IH_UTCTimeTypeDef *IH_UTCTime);

// Telemetry
void IH_TelemetryData_GetString(char* str, IH_TelemetryDataTypeDef *IH_TelemetryData);

#endif /* INC_IH_TELEMETRY_H_ */
