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

//direction defines
#define UP				1
#define DOWN			2
#define LEFT			3
#define RIGHT			4
#define STOP			5
#define OFF				0

//capacitance thresholds defines
#define THRESHOLD_PROX	19000
#define THRESHOLD_UP	1600
#define THRESHOLD_DOWN	2300
#define THRESHOLD_LEFT	2150
#define THRESHOLD_RIGHT	1700
#define THRESHOLD_STOP	1700

#define PULSE_LENGTH	10
#define PULSES_TO_SKIP	2

uint32_t klok = 0;
volatile uint32_t i;
long capValue;

int dirPressed = OFF;
xSemaphoreHandle semMutex = NULL;

TaskHandle_t ProxSensorUP_Handle = NULL;
TaskHandle_t ProxSensorDOWN_Handle = NULL;
TaskHandle_t ProxSensorLEFT_Handle = NULL;
TaskHandle_t ProxSensorRIGHT_Handle = NULL;
TaskHandle_t ProxSensorSTOP_Handle = NULL;
TaskHandle_t vBlinkLedsHandle = NULL;

typedef struct{
   int dir;
   long  threshold;
}capButton;

capButton buttonUP 		= {UP, 		THRESHOLD_UP};
capButton buttonDOWN 	= {DOWN, 	THRESHOLD_DOWN};
capButton buttonLEFT 	= {LEFT, 	THRESHOLD_LEFT};
capButton buttonRIGHT	= {RIGHT, 	THRESHOLD_RIGHT};
capButton buttonSTOP 	= {STOP, 	THRESHOLD_STOP};


extern void init(void);
void delay(int x){
    for(i=0; i<x; i++){
    }
}

void showDir(int dir){
	switch(dir){
		case UP:
			startBlinking(4, 5);
			break;

		case DOWN:
			startBlinking(1, 8);
			break;

		case LEFT:
			turnLED(2);
			turnLED(3);
			break;

		case RIGHT:
			turnLED(TOGGLE);
			turnLED(6);
			turnLED(7);
			break;

		case STOP:
			turnLED(MIDDLE);
			break;

		case OFF:
			turnLED(ALL_OFF);
			stopBlinking();
			break;
		}
}

void vBlinkLeds(void *p){
	dirPressed = OFF;

	while(1){
		showDir(dirPressed);
		vTaskSuspend(NULL);
		vTaskDelay(1);

	}
}

int waitForPress(int _threshold){
	int i = PULSE_LENGTH, j = PULSES_TO_SKIP, touch = 0;


	//skip the first couple samples to give the capacitive sensor time to settle
	while(j--){
			TA2CTL |= TACLR;
			vTaskDelay(1);
			capValue = TA2R;
	}

	while(i--){
		TA2CTL |= TACLR;
		vTaskDelay(1);
		capValue = TA2R;
		//if touch is detected
		if(capValue < _threshold){
			touch = 1;
			break;
		}
	}
	return touch;
}

void waitTillPressEnded(int _threshold){
	do{
		TA2CTL |= TACLR;
		vTaskDelay(1);
		capValue = TA2R;
	}while(capValue < _threshold);
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

//--------------------sensor readings------------------->>


void generalSensorTask(capButton* C){
	int _dir = C->dir;
	long _threshold = C->threshold;

	while(1){
		if (xSemaphoreTake(semMutex, 2000) == pdTRUE){
			initCap(_dir);
			//read Capacitance/proximity value
			if (waitForPress(_threshold)){	//if touch is detected
				dirPressed = _dir;
				vTaskResume(vBlinkLedsHandle);
				waitTillPressEnded(_threshold);
			}else{
			//if no touch is detected go check the next pad
			//YIELD();
			}

			dirPressed = OFF;
			vTaskResume(vBlinkLedsHandle);
			xSemaphoreGive(semMutex);
			vTaskDelay(1);
		}
	}
}

void vProxSensorUP(capButton* C){
	generalSensorTask(C);
}

void vProxSensorDOWN(capButton* C){
	generalSensorTask(C);
}

void vProxSensorLEFT(capButton* C){
	generalSensorTask(C);
}

void vProxSensorRIGHT(capButton* C){
	generalSensorTask(C);
}

void vProxSensorSTOP(capButton* C){
	generalSensorTask(C);
}

//--------------------sensor readings-------------------<<

/*
void tresholdChecker(void *pvParameters){
	capValue = 0;
	initCap(STOP);
	while(1){
	  	TA2CTL |= TACLR;
	   	vTaskDelay(1);
	   	capValue = TA2R;
	}
}*/


int main(void) {
    WDTCTL = WDTPW | WDTHOLD;  /* Stop watchdog timer */

    init();
    klok = CS_getMCLK();
    printf("Kloksnelheid is: %" PRIu32 "\n", klok);

    semMutex = xSemaphoreCreateMutex();

    //xTaskCreate(tresholdChecker, (signed char*)"tresholdChecker", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    xTaskCreate(vProxSensorUP, (signed char*)"vProxSensorUP", configMINIMAL_STACK_SIZE, &buttonUP, 1, &ProxSensorUP_Handle);
    xTaskCreate(vProxSensorDOWN, (signed char*)"vProxSensorDOWN", configMINIMAL_STACK_SIZE, &buttonDOWN, 1, &ProxSensorDOWN_Handle);
    xTaskCreate(vProxSensorLEFT, (signed char*)"vProxSensorLEFT", configMINIMAL_STACK_SIZE, &buttonLEFT, 1, &ProxSensorLEFT_Handle);
    xTaskCreate(vProxSensorRIGHT, (signed char*)"vProxSensorRIGHT", configMINIMAL_STACK_SIZE, &buttonRIGHT, 1, &ProxSensorRIGHT_Handle);
    xTaskCreate(vProxSensorSTOP, (signed char*)"vProxSensorSTOP", configMINIMAL_STACK_SIZE, &buttonSTOP, 1, &ProxSensorSTOP_Handle);

    xTaskCreate(vBlinkLeds, (signed char*)"vBlinkLeds", 1024, NULL, 2, &vBlinkLedsHandle);

    vTaskStartScheduler();

    while(1);

    return 0;
}
