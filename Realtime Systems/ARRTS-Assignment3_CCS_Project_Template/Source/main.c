#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>


/*
 * ARTS-Lab-2016, HHs Electrotechniek, W.Muhammad
 * Assignment 3- Project Template

     */
void init(void);
void initClock(void);
void initTimers(void);
void delay(){
    for(i=0; i<SEC; i++){
    }
}
void LEDClockWise(void);
void All8LEDS_Blink(int nTimes);
void vProxSensor(void*);

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;  /* Stop watchdog timer */

    init();

    while(1) {

    }


	return 0;
}

void init(void) {
    initClock();
    initTImers();

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

void initTimers(void) {
    WDTCTL = WDTPW | WDTHOLD; /* Stop watchdog timer */
    MAP_GPIO_setAsOutputPin (GPIO_PORT_P1, GPIO_PIN0);
    MAP_Timer32_initModule (TIMER32_0_BASE, TIMER32_PRESCALER_1,
    TIMER32_32BIT,TIMER32_FREE_RUN_MODE);   //timer 1
    MAP_Timer32_initModule (TIMER32_1_BASE, TIMER32_PRESCALER_1,
    TIMER32_32BIT,TIMER32_FREE_RUN_MODE);   //timer 2

    MAP_Timer32_setCount (TIMER32_0_BASE,TIMER_COUNTER);    //timer 1
    MAP_Timer32_setCount (TIMER32_1_BASE,24000000); //timer 2
    MAP_Interrupt_enableInterrupt (INT_T32_INT1); // Enable timer 32 in NVIC timer 1
    MAP_Interrupt_enableInterrupt (INT_T32_INT2); // Enable timer 32 in NVIC timer 2
    MAP_Interrupt_setPriority (INT_T32_INT1, 0x40); // b0100 0000 , sets a priority of 2 timer 1
    MAP_Interrupt_setPriority (INT_T32_INT2, 0x40); // b0100 0000 , sets a priority of 2 timer 2
    MAP_Timer32_enableInterrupt (TIMER32_0_BASE); // Enable peripheral (timer 32 module 0) interrupt timer 1
    MAP_Timer32_enableInterrupt (TIMER32_1_BASE); // Enable peripheral (timer 32 module 0) interrupt timer 2
    MAP_Timer32_registerInterrupt ( TIMER32_0_INTERRUPT, T32_INT1_IRQHandler ); //Register ISR timer 1
    MAP_Timer32_registerInterrupt ( TIMER32_1_INTERRUPT, T32_INT2_IRQHandler ); //Register ISR timer 2
    MAP_Interrupt_enableMaster (); // Enable global interrupt
    //MAP_Timer32_startTimer (TIMER32_0_BASE, 1); // Start the timer
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

}
