/*
 * commnad_parser_fsm.c
 *
 *  Created on: Dec 3, 2022
 *      Author: Admin
 */
#include "commnad_parser_fsm.h"

//Function Prototyping
uint8_t checkRST(void);
uint8_t checkOK(void);
void clearBuffer();
//END Function Prototyping
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer = 0;

uint8_t isRST;
uint8_t isOK;

char * string_buffer;

void command_parser_fsm (){
	switch (parserStatus){
	case INIT:	//INIT
		if(isRST == 1){
			sensor_flag = 1;//print
			isRST = 0;
			parserStatus = WRITE;
		}
		break;
	case WRITE: //WRITE TO TERMINAL
		//TODO PRINT DATA
		sensor_flag = 1;
		setTimer1(PARSER_TIME_OUT);
		parserStatus = WAIT;
		break;
 	case WAIT:	//WAIT FOR OK CMD
 		if(isRST == 1){
 			//PRINT
 			isRST =  0;
 			sensor_flag = 1;
 			setTimer1(0);//delete timer
 			parserStatus = WRITE;
 			break;
 		}
 		if(isOK == 1){
// 			DONE
 			sensor_flag = 0;
 			setTimer1(0);
 			isOK = 0;
 			parserStatus = INIT;
 			break;
 		}
 		if(timer1_flag == 1){
 			//DONE
 			sensor_flag = 1;
 			parserStatus = WRITE;
 			//HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);
 			timer1_flag = 0;
 			break;
 		}
		break;
 	default:
 		break;
	}


}
void updateBuffer(uint8_t value){
	uint8_t *checkEnter = (uint8_t *)"\r\n";
	isRST = checkRST();
	isOK = checkOK();
	buffer[index_buffer] = value;
	index_buffer = (index_buffer + 1) % MAX_BUFFER_SIZE; //ENSURE NO EXCEED MAX SIZE

//	if(value == *checkEnter){
//		isRST = checkRST();
//		isOK = checkOK();
//		clearBuffer();
//	}
//	else{
//
//	}
	string_buffer = (char*) buffer;
}
void clearBuffer(void){
	for(uint8_t i = 0;i<index_buffer;i++){
		buffer[i] = 0;
	}
	index_buffer = 0;
}
uint8_t checkRST(void){
	char * requestCmd = (char *)"!RST#";
	if(strcmp(string_buffer,requestCmd) == 0){
		return 1;
	}
	return 0;
}
uint8_t checkOK(void){
	char * requestCmd = (char *)"!OK#";
	if(strcmp(string_buffer,requestCmd) == 0){
		return 1;
	}
	return 0;
}
