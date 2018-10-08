/*
 *  hhs_setup_0.c
 *
 *  Created on: 2018 / 07
 *      Author: Fidelis Theinert
 *      Base on code from Texas Instruments / Richard Sikora
 *      see (C) below
 */

/*
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/


#include "hhs_setup_0.h"

// **************************************************************************************
int HHS_Setup (unsigned int pll_freq, unsigned long sample_rate, unsigned int gain_db)
// **************************************************************************************
{
    // Initialize BSL
    USBSTK5505_init ();

	// Initialize PLL
	pll_frequency_setup (pll_freq);

    // Initialize hardware interface and I2C for codec
    aic3204_hardware_init ();

    // Initialize AIC3204 codec
	aic3204_init ();

	// Setup sampling frequency and gain for input
    set_sampling_frequency_and_gain (sample_rate, gain_db);

    if (gain_db >= 30) {
		// switch microphone bias voltage on
		AIC3204_rset ( 0, 1);     		// Point to page 1
		AIC3204_rset (51, 0x40);     	// switch MIC-Bias on
		AIC3204_rset ( 0, 0);      	// Point to page 0
    }

	// switch Led off
    HHS_LEDOFF ();

	return HHS_OK;
}

// **************************************************************************************
void HHS_Stop (void)
// **************************************************************************************
{
	// switch Led off
    HHS_LEDOFF ();

    // Reset Codec and I2S
	aic3204_disable();

	// hold forever
	while (1);
}


// **************************************************************************************
int HHS_InStereo (S16 *left, S16 *right)
// **************************************************************************************
{
    aic3204_codec_read(left, right);  // Configured for one interrupt per two channels

    return HHS_OK;
}


// **************************************************************************************
void HHS_Led (int on)
// **************************************************************************************
{
	if (on == HHS_LED_ON) {
		 asm(" bset XF");
	} else {
		 asm(" bclr XF");
	}
}


// **************************************************************************************
int HHS_OutStereo (S16 left, S16 right)
// **************************************************************************************
{
    aic3204_codec_write(left, right);

    return HHS_OK;
}




