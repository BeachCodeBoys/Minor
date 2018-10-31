#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>
#include <inttypes.h>

/*
 * ARTS-Lab-2016, HHs Electrotechniek, W.Muhammad
 * Assignment 1- Project Template
     *
     * Initial Steps for hardware configuration required for Assignment 1:
     * 1) Setup source clocks, use the clock frequency of 48 MHz. Read through Clock System Operation section
     *    of the MSP432 Datasheet. Use driver lib API document to find the correct functions to use.
     * 	  In this assignment you only need to set MCK, see MSP432 CSS examples.
     * 2) Configure General purpose I/O (GPIO) pin P1.0 (Port1 pin0) as output , see example projects
     *    and Driver Lib API document to find out how you can configure a specific pin as digital output
     * 3) Add the appropiate delay mentioned on the assignment document, you can use busy waiting (loop).
     * 4) Toggle the output PIN (P1.0) connected to LED
     * 5) Print the current state of the LED on the CCS output console. Always use fflush(stdout); after
     *    printf() call.
     *kjkjkj j
     *  Good Luck! homojo
     */

#define SEC 			1100000
#define ALL_OFF			0
#define RIGHT_HALF		9
#define TOGGLE			10
#define TIMER_COUNTER	96000	//500Hz


uint32_t klok = 0;
volatile uint32_t i, j, timerCounter = 0, blinkTimes = 0, times2blink, blinkSpeed = 1000;


void initClock(void);
void LEDClockWise(void);
void All8LEDS_Blink(int nTimes);
void delay(){
	for(i=0; i<SEC; i++){
	}
}
void init();
void turnLED(uint8_t led);


void T32_INT1_IRQHandler(void)	//runs 500 times a sec
{
	MAP_Timer32_clearInterruptFlag (TIMER32_0_BASE); // Acknowledge Interrupt

 	 //reset timerCounter and enable leds for toggle
	if(timerCounter>blinkSpeed){
		timerCounter = 0;
		turnLED(RIGHT_HALF);
		blinkTimes++;
		if(blinkTimes > times2blink){	//double blink speed after 5 times blinking
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



int main(void) {
	init();
	LEDClockWise();
	All8LEDS_Blink(2);

	while(1){

	}
}





void initClock(void){
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
 	//MAP_GPIO_setAsOutputPin (GPIO_PORT_P1, GPIO_PIN0);
	MAP_Timer32_initModule (TIMER32_0_BASE, TIMER32_PRESCALER_1,
	TIMER32_32BIT,TIMER32_FREE_RUN_MODE);	//timer 1
	MAP_Timer32_initModule (TIMER32_1_BASE, TIMER32_PRESCALER_1,
	TIMER32_32BIT,TIMER32_FREE_RUN_MODE);	//timer 2

	MAP_Timer32_setCount (TIMER32_0_BASE,TIMER_COUNTER);	//timer 1
	MAP_Timer32_setCount (TIMER32_1_BASE,24000000);			//timer 2
	MAP_Interrupt_enableInterrupt (INT_T32_INT1); // Enable timer 32 in NVIC timer 1
	MAP_Interrupt_enableInterrupt (INT_T32_INT2); // Enable timer 32 in NVIC timer 2
	MAP_Interrupt_setPriority (INT_T32_INT1, 0x40); // b0100 0000 , sets a priority of 2 timer 1
	MAP_Interrupt_setPriority (INT_T32_INT2, 0x40); // b0100 0000 , sets a priority of 2 timer 2
	MAP_Timer32_enableInterrupt (TIMER32_0_BASE); // Enable peripheral (timer 32 module 0) interrupt timer 1
	MAP_Timer32_enableInterrupt (TIMER32_1_BASE); // Enable peripheral (timer 32 module 0) interrupt timer 2
	MAP_Timer32_registerInterrupt ( TIMER32_0_INTERRUPT, T32_INT1_IRQHandler ); //Register ISR timer 1
	MAP_Timer32_registerInterrupt ( TIMER32_1_INTERRUPT, T32_INT2_IRQHandler ); //Register ISR timer 2
	MAP_Interrupt_enableMaster (); // Enable global interrupt
}

void init(){
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

	//pull all LEDs low
	turnLED(ALL_OFF);
	GPIO_setOutputLowOnPin(GPIO_PORT_P6,  GPIO_PIN0);
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

void All8LEDS_Blink(int nTimes){
	blinkTimes = 0;
	times2blink = nTimes;
	MAP_Timer32_startTimer (TIMER32_0_BASE, 1); // Start the timer 1
}
