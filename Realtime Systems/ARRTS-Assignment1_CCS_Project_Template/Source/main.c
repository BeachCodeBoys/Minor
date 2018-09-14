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
     *
     *  Good Luck!
     */

void FunBlinkLed(void);
void FunDelay(void);
void FunPrint(void);
void initClock(void);

uint32_t klok = 0;
volatile uint32_t ii;

int main(void) {
    //WDTCTL = WDTPW | WDTHOLD;  /* Stop watchdog timer */

    //initClock();

    klok = CS_getMCLK();

    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1,  GPIO_PIN0);

    printf("%" PRIu32 "\n",klok);

    FunBlinkLed();


    while (1)
    {

    	FunBlinkLed();
    	//FunPrint();
    	FunDelay();





    }//	*/

// maak af dan kklijer


	return 0;
}

void initClock(void)
{
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

void FunBlinkLed(void)
{
	MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1,  GPIO_PIN0);

}

void FunDelay(void)
{
	for(ii=0;ii<5000;ii++)
	{
	}
}

void FunPrint(void)
{

}
