/*
 * global.c
 *
 *  Created on: Dec 3, 2022
 *      Author: Admin
 */
#include "global.h"

int parserStatus = INIT;
int sensorStatus = SENSOR_INIT;
int sensor_flag = 0;


uint8_t temp = 0;
uint8_t buffer_flag = 1;
int ADC_value =0;
