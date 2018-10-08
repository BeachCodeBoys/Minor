/*
 *  hhs_setup_0.c
 *
 *  Created on: 2018 / 07
 *      Author: Fidelis Theinert
 *      Base on code from Texas Instruments / Richard Sikora
 */

#ifndef HHS_SETUP_0_H_
#define HHS_SETUP_0_H_

#include "stdio.h"
#include "usbstk5505.h"
#include "aic3204.h"
#include "PLL.h"

#define HHS_OK      0
#define HHS_ERROR  -1

#define HHS_LED_ON  1
#define HHS_LED_OFF 0

#define S16 short

#ifndef HHS_SAMPLES_PER_SECOND
#define HHS_SAMPLES_PER_SECOND 48000
#endif  // HHS_SAMPLES_PER_SECOND

#ifndef HHS_GAIN_DB
#define HHS_GAIN_DB 48
#endif  // HHS_GAIN_DB

#ifndef HHS_PLL_FREQ
#define HHS_PLL_FREQ 100
#endif  // HHS_PLL_FREQ

#define HHS_LEDOFF() {asm(" bclr XF");}
#define HHS_LEDON()  {asm(" bset XF");}

int HHS_Setup (unsigned int, unsigned long, unsigned int);
void HHS_Stop (void);
void HHS_Led (int);
int HHS_InStereo (S16 *, S16 *);
int HHS_OutStereo (S16, S16);


#endif /* HHS_SETUP_0_H_ */
