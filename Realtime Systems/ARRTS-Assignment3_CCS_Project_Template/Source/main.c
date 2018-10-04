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


uint32_t klok = 0;
volatile uint32_t i, j, timerCounter = 0, blinkTimes = 0, times2blink, blinkSpeed = 1000;


extern void init(void);
void delay(){
    for(i=0; i<SEC; i++){
    }
}
void LEDClockWise(void);
void All8LEDS_Blink(int nTimes);
extern void turnLED(uint8_t led);
void vProxSensor(void*);
void leesSensor(void);

int main(void) {	//THIS IS THE MAIN COEDE
    WDTCTL = WDTPW | WDTHOLD;  /* Stop watchdog timer */

    init();
    klok = CS_getMCLK();
    printf("Kloksnelheid is: %" PRIu32 "\n", klok);

    CAPTIO0CTL = (CAPTIOPOSEL_4 + CAPTIOPISEL_6 + CAPTIOEN);

    while (1) {
    uint8_t pinWaarde = GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN6);
    //printf("%d\n", pinWaarde);
    if (pinWaarde > 0) {
        printf("hi");
    }
    //LEDClockWise();
    //All8LEDS_Blink(2);

    }



	return 0;
}

void T32_INT1_IRQHandler(void)
{
    MAP_Timer32_clearInterruptFlag (TIMER32_0_BASE); // Acknowledge Interrupt

     //reset timerCounter and enable leds for toggle
    if(timerCounter>blinkSpeed){
        timerCounter = 0;
        turnLED(RIGHT_HALF);
        blinkTimes++;
        if(blinkTimes > times2blink){   //double blink speed after 5 times blinking
            blinkSpeed = 500;
        }
    }
     //turns off leds (half of the time)
    else if(timerCounter>(blinkSpeed/2)){
        turnLED(ALL_OFF);
    }
     //toggle LEDs (turn all leds on)
    else {
        turnLED(TOGGLE);
    }

    timerCounter++;
    MAP_Timer32_setCount (TIMER32_0_BASE,TIMER_COUNTER);
}

void T32_INT2_IRQHandler(void)
{
    MAP_Timer32_clearInterruptFlag (TIMER32_1_BASE); // Acknowledge Interrupt
    MAP_GPIO_toggleOutputOnPin (GPIO_PORT_P6,  GPIO_PIN0);
    MAP_Timer32_setCount (TIMER32_1_BASE,24000000);
}


void LEDClockWise(void){
    for(j = 1; j<=8; j++){
        turnLED(j);
        delay();
        //printf("Turing led %d on\n", j);
    }
    delay();
}

void All8LEDS_Blink(int nTimes){
    blinkTimes = 0;
    times2blink = nTimes;
    MAP_Timer32_startTimer (TIMER32_0_BASE, 1); // Start the timer 1
    MAP_Timer32_startTimer (TIMER32_1_BASE, 1); // Start the timer 2
}



void vProxSensor(void* pvParameters) {
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P4,  GPIO_PIN6);
}

void leesSensor() {

}
