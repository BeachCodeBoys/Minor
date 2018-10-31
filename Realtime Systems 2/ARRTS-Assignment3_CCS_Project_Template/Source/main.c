 #include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>
#include <inttypes.h>

/*
 * ARTS-Lab-2016, HHs Electrotechniek, W.Muhammad
 * Assignment 3- Project Template

     */

#define SEC             1100000
#define ALL_OFF         0
#define RIGHT_HALF      9
#define TOGGLE          10
#define TIMER_COUNTER   96000   //500Hz
#define TRUE			1
#define FALSE			0

#define THRESHOLD		19000
uint32_t klok = 0;
volatile uint32_t i;
long capValue;

TaskHandle_t ProxSensorHandle = NULL;
TaskHandle_t All8LEDS_BlinkHandle = NULL;

extern void init(void);
void delay(){
    for(i=0; i<SEC; i++){
    }
}


void All8LEDS_Blink(int i){

	while(1){
		startBlinking(i);
		vTaskSuspend(NULL);
	}
}

void vProxSensor(void *p){

	while(1){
		//read Capacitance/proximity value;
		TA2CTL |= TACLR;
		vTaskDelay(100);
		capValue = TA2R;

		if(capValue < THRESHOLD){
			vTaskResume(All8LEDS_BlinkHandle);
		}
	}
}

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;  /* Stop watchdog timer */

    init();
    klok = CS_getMCLK();
    printf("Kloksnelheid is: %" PRIu32 "\n", klok);

    //init capacitor
    CAPTIO0CTL = (CAPTIOPOSEL_4 + CAPTIOPISEL_6 + CAPTIOEN);
    TA2CTL |= ( MC__CONTINUOUS | TACLR | TASSEL_3);


    xTaskCreate(vProxSensor, (signed char*)"vProxSensor", 1024, NULL, 1, &ProxSensorHandle);
    xTaskCreate(All8LEDS_Blink, (signed char*)"All8LEDS_Blink", 1024, 2, 1, &All8LEDS_BlinkHandle);
    vTaskSuspend(All8LEDS_BlinkHandle);

    vTaskStartScheduler();


    return 0;
}
