 #include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>
#include <inttypes.h>
#include <semphr.h>

/*
 * ARTS-Lab-2016, HHs Electrotechniek, W.Muhammad
 * Assignment 3- Project Template

     */

#define SEC             1100000

//turn led defines
#define ALL_OFF         0
#define RIGHT_HALF      9
#define TOGGLE          10
#define MIDDLE			11

#define TIMER_COUNTER   96000   //500Hz
#define TRUE			1
#define FALSE			0


#define PULSE_LENGTH	5
#define PULSES_TO_SKIP	2

#define UP_UNTOUCHED	1655
#define UP_TOUCHED		1552

#define RIGHT_UNTOUCHED	1761
#define RIGHT_TOUCHED	1663

#define DOWN_UNTOUCHED	2400
#define DOWN_TOUCHED	2200

#define LEFT_UNTOUCHED	2271
#define LEFT_TOUCHED	2095

//direction defines
#define UP				1
#define DOWN			2
#define LEFT			3
#define RIGHT			4
#define STOP			5
#define OFF				0


long step = 0;

uint32_t klok = 0;
volatile uint32_t i;
long capValue;

int dirPressed = OFF;
xSemaphoreHandle semMutex = NULL;


extern void init(void);
void delay(int x){
    for(i=0; i<x; i++){
    }
}

void turnOnLED(int s){
	if(s <= 0)		//led off
		turnLED(ALL_OFF);

	//turns on LED if between:
	else if(s < 5)	//1-4
		turnLED(1);

	else if(s < 8)	//5-7
		turnLED(2);

	else if(s < 11)	//8-10
		turnLED(3);

	else if(s < 17)	//11-16
		turnLED(4);

	else if(s < 22)	//17-21
		turnLED(5);

	else if(s < 25)	//22-24
		turnLED(6);

	else if(s < 27)	//24-26
		turnLED(7);

	else 			//27-32
		turnLED(8);
}

void initCap(int cap){
	switch(cap){
		case UP:
			CAPTIO0CTL = (CAPTIOPOSEL_5 + CAPTIOPISEL_2 + CAPTIOEN);
			break;

		case DOWN:
			CAPTIO0CTL = (CAPTIOPOSEL_6 + CAPTIOPISEL_4 + CAPTIOEN);
			break;

		case LEFT:
			CAPTIO0CTL = (CAPTIOPOSEL_6 + CAPTIOPISEL_5 + CAPTIOEN);
			break;

		case RIGHT:
			CAPTIO0CTL = (CAPTIOPOSEL_3 + CAPTIOPISEL_6 + CAPTIOEN);
			break;

		case STOP:
			CAPTIO0CTL = (CAPTIOPOSEL_5 + CAPTIOPISEL_0 + CAPTIOEN);
			break;
	}

	TA2CTL |= ( MC__CONTINUOUS | TACLR | TASSEL_3);
}


//--------------------sensor readings-------------------<<

long 	capValueUP, capValueDOWN, capValueLEFT, capValueRIGHT,
		upperHalf, lowerHalf;

//long upness = 0, rightness = 0, downness = 0, leftness = 0;
long 	max_upness 	= 	UP_UNTOUCHED 	- UP_TOUCHED,
		max_rightness = RIGHT_UNTOUCHED - RIGHT_TOUCHED,
		max_downness = 	DOWN_UNTOUCHED 	- DOWN_TOUCHED,
		max_leftness = 	LEFT_UNTOUCHED 	- LEFT_TOUCHED;

uint up_percentage, right_percentage, down_percentage, left_percentage;


int skip, measure;

long getCapValue(int capDir){
	skip = PULSES_TO_SKIP, measure = PULSE_LENGTH;
	initCap(capDir);

	//skip first 2 samples
	while(skip--){
		TA2CTL |= TACLR;
		vTaskDelay(1);
		capValue = TA2R;
	}
	while(measure--){
		TA2CTL |= TACLR;
		vTaskDelay(1);
		capValue = TA2R;
	}
	return capValue;
}

int getPercentage(ulong capRaw, ulong untouchedTreshold, ulong max_dirNess){
	ulong dirNess;
	int dirPercentage;

	if(capRaw < untouchedTreshold-5){
			dirNess = untouchedTreshold - capRaw;
	}else{
			dirNess = 0;
	}

	dirPercentage = (double)dirNess/(double)max_dirNess * 100.0;

	return dirPercentage;
}



void capCheckerUP(void *pvParameters){
	capValueUP = 0;
	up_percentage =0;

	while(1){
		if (xSemaphoreTake(semMutex, 200)){

			capValueUP = getCapValue(UP);
			up_percentage = getPercentage(capValueUP, UP_UNTOUCHED, max_upness);

			//indicate (with negative) if left side is touched
			if (left_percentage > right_percentage){
				upperHalf = -1* up_percentage;
			}else{
				upperHalf = up_percentage;
			}

			xSemaphoreGive(semMutex);
			vTaskDelay(1);
		}

	}
}

void capCheckerRIGHT(void *pvParameters){
	capValueRIGHT = 0;
	 right_percentage =0;

	while(1){
		if (xSemaphoreTake(semMutex, 200)){

			capValueRIGHT = getCapValue(RIGHT);
			right_percentage = getPercentage(capValueRIGHT, RIGHT_UNTOUCHED, max_rightness);

			xSemaphoreGive(semMutex);
			vTaskDelay(1);
		}
	}
}

void capCheckerDOWN(void *pvParameters){
	capValueDOWN = 0;
	down_percentage =0;

	while(1){
		if (xSemaphoreTake(semMutex, 200)){

			capValueDOWN = getCapValue(DOWN);
			down_percentage = getPercentage(capValueDOWN, DOWN_UNTOUCHED, max_downness);

			//indicate (with negative) if right side is touched
			if(right_percentage > left_percentage){
				lowerHalf = -1 * down_percentage;
			}else{
				lowerHalf = down_percentage;
			}

			xSemaphoreGive(semMutex);
			vTaskDelay(1);
		}
	}
}

void capCheckerLEFT(void *pvParameters){
	capValueLEFT = 0;
	left_percentage =0;

	while(1){
		if (xSemaphoreTake(semMutex, 200)){

			capValueLEFT = getCapValue(LEFT);
			left_percentage = getPercentage(capValueLEFT, LEFT_UNTOUCHED, max_leftness);

			xSemaphoreGive(semMutex);
			vTaskDelay(1);
		}
	}
}

void calculateStep(){
	//if upper half was touched
	if (upperHalf < 0){//if leftside of upperhalf is touched
		step = 2400 - (8* upperHalf);
	}else if (upperHalf > 0){//if rightside of upperhalf is touched
		step = 800 - (8 * upperHalf);
	}

	//if lower half is touched
	else{
		if (lowerHalf < 0){//if leftside of lowerhalf is touched
			step = 800 + (-8* lowerHalf);
		}else if (lowerHalf > 0){//if rightside of lowerhalf is touched
			step = 2400 - (8 * lowerHalf);
		}else{//if nothing is touched
			step = 0;
		}
	}
	step = (step+50)/100;	//+50 for rounding
}

void indicateLED(void *pvParameters){
	step = 0;

	while(1){
		if (xSemaphoreTake(semMutex, 200)){

			calculateStep();
			turnOnLED(step);

			xSemaphoreGive(semMutex);
			vTaskDelay(1);
		}
	}
}


int main(void) {
    WDTCTL = WDTPW | WDTHOLD;  /* Stop watchdog timer */

    init();
    klok = CS_getMCLK();
    printf("Kloksnelheid is: %" PRIu32 "\n", klok);

    semMutex = xSemaphoreCreateMutex();

    //task checking the amount of touch is present on it's capacitive touch pad
    xTaskCreate(capCheckerUP, (signed char*)"capChecker1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(capCheckerRIGHT, (signed char*)"capChecker2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(capCheckerDOWN, (signed char*)"capChecker3", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(capCheckerLEFT, (signed char*)"capChecker3", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    //task to interpret the position (based on the touch percentages) and turn on a LED accordingly
    xTaskCreate(indicateLED, (signed char*)"indicateLED", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    vTaskStartScheduler();

    while(1);

    return 0;
}
