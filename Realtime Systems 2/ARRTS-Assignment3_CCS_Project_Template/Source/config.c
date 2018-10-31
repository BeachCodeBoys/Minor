#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

#define TIMER_COUNTER   96000   //500Hz
#define ALL_OFF         0
#define RIGHT_HALF      9
#define TOGGLE          10

volatile uint32_t j, blinkTimes = 0, times2blink = 0, timerCounter= 0;

void initClock(void);
void initTimers(void);
void turnLED(uint8_t);
extern void T32_INT1_IRQHandler(void);

void T32_INT1_IRQHandler(void)	//runs at 500Hz
{
	MAP_Timer32_clearInterruptFlag (TIMER32_0_BASE); // Acknowledge Interrupt
	if(timerCounter<= 500){
		turnLED(TOGGLE);
	}
	else if(timerCounter >=1000){
		turnLED(RIGHT_HALF);
		timerCounter = 0;
		times2blink--;
	}else{
		turnLED(ALL_OFF);
	}
	if (times2blink <= 0){
		stopBlinking();
	}

	timerCounter++;
	MAP_Timer32_setCount (TIMER32_0_BASE,TIMER_COUNTER);
}

void init(void) {
    initClock();
    initTimers();

    //set LED as output
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P4,  GPIO_PIN3);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1,  GPIO_PIN5);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1,  GPIO_PIN7);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1,  GPIO_PIN6);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P4,  GPIO_PIN1);

    //Middle booster pack LED
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P6,  GPIO_PIN0);

    //Make capacitor an input
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P4,  GPIO_PIN6);

    //pull all LEDs low
    turnLED(ALL_OFF);
    GPIO_setOutputLowOnPin(GPIO_PORT_P6,  GPIO_PIN0);
}

void initClock(void) {
        /* Halting WDT and disabling master interrupts */
    MAP_WDT_A_holdTimer();
    MAP_Interrupt_disableMaster();

        /* Set the core voltage level to VCORE1 */
    MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);

        /* Set 2 flash wait states for Flash bank 0 and 1*/
    MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
    MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);

        /* Initializes Clock System */
    MAP_CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
    MAP_CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1 );
    MAP_CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
}

void initTimers(){
	WDTCTL = WDTPW | WDTHOLD; /* Stop watchdog timer */
 	MAP_GPIO_setAsOutputPin (GPIO_PORT_P1, GPIO_PIN0);
	MAP_Timer32_initModule (TIMER32_0_BASE, TIMER32_PRESCALER_1,
	TIMER32_32BIT,TIMER32_FREE_RUN_MODE);	//timer 1

	MAP_Timer32_setCount (TIMER32_0_BASE,TIMER_COUNTER);	//timer 1
	MAP_Interrupt_enableInterrupt (INT_T32_INT1); // Enable timer 32 in NVIC timer 1
	MAP_Interrupt_setPriority (INT_T32_INT1, 0x40); // b0100 0000 , sets a priority of 2 timer 1
	MAP_Timer32_enableInterrupt (TIMER32_0_BASE); // Enable peripheral (timer 32 module 0) interrupt timer 1
	MAP_Timer32_registerInterrupt ( TIMER32_0_INTERRUPT, T32_INT1_IRQHandler ); //Register ISR timer 1
	MAP_Interrupt_enableMaster (); // Enable global interrupt
	//MAP_Timer32_startTimer (TIMER32_0_BASE, 1); // Start the timer
}


void turnLED(uint8_t led){
	switch (led){
		case 0:	//turn off leds
			GPIO_setOutputLowOnPin(GPIO_PORT_P4,  GPIO_PIN3);
			GPIO_setOutputLowOnPin(GPIO_PORT_P1,  GPIO_PIN5);
			GPIO_setOutputLowOnPin(GPIO_PORT_P1,  GPIO_PIN6);
			GPIO_setOutputLowOnPin(GPIO_PORT_P1,  GPIO_PIN7);
			GPIO_setOutputLowOnPin(GPIO_PORT_P4,  GPIO_PIN1);
			break;

		case 1:	//turn led 1 on
			GPIO_setOutputLowOnPin(GPIO_PORT_P4,  GPIO_PIN1);
			GPIO_setOutputHighOnPin(GPIO_PORT_P1,  GPIO_PIN6);
			break;
		case 2: //turn led 2 on
			GPIO_setOutputLowOnPin(GPIO_PORT_P4,  GPIO_PIN1);
			GPIO_setOutputHighOnPin(GPIO_PORT_P1,  GPIO_PIN7);
			break;
		case 3: //turn led 3 on
			GPIO_setOutputLowOnPin(GPIO_PORT_P4,  GPIO_PIN1);
			GPIO_setOutputHighOnPin(GPIO_PORT_P1,  GPIO_PIN5);
			break;
		case 4: //turn led 4 on
			GPIO_setOutputLowOnPin(GPIO_PORT_P4,  GPIO_PIN1);
			GPIO_setOutputHighOnPin(GPIO_PORT_P4,  GPIO_PIN3);
			break;

		case 5: //turn led 5 on
			GPIO_setOutputHighOnPin(GPIO_PORT_P4,  GPIO_PIN1);
			GPIO_setOutputLowOnPin(GPIO_PORT_P4,  GPIO_PIN3);
			break;
		case 6: //turn led 6 on
			GPIO_setOutputHighOnPin(GPIO_PORT_P4,  GPIO_PIN1);
			GPIO_setOutputLowOnPin(GPIO_PORT_P1,  GPIO_PIN5);
			break;
		case 7: //turn led 7 on
			GPIO_setOutputHighOnPin(GPIO_PORT_P4,  GPIO_PIN1);
			GPIO_setOutputLowOnPin(GPIO_PORT_P1,  GPIO_PIN7);
			break;
		case 8: //turn led 8 on
			GPIO_setOutputHighOnPin(GPIO_PORT_P4,  GPIO_PIN1);
			GPIO_setOutputLowOnPin(GPIO_PORT_P1,  GPIO_PIN6);
			break;

		case 9: //turn right half on
			GPIO_setOutputLowOnPin(GPIO_PORT_P4,  GPIO_PIN3);
			GPIO_setOutputLowOnPin(GPIO_PORT_P1,  GPIO_PIN5);
			GPIO_setOutputLowOnPin(GPIO_PORT_P1,  GPIO_PIN6);
			GPIO_setOutputLowOnPin(GPIO_PORT_P1,  GPIO_PIN7);
			GPIO_setOutputHighOnPin(GPIO_PORT_P4,  GPIO_PIN1);
			break;

		case 10: //togle leds
			MAP_GPIO_toggleOutputOnPin (GPIO_PORT_P4,  GPIO_PIN3);
			MAP_GPIO_toggleOutputOnPin (GPIO_PORT_P1,  GPIO_PIN5);
			MAP_GPIO_toggleOutputOnPin (GPIO_PORT_P1,  GPIO_PIN7);
			MAP_GPIO_toggleOutputOnPin (GPIO_PORT_P1,  GPIO_PIN6);
			MAP_GPIO_toggleOutputOnPin (GPIO_PORT_P4,  GPIO_PIN1);
	}
}

void LEDClockWise(void){
	for(j = 1; j<=8; j++){
		turnLED(j);
		delay();
		//printf("Turing led %d on\n", j);
	}
	delay();
}

void startBlinking(int nTimes){
	//first turn right half on so you can toggle
	turnLED(RIGHT_HALF);

	blinkTimes = 0;
	times2blink = nTimes;
	MAP_Timer32_startTimer (TIMER32_0_BASE, 1); // Start the timer 1
}

void stopBlinking(){
	Timer32_haltTimer(TIMER32_0_BASE);	// Stop the timer 1
	turnLED(ALL_OFF);
}
