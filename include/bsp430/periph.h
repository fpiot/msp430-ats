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

/** @file
 *
 * @brief Generic peripheral support for MSP430 MCUs.
 *
 * This file, included by peripheral-specific include files, supports
 * handles to peripherals which in turn are used in application code.
 * Use of a given peripheral must be indicated by defining the
 * corresponding @c configBSP430_PERIPH_xx in the application @c
 * FreeRTOSConfig.h file.
 *
 * Structures are defined in the peripheral-specific header for each
 * class of peripheral that may have multiple instances with the same
 * register set, to simplify access by converting the periphal address
 * to a pointer to such a structure.  These structures intentionally
 * uses the GCC/ISO C11 extensions for unnamed struct/union fields.
 * Access to the peripheral area through such pointers must be done
 * with care, as some structure fields are not valid for some variants
 * of the peripheral.
 *
 * @author Peter A. Bigot <bigotp@acm.org>
 * @date 2012
 * @homepage http://github.com/pabigot/freertos-mspgcc
 * @copyright <a href="http://www.opensource.org/licenses/BSD-3-Clause">BSD-3-Clause</a>
 */

#ifndef BSP430_PERIPH_H
#define BSP430_PERIPH_H

#include <bsp430/common.h>
#include <msp430.h>

/** An integral type used to uniquely identify a raw MCU peripheral.
 *
 * For MCU families where peripheral base addresses are provided in
 * the header files, those base addresses are used as the handle.  In
 * other cases arbitrary values may be used, so in general objects
 * with this type should be referenced only equality testing against
 * the constant handle identifier provided in the peripheral
 * header.
 *
 * The value zero is reserved and available as #BSP430_PERIPH_NONE to
 * indicate no peripheral.
 *
 * Odd values are reserved for non-standard "peripherals" for which
 * some identifier is necessary to allow use in functions like
 * #iBSP430platformConfigurePeripheralPinsFromISR, such as
 * #BSP430_PERIPH_XT1.
 *
 * Negative values indicate an error. */
typedef int xBSP430periphHandle;

/** HPL handle specifying that no peripheral has been identified. */
#define BSP430_PERIPH_NONE ((xBSP430periphHandle)0)

/** HPL handle identifying the XT1 crystal functionality.
 *
 * This is used by platform-independent clock peripherals to request
 * that the pins related to XIN and XOUT be configured to their
 * peripheral function. */
#define BSP430_PERIPH_XT1 ((xBSP430periphHandle)1)

/** HPL handle identifying the ability to expose clock signals.
 *
 * This is used by application code as a debug facility, invoking
 * #iBSP430platformConfigurePeripheralPinsFromISR to expose MCLK, SMCLK, and
 * ACLK on pins where they may be monitored.  Its availability is
 * conditional on platform support and
 * #configBSP430_PERIPH_EXPOSED_CLOCKS. */
#define BSP430_PERIPH_EXPOSED_CLOCKS ((xBSP430periphHandle)3)

/** @def configBSP430_PERIPH_EXPOSED_CLOCKS
 *
 * Define to a true value in @c FreeRTOSConfig.h to enable use of
 * #BSP430_PERIPH_EXPOSED_CLOCKS in
 * #iBSP430platformConfigurePeripheralPinsFromISR. */
#ifndef configBSP430_PERIPH_EXPOSED_CLOCKS
#define configBSP430_PERIPH_EXPOSED_CLOCKS 0
#endif /* configBSP430_PERIPH_EXPOSED_CLOCKS */

#endif /* BSP430_PERIPH_H */