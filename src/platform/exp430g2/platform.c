/* Copyright (c) 2012, Peter A. Bigot <bigotp@acm.org>
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * * Neither the name of the software nor the names of its contributors may be
 *   used to endorse or promote products derived from this software without
 *   specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <bsp430/platform/exp430g2.h>
#include <bsp430/periph/bc2.h>
#include <bsp430/utility/uptime.h>
#include <bsp430/utility/led.h>
#include "serial.h"
#include "task.h"

const xBSP430led pxBSP430leds[] = {
	{ .pucPxOUT = &P1OUT, .ucBIT = BIT0 }, /* Red */
	{ .pucPxOUT = &P1OUT, .ucBIT = BIT6 }, /* Green */
};
const unsigned char ucBSP430leds = sizeof(pxBSP430leds) / sizeof(*pxBSP430leds);


int
iBSP430platformConfigurePeripheralPins_ni (xBSP430periphHandle device, int enablep)
{
	unsigned int bits;

	if (BSP430_PERIPH_XT1 == device) {
		bits = BIT6 | BIT7;
		if (enablep) {
			P2SEL |= bits;
		} else {
			P2SEL &= ~bits;
		}
		return 0;
	}
#if configBSP430_PERIPH_EXPOSED_CLOCKS - 0
	else if (BSP430_PERIPH_EXPOSED_CLOCKS == device) {
		bits = BIT0 | BIT4;
		if (enablep) {
			P1SEL |= bits;
		} else {
			P1SEL &= ~bits;
		}
		P1DIR |= bits;
		return 0;
	}
#endif /* configBSP430_PERIPH_EXPOSED_CLOCKS */

	return -1;
}

void vBSP430platformSetup_ni ()
{
	unsigned char ucDCOCTL = DCOCTL;
	unsigned char ucBCSCTL1 = BCSCTL1;
	unsigned char ucBCSCTL2 = BCSCTL2;
	unsigned char ucBCSCTL3 = BCSCTL3;
	
	/* Hold off watchdog */
	WDTCTL = WDTPW + WDTHOLD;

	ucBCSCTL3 = XCAP_1;
#if 16000000 == BSP430_CLOCK_NOMINAL_MCLK_HZ
	/* 16 MHz MCLK, 4 MHz SMCLK */
	ucBCSCTL1 = CALBC1_16MHZ;
	ucDCOCTL = CALDCO_16MHZ;
#elif 12000000 == BSP430_CLOCK_NOMINAL_MCLK_HZ
	/* 12 MHz MCLK, 12 MHz SMCLK */
	ucBCSCTL1 = CALBC1_12MHZ;
	ucDCOCTL = CALDCO_12MHZ;
#elif 8000000 == BSP430_CLOCK_NOMINAL_MCLK_HZ
	/* 8 MHz MCLK, 4 MHz SMCLK */
	ucBCSCTL1 = CALBC1_8MHZ;
	ucDCOCTL = CALDCO_8MHZ;
#elif 1000000 == BSP430_CLOCK_NOMINAL_MCLK_HZ
	/* 1 MHz MCLK, 1 MHz SMCLK */
	ucBCSCTL1 = CALBC1_1MHZ;
	ucDCOCTL = CALDCO_1MHZ;
#endif /* BSP430_CLOCK_NOMINAL_MCLK_HZ */

	ucBCSCTL2 = DIVS0 * BSP430_CLOCK_SMCLK_DIVIDING_SHIFT;

	/* ucBSP430bc2Configure_ni does the crystal stabilization */
	(void)ucBSP430bc2Configure_ni(ucDCOCTL, ucBCSCTL1, ucBCSCTL2, ucBCSCTL3);

#if configBSP430_UPTIME - 0
	vBSP430uptimeStart_ni();
#endif
}

void
vBSP430platformSpinForJumper_ni (void)
{
    /* P2.6 I/O input with pullup */
    P2DIR &= ~BIT6;
    P2SEL &= ~BIT6;
    P2REN |= BIT6;
    P2OUT |= BIT6;

    /* Flash LEDs alternately while waiting */
    P1OUT |= BIT0;
    while (! (P2IN & BIT6)) {
      __delay_cycles(100000);
      P1OUT ^= BIT0 | BIT6;
    }

    /* Restore P2.6 and LEDs */
    P1OUT &= ~(BIT0 | BIT6);
    P2DIR |= BIT6;
    P2REN &= ~BIT6;
}