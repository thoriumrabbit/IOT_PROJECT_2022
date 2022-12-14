/*
 * global.h
 *
 *  Created on: Dec 3, 2022
 *      Author: Admin
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

/*INCLUDES*/
#include "main.h"
#include "read_sensor.h"
#include "commnad_parser_fsm.h"
#include "software_timer.h"
#include <stdio.h>
#include <string.h>
/*END INCLUDES*/

#define INIT 		1
#define WAIT		2
#define WRITE		3
#define MAX_BUFFER_SIZE 30

#define SENSOR_INIT	11
#define SENSOR_WAIT	12
#define SENSOR_READ	13


#define PARSER_TIME_OUT		3000
#define SENSOR_DELAY		500

extern int parserStatus;
extern int sensorStatus;
extern int sensor_flag;


extern uint8_t temp;
extern int ADC_value_RT;
extern int ADC_value_RH;

extern uint8_t buffer [ MAX_BUFFER_SIZE ];
extern uint8_t index_buffer;
extern uint8_t buffer_flag;
#endif /* INC_GLOBAL_H_ */
