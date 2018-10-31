#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>


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

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;  /* Stop watchdog timer */



	return 0;
}

