 #include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>
#include <inttypes.h>
#include <semphr.h>
/*
 * ARTS-Lab-2016, HHs Electrotechniek, W.Muhammad
 * Assignment 3- Project Template

     */
//#define INCLUDE_vTaskSuspend  1
//#define INCLUDE_vTaskDelay    1

#define SEC             1100000
#define ALL_OFF         0
#define RIGHT_HALF      9
#define TOGGLE          10
#define TIMER_COUNTER   96000   //500Hz
#define TRUE			1
#define FALSE			0

#define THRESHOLD		1700	//45000

uint32_t klok = 0;
volatile uint32_t i, j;
volatile long capValue;

TaskHandle_t toggleLEDHandle = NULL;
TaskHandle_t capTouchButtonHandle = NULL;


extern void init(void);
void delay(){
    for(j=0; j<SEC; j++){
    }
}



void vToggleLED(void *p){

	while(1){

		//toggle LED
		MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P6,  GPIO_PIN0);
		while(capValue < THRESHOLD);

		vTaskSuspend(NULL);
	}
}

void vCapTouchButton(void *p){

	while(1){
		//read Capacitance/proximity value;
		TA2CTL |= TACLR;

		vTaskDelay(1);
		capValue = TA2R;

		//if capacitance is detected--> start toggleLED task
		if(capValue < THRESHOLD){
			vTaskResume(toggleLEDHandle);
			vTaskDelay(100);	//debounce
		}
	}
}


int main(void) {
    WDTCTL = WDTPW | WDTHOLD;  /* Stop watchdog timer */

    init();
    klok = CS_getMCLK();
    printf("Kloksnelheid is: %" PRIu32 "\n", klok);

    //init capacitor
    CAPTIO0CTL = (CAPTIOPOSEL_5 + CAPTIOPISEL_0 + CAPTIOEN);
    TA2CTL |= ( MC__CONTINUOUS | TACLR | TASSEL_3);

    xTaskCreate(vCapTouchButton, (signed char*)"vCapTouchButton", 1024, NULL, 2, &capTouchButtonHandle);
    xTaskCreate(vToggleLED, (signed char*)"vToggleLED", 1024, NULL, 2, &toggleLEDHandle);
    vTaskSuspend(toggleLEDHandle);

    vTaskStartScheduler();


    return 0;
}
