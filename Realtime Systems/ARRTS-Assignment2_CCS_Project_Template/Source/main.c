#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>


/*
 * ARTS-Lab-2016, HHs Electrotechniek, W.Muhammad
 * Assignment 2- Project Template
     *
     * Initial Steps for hardware configuration required for Assignment 2:
     * 1) Setup source clocks, use the clock frequency of 48 MHz. Read through Clock System Operation section
     *    of the MSP432 Datasheet. Use driver lib API document to find the correct functions to use.
     * 2) Read and understand the CBP schematic and pin connections. The CBP 9 LEDS and their corresponding
     *    pin connections with MSP432 (Document is available on Blackboard under Lab2 folder)
     * 3) Write the function LEDCockWise() to blink the LEDS in clockwise fashion with an approximate delay
     *    of 500 msec.
     * 3) Configure any MSP432 timer to generate an interrupt at exactly 500 msec.
     * 4) In the interrupt handling routine (ISR) toggle the middle LED (LED9).
     * 5) Complete the assignment with writing the function All8LEDS_blink(int nTime) according to the
     *    requirements menioned in the assignment document.
     *
     *  Good Luck!
     */

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;  /* Stop watchdog timer */



	return 0;
}

