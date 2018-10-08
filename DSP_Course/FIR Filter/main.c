/******************************************************************************
 File            : main.c
 Compiler        : TI C5500, Version 4.4.1 (CCS 6.1.2)
 Revision        : Revision: 1.2
 Date            : 2018 / 07
 Author          : Fidelis Theinert

 Copyright (C) 2016 - 2018 Fidelis Theinert

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 * simple demonstration of the USBSTKC5505:
 * reading a stereo sample from the microphone input
 * and sending the sample to the headphone output
 *
 * use as starting point for the DSP workshop of
 * the Minor Embedded System at the HHS / Delft
 *****************************************************************************/

#include "hhs_setup_0.h"

// define settings to initialize codec
#define HHS_PLL_FREQ 100
#define HHS_SAMPLES_PER_SECOND 48000
#define HHS_GAIN_DB 48

#define SECS_TO_RUN 60


// **************************************************************************************
void main (void)
// **************************************************************************************
{
	// declare input and output variables
	// all samples are signed 16 variables
	S16 inLeft, inRight, outLeft, outRight;

	unsigned long loop = 0;

	// setup USB5505 for Headphone and Microphone use
	HHS_Setup (HHS_PLL_FREQ, HHS_SAMPLES_PER_SECOND, HHS_GAIN_DB);
   
    printf ("\nLoopback: Microphone IN -> Headphone OUT\n");

    while (loop < (HHS_SAMPLES_PER_SECOND * SECS_TO_RUN))
 	{
    	// read one stereo sample (left and right) from input codec (ADC)
    	HHS_InStereo (&inLeft, &inRight);
   
    	// place your own code for processing here
    	outLeft  = inLeft;
    	outRight = inRight;
    
    	// write one stereo sample (left and right) to output codec (DAC)
    	HHS_OutStereo (outLeft, outRight);

    	if (loop & 0x4000)  {
    		HHS_LEDON ();
    	} else {
    		HHS_LEDOFF ();
    	}

    	loop++;
 	}

    printf( "\nTerminating Application!\n" );
 	HHS_Stop ();
}

// End of file: main.c
