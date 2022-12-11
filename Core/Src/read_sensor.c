/*
 * read_sensor.c
 *
 *  Created on: Dec 5, 2022
 *      Author: Admin
 */

#include "read_sensor.h"



void read_sensor_fsm(){
	switch (sensorStatus){
	case SENSOR_INIT:
		sensorStatus = SENSOR_WAIT;
		break;
	case SENSOR_WAIT:
		if(sensor_flag == 1){
			setTimer2(SENSOR_DELAY);
			sensorStatus = SENSOR_READ;
		}
		break;
	case SENSOR_READ:
		if(sensor_flag == 0){
			sensorStatus = SENSOR_WAIT;
		}
		if(timer2_flag == 1){
			Read_Value();
			setTimer2(PARSER_TIME_OUT);
		}
		break;
	default:
		break;
	}
}
