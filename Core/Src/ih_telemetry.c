/*
 * ih_telemetry.c
 *
 *  Created on: Dec 21, 2023
 *      Author: SURFACE
 */
// includes
#include "ih_telemetry.h"
// types

// variables

// constants

// function prototypes

// functions

// UTC time
void IH_UTCTime_AddSecond(IH_UTCTimeTypeDef *IH_UTCTime){
	IH_UTCTime->SECOND++;
	if (IH_UTCTime->SECOND >= 60){
		IH_UTCTime->MINUTE++;
		IH_UTCTime->SECOND = 0;
	}
	if (IH_UTCTime->MINUTE >= 60){
		IH_UTCTime->HOUR++;
		IH_UTCTime->MINUTE = 0;
	}
	if (IH_UTCTime->HOUR >= 24){
		IH_UTCTime->HOUR = 0;
	}
}
void IH_UTCTime_SetTime(IH_UTCTimeTypeDef *IH_UTCTime, uint8_t hour, uint8_t minute, uint8_t second){
	IH_UTCTime->HOUR = hour;
	IH_UTCTime->HOUR = minute;
	IH_UTCTime->HOUR = second;
}
void IH_UTCTime_CopyTime(IH_UTCTimeTypeDef *IH_UTCTime_dest, IH_UTCTimeTypeDef *IH_UTCTime_source){
	memcpy(IH_UTCTime_dest, IH_UTCTime_source, sizeof(IH_UTCTimeTypeDef));
}
void IH_UTCTime_GetString(char* str, IH_UTCTimeTypeDef *IH_UTCTime){
    str[0] = '0';
    str[3] = '0';
    str[6] = '0';

    sprintf(str +     (IH_UTCTime->HOUR  >10 ? 0 : 1), "%d", IH_UTCTime->HOUR);
    sprintf(str + 3 + (IH_UTCTime->MINUTE>10 ? 0 : 1), "%d", IH_UTCTime->MINUTE);
    sprintf(str + 6 + (IH_UTCTime->SECOND>10 ? 0 : 1), "%d", IH_UTCTime->SECOND);

    str[2] = ':';
    str[5] = ':';
}
// Telemetry
void IH_TelemetryData_GetString(char* str, IH_TelemetryDataTypeDef *IH_TelemetryData){
	int idx = 0;

	idx += sprintf(str+idx, "%d", IH_TelemetryData->TEAM_ID);
	str[idx] = ',';
	idx++;

    IH_UTCTime_GetString(str+idx, &(IH_TelemetryData->MISSION_TIME));
    idx += 8;
	str[idx] = ',';
	idx++;

	idx += sprintf(str+idx, "%d", IH_TelemetryData->PACKET_COUNT);
	str[idx] = ',';
	idx++;

	idx += sprintf(str+idx, "%c", IH_TelemetryData->MODE);
	str[idx] = ',';
	idx++;

	idx += sprintf(str+idx, "%s", IH_TelemetryData->STATE);
	str[idx] = ',';
	idx++;

	idx += sprintf(str+idx, "%.1f", IH_TelemetryData->ALTITUDE);
	str[idx] = ',';
	idx++;

	idx += sprintf(str+idx, "%.1f", IH_TelemetryData->AIR_SPEED);
	str[idx] = ',';
	idx++;

	idx += sprintf(str+idx, "%c", IH_TelemetryData->HS_DEPLOYED);
	str[idx] = ',';
	idx++;

	idx += sprintf(str+idx, "%c", IH_TelemetryData->PC_DEPLOYED);
	str[idx] = ',';
	idx++;

	idx += sprintf(str+idx, "%.1f", IH_TelemetryData->TEMPERATURE);
	str[idx] = ',';
	idx++;

	idx += sprintf(str+idx, "%.1f", IH_TelemetryData->VOLTAGE);
	str[idx] = ',';
	idx++;

	idx += sprintf(str+idx, "%.1f", IH_TelemetryData->PRESSURE);
	str[idx] = ',';
	idx++;

    IH_UTCTime_GetString(str+idx, &(IH_TelemetryData->GPS_TIME));
    idx += 8;
	str[idx] = ',';
	idx++;

	idx += sprintf(str+idx, "%.1f", IH_TelemetryData->GPS_ALTITUDE);
	str[idx] = ',';
	idx++;

	idx += sprintf(str+idx, "%.4f", IH_TelemetryData->GPS_LATITUDE);
	str[idx] = ',';
	idx++;

	idx += sprintf(str+idx, "%.4f", IH_TelemetryData->GPS_LONGITUDE);
	str[idx] = ',';
	idx++;

	idx += sprintf(str+idx, "%d", IH_TelemetryData->GPS_SATS);
	str[idx] = ',';
	idx++;

	idx += sprintf(str+idx, "%.2f", IH_TelemetryData->TILT_X);
	str[idx] = ',';
	idx++;

	idx += sprintf(str+idx, "%.2f", IH_TelemetryData->TILT_Y);
	str[idx] = ',';
	idx++;

	idx += sprintf(str+idx, "%.1f", IH_TelemetryData->ROT_Z);
	str[idx] = ',';
	idx++;

	idx += sprintf(str+idx, "%s", IH_TelemetryData->CMD_ECHO);
	str[idx] = '\0';
}
