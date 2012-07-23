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
 * @brief Genericized digital I/O port (PORTX/PORTX_R) for MSP430 MCUs
 *
 * A hardware presentation layer is defined that provides a structure
 * definition associated with a port-specific address, to allow
 * manipulation of standard port registers like @c PxDIR and @c PxSEL
 * through a single pointer.  This would be useful when an external
 * component such as a DS18B20 may be placed on one of several ports
 * depending on platform.  Presentation layer structures are defined
 * for each 8-bit port, and for the 16-bit port interfaces on MCUs
 * that support them.
 *
 * A hardware abstraction layer is defined that allows registering
 * callbacks to be invoked when port interrupts occur.  This is
 * necessary when a library provides support for an external component
 * that signals events through an interrupt, but is not permitted to
 * define the interrupt handler for the entire port.  The abstraction
 * layer is supported only for the 8-bit port interface.
 *
 * @author Peter A. Bigot <bigotp@acm.org>
 * @date 2012
 * @homepage http://github.com/pabigot/freertos-mspgcc
 * @copyright <a href="http://www.opensource.org/licenses/BSD-3-Clause">BSD-3-Clause</a>
 */

/* !BSP430! periph=port */
/* !BSP430! instance=PORT1,PORT2,PORT3,PORT4,PORT5,PORT6,PORT7,PORT8,PORT9,PORT10,PORT11 */

#ifndef BSP430_PERIPH_PORT_H
#define BSP430_PERIPH_PORT_H

#include <bsp430/periph.h>
#if ! (defined(__MSP430_HAS_PORT1__) || defined(__MSP430_HAS_PORT1_R__))
#warning Peripheral not supported by configured MCU
#endif /* __MSP430_HAS_PORT1__ */

/* Analysis of port capabilities:
 *
 * 1xx: P1/P2 are uniform contiguous with interrupt capability.  P3-P6
 * are uniform contiguous without interrupt capability.  There is no
 * REN capability.
 *
 * 2xx: P1/P2 are uniform contiguous inclusive of REN but exclusive of
 * SEL2, which is contiguous at a distinct base address, and have
 * interrupt capability.  P3-P6 are uniform 8-bit and P7-P8 are
 * uniform 16-bit contiguous, exclusive of REN and SEL2.  PA=(P7,P8)
 * in the headers, but is not named as such in the user's guide.
 * 
 * 3xx: P1/P2 are uniform contiguous with interrupt capability.  P3-P4
 * are uniform contiguous without interrupt capability.  There is no
 * REN capability.
 * 
 * 4xx: P1/P2 are uniform contiguous including REN capability, and
 * have interrupt capability.  P3-P6 are uniform 8-bit and P7-P10 are
 * uniform 16-bit contiguous; these are exclusive of REN, which is
 * contiguous at a distinct base address.  PA=(P7,P8), PB=(P9,P10).
 *
 * 5xx: All ports uniform 16-bit contiguous.  PA=(P1,P2), PB=(P3,P4),
 * and so forth.  All registers have space reserved for interrupt
 * support.
 *
 * In the above, "8-bit" means that the register fields are
 * immediately adjacent with byte addresses.  "16-bit" means that
 * register pairs are interleaved within function; e.g. P1IN would be
 * at 0x00 while P2IN is at 0x01 and P1OUT at 0x02.
 *
 * 16-bit ports were introduced in MSP430X and are available on
 * several chips in the 2xx and 4xx family.  In 2xx/4xx MCUs, PORTA
 * overlays P7/P8; in 5xx MCUs it overlays P1/P2.
 *
 * In pre-5xx families, registers supporting interrupts have a
 * different layout than registers that do not support interrupts.
 * However, the layouts (exclusive of SEL2 and REN) are compatible
 * within those types.
 *
 * Thus there are several distinct layouts that need to be supported:
 *
 * + [PORT_IE_8] Pre-5xx interrupt-capable, 8-bit interface
 * + [PORT_8] Pre-5xx non-interrupt, 8-bit interface
 * + [PORT_16] Pre-5xx non-interrupt, 16-bit interface
 * + [PORT_5XX] 5xx registers, 8-bit interface
 * + [PORT_5XX_16] 5xx registers, 16-bit interface
 *
 * 5xx chips are identified by MSP430XV2_CPU.  For these, a uniform
 * HPL based on the 16-bit alphabetic register names is presented.
 */

/** Layout for pre-5xx--family ports supporting interrupts.
 *
 * Access to SEL2 capability for these ports is not available in the
 * hardware-presentation layer. */
typedef struct xBSP430periphPORT_IE_8 {
	unsigned char in;			/* 0x00 */
	unsigned char out;			/* 0x01 */
	unsigned char dir;			/* 0x02 */
	unsigned char ifg;			/* 0x03 */
	unsigned char ies;			/* 0x04 */
	unsigned char ie;			/* 0x05 */
	unsigned char sel;			/* 0x06 */
	unsigned char ren;			/* 0x07 */
} xBSP430periphPORT_IE_8;

/** Layout for pre-5xx--family 8-bit ports not supporting interrupts.
 *
 * Access to SEL2 and REN capability for these ports is not available
 * in the hardware-presentation layer. */
typedef struct xBSP430periphPORT_8 {
	unsigned char in;			/* 0x00 */
	unsigned char out;			/* 0x01 */
	unsigned char dir;			/* 0x02 */
	unsigned char sel;			/* 0x03 */
} xBSP430periphPORT_8;

/** Helper for accessing 8-bit registers within 16-bit registers */
typedef union xBSP430periphPORT_16_u {
	unsigned int w;				/**< Word access (e.g., PAIN) */
	unsigned char b[2];			/**< Byte access, indexed */
	struct {
		unsigned char l;		/**< Low byte access for odd members of pair (e.g., P1IN) */
		unsigned char h;		/**< High byte access for even members of pair (e.g., P2IN) */
	};
} xBSP430periphPORT_16_u;

/** Layout for 2xx/4xx family 16-bit ports not supporting interrupts.
 *
 * Access to SEL2 and REN capability for these ports is not available
 * in the hardware-presentation layer. */
typedef struct xBSP430periphPORT_16 {
	xBSP430periphPORT_16_u in;	/* 0x00 */
	xBSP430periphPORT_16_u out;	/* 0x02 */
	xBSP430periphPORT_16_u dir;	/* 0x04 */
	xBSP430periphPORT_16_u sel;	/* 0x08 */
} xBSP430periphPORT_16;

/** Layout for 5xx family ports, 16-bit access
 */
typedef struct xBSP430periphPORT_5XX_16 {
	xBSP430periphPORT_16_u in;	/**< PxIN */ /* 0x00 */
	xBSP430periphPORT_16_u out;	/**< PxOUT */ /* 0x02 */
	xBSP430periphPORT_16_u dir;	/**< PxDIR (set for output) */ /* 0x04 */
	xBSP430periphPORT_16_u ren;	/**< PxREN (set to enable) */ /* 0x06 */
	xBSP430periphPORT_16_u ds;	/**< PxDS (drive select, some devices) */ /* 0x08 */
	union {
		xBSP430periphPORT_16_u sel; /**< PxSEL (non-FR5xx devices) */ /* 0x0A */
		xBSP430periphPORT_16_u sel0; /**< PxSEL0 (FR5xx devices) */ /* 0x0A */
	};
	xBSP430periphPORT_16_u sel1; /**< PxSEL1 (secondary/tertiary function, FR5xx devices only) */ /* 0x0C */
	unsigned int _reserved_x0E;
	xBSP430periphPORT_16_u selc; /**< PxSELC (support atomic transition to tertiary function, FR5xx devices only) */ /* 0x10 */
	unsigned int _reserved_x12;
	unsigned int _reserved_x14;
	unsigned int _reserved_x16;
	xBSP430periphPORT_16_u ies;	 /**< PxIES */ /* 0x18 */
	xBSP430periphPORT_16_u ie;	 /**< PxIE */ /* 0x1A */
	xBSP430periphPORT_16_u ifg;	 /**< PxIFG */ /* 0x1C */
} xBSP430periphPORT_5XX_16;

/** Layout for 5xx family ports, 8-bit access
 *
 * This structure includes the necessary padding to maintain alignment
 * when referencing the second 8-bit register in a 16-bit bank.
 */
typedef struct xBSP430periphPORT_5XX_8 {
	unsigned char in;	/**< PxIN */ /* 0x00 */
	unsigned char _reserved_x01;
	unsigned char out;	/**< PxOUT */ /* 0x02 */
	unsigned char _reserved_x03;
	unsigned char dir;	/**< PxDIR (set for output) */ /* 0x04 */
	unsigned char _reserved_x05;
	unsigned char ren;	/**< PxREN (set to enable) */ /* 0x06 */
	unsigned char _reserved_x07;
	unsigned char ds; /**< PxDS (drive select, some devices) */ /* 0x08 */
	unsigned char _reserved_x09;
	union {
		unsigned char sel; /**< PxSEL (non-FR5xx devices) */ /* 0x0A */
		unsigned char sel0; /**< PxSEL0 (FR5xx devices) */ /* 0x0A */
	};
	unsigned char _reserved_x0B;
	unsigned char sel1; /**< PxSEL1 (secondary/tertiary function, FR5xx devices only) */ /* 0x0C */
	unsigned char _reserved_x0D;
	unsigned char _reserved_x0E;
	unsigned char _reserved_x0F;
	unsigned char selc; /**< PxSELC (support atomic transition to tertiary function, FR5xx devices only) *//* 0x10 */
	unsigned char _reserved_x11;
	unsigned char _reserved_x12;
	unsigned char _reserved_x13;
	unsigned char _reserved_x14;
	unsigned char _reserved_x15;
	unsigned char _reserved_x16;
	unsigned char _reserved_x17;
	unsigned char ies;	 /**< PxIES */ /* 0x18 */
	unsigned char _reserved_x19;
	unsigned char ie;	 /**< PxIE */ /* 0x1A */
	unsigned char _reserved_x1B;
	unsigned char ifg;	 /**< PxIFG */ /* 0x1C */
} xBSP430periphPORT_5XX_8;

/** @cond DOXYGEN_INTERNAL */
#if defined(__MSP430_HAS_MSP430XV2_CPU__)
#define _BSP430_PERIPH_PORTIE xBSP430periphPORT_5XX_8
#define _BSP430_PERIPH_PORT xBSP430periphPORT_5XX_8
#define _BSP430_PERIPH_PORTW xBSP430periphPORT_5XX_16
#else /* MSP430XV2 */
#define _BSP430_PERIPH_PORTIE xBSP430periphPORT_IE_8
#define _BSP430_PERIPH_PORT xBSP430periphPORT_8
#define _BSP430_PERIPH_PORTW xBSP430periphPORT_16
#endif /* MSP430XV2 */
/** @endcond */ /* DOXYGEN_INTERNAL */

/** Structure used to access ports with interrupt capability.
 *
 * The underlying structure selected depends on the MCU family. */
typedef _BSP430_PERIPH_PORTIE xBSP430periphPORTIE;

/** Structure used to access ports without interrupt capability.
 *
 * The underlying structure selected depends on the MCU family. */
typedef _BSP430_PERIPH_PORT xBSP430periphPORT;

/** Structure used to access 16-bit ports.
 *
 * The underlying structure selected depends on the MCU family. */
typedef _BSP430_PERIPH_PORTW xBSP430periphPORTW;

/** Callback flag indicating ISR should yield.
 *
 * Since the #xBSP430portInterruptCallback does not execute in the
 * stack frame of the ISR top half, this bit is to be added to the
 * return value of a callback if the callback has detected that the
 * interrupt should yield before returning. */
#define BSP430_PORT_ISR_YIELD 0x1000

/** Get the peripheral register pointer for an interrupt-enabled port.
 *
 * @note All ports on 5xx-family devices are interrupt-enabled.
 * 
 * @param xHandle The handle identifier, such as #BSP430_PERIPH_PORT1.
 *
 * @return A typed pointer that can be used to manipulate the port.  A
 * null pointer is returned if the handle does not correspond to a
 * timer which has been enabled (e.g., with
 * #configBSP430_PERIPH_PORT1), or if the specified port does not
 * support interrupts (see #xBSP430periphLookupPORT)
 */
volatile xBSP430periphPORTIE * xBSP430periphLookupPORTIE (xBSP430periphHandle xHandle);

/** Get the peripheral register pointer for a non-interrupt-enabled port.
 *
 * @param xHandle The handle identifier, such as #BSP430_PERIPH_PORT1.
 *
 * @return A typed pointer that can be used to manipulate the port.  A
 * null pointer is returned if the handle does not correspond to a
 * timer which has been enabled (e.g., with
 * #configBSP430_PERIPH_PORT1), or if the specified port supports
 * interrupts (see #xBSP430periphLookupPORTIE)
 */
volatile xBSP430periphPORT * xBSP430periphLookupPORT (xBSP430periphHandle xHandle);

/** @cond DOXYGEN_INTERNAL */

#if defined(__MSP430_HAS_MSP430XV2_CPU__)
/* All 5xx ports are resistor enabled */
#define _BSP430_PERIPH_PORTA_BASEADDRESS __MSP430_BASEADDRESS_PORTA_R__
#define _BSP430_PERIPH_PORTB_BASEADDRESS __MSP430_BASEADDRESS_PORTB_R__
#define _BSP430_PERIPH_PORTC_BASEADDRESS __MSP430_BASEADDRESS_PORTC_R__
#define _BSP430_PERIPH_PORTD_BASEADDRESS __MSP430_BASEADDRESS_PORTD_R__
#define _BSP430_PERIPH_PORTE_BASEADDRESS __MSP430_BASEADDRESS_PORTE_R__
#define _BSP430_PERIPH_PORTF_BASEADDRESS __MSP430_BASEADDRESS_PORTF_R__

#define _BSP430_PERIPH_PORT1_BASEADDRESS __MSP430_BASEADDRESS_PORT1_R__
#define _BSP430_PERIPH_PORT2_BASEADDRESS __MSP430_BASEADDRESS_PORT2_R__
#define _BSP430_PERIPH_PORT3_BASEADDRESS __MSP430_BASEADDRESS_PORT3_R__
#define _BSP430_PERIPH_PORT4_BASEADDRESS __MSP430_BASEADDRESS_PORT4_R__
#define _BSP430_PERIPH_PORT5_BASEADDRESS __MSP430_BASEADDRESS_PORT5_R__
#define _BSP430_PERIPH_PORT6_BASEADDRESS __MSP430_BASEADDRESS_PORT6_R__
#define _BSP430_PERIPH_PORT7_BASEADDRESS __MSP430_BASEADDRESS_PORT7_R__
#define _BSP430_PERIPH_PORT8_BASEADDRESS __MSP430_BASEADDRESS_PORT8_R__
#define _BSP430_PERIPH_PORT9_BASEADDRESS __MSP430_BASEADDRESS_PORT9_R__
#define _BSP430_PERIPH_PORT10_BASEADDRESS __MSP430_BASEADDRESS_PORT10_R__
#define _BSP430_PERIPH_PORT11_BASEADDRESS __MSP430_BASEADDRESS_PORT11_R__

#define _BSP430_PERIPH_PORTJ_BASEADDRESS __MSP430_BASEADDRESS_PORTJ_R__

#else /* 5xx */
/* Port addresses are fixed for all pre-5xx families. */
#define _BSP430_PERIPH_PORT1_BASEADDRESS 0x0020
#define _BSP430_PERIPH_PORT2_BASEADDRESS 0x0028
#define _BSP430_PERIPH_PORT3_BASEADDRESS 0x0018
#define _BSP430_PERIPH_PORT4_BASEADDRESS 0x000C
#define _BSP430_PERIPH_PORT5_BASEADDRESS 0x0030
#define _BSP430_PERIPH_PORT6_BASEADDRESS 0x0034

#define _BSP430_PERIPH_PORTA_BASEADDRESS 0x0038
#define _BSP430_PERIPH_PORT7_BASEADDRESS 0x0038
#define _BSP430_PERIPH_PORT8_BASEADDRESS 0x0039

#define _BSP430_PERIPH_PORTB_BASEADDRESS 0x0008
#define _BSP430_PERIPH_PORT9_BASEADDRESS 0x0008
#define _BSP430_PERIPH_PORT10_BASEADDRESS 0x0009

#endif /* 5xx */

/** @endcond */ /* DOXYGEN_INTERNAL */

#if 1 // defined(__MSP430_HAS_MSP430XV2_CPU__)
/* 5xx-family port management */

/* Forward declaration to hardware abstraction layer for 5xx-family ports */
struct xBSP430port5xxState;

/** The PORT internal state is protected. */
typedef struct xBSP430port5xxState * xBSP430portHandle;

/** Prototype for callbacks from shared port interrupt service routines.
 *
 * @note Because these callbacks do not execute in the stack frame of
 * the ISR itself, you cannot use the standard @c
 * __bic_status_register_on_exit() intrinsic to affect the status
 * register flags upon return.  Instead, you must provide the bits
 * that you want cleared as the return value of the callback.
 *
 * @param port A reference to the HAL port structure associated with the port.
 *
 * @param bit The bit for which the interrupt was received; values
 * range from 0 through 7.
 *
 * @return Bits to clear in the status register before returning from
 * the ISR.  For example, if the routine wants to leave low-power mode
 * without affecting the interrupt enable bit, return @c LPM4_bits.
 * Other bits are also relevant, see #BSP430_PORT_ISR_YIELD. */
typedef int (* xBSP430portInterruptCallback) (xBSP430portHandle port, int bit);

struct xBSP430port5xxState {
	unsigned int flags;
	volatile xBSP430periphPORT_5XX_8 * const port;
	xBSP430portInterruptCallback isr[8];
};

/* !BSP430! insert=hpl_ba_decl */
/* BEGIN AUTOMATICALLY GENERATED CODE---DO NOT MODIFY [hpl_ba_decl] */
/** @def configBSP430_PERIPH_PORT1
 *
 * Define to a true value in @c FreeRTOSConfig.h to enable use of the
 * @c PORT1 peripheral HPL or HAL interface.  Only do this if the MCU
 * supports this device. */
#ifndef configBSP430_PERIPH_PORT1
#define configBSP430_PERIPH_PORT1 0
#endif /* configBSP430_PERIPH_PORT1 */

/** Handle for the raw PORT1 device.
 *
 * The handle may be used only if #configBSP430_PERIPH_PORT1
 * is defined to a true value. */
#define BSP430_PERIPH_PORT1 ((xBSP430periphHandle)(_BSP430_PERIPH_PORT1_BASEADDRESS))

/** Pointer to the peripheral register map for PORT1.
 *
 * The pointer may be used only if #configBSP430_PERIPH_PORT1
 * is defined to a true value. */
extern volatile xBSP430periphPORT * const xBSP430periph_PORT1;

/** @def configBSP430_PERIPH_PORT2
 *
 * Define to a true value in @c FreeRTOSConfig.h to enable use of the
 * @c PORT2 peripheral HPL or HAL interface.  Only do this if the MCU
 * supports this device. */
#ifndef configBSP430_PERIPH_PORT2
#define configBSP430_PERIPH_PORT2 0
#endif /* configBSP430_PERIPH_PORT2 */

/** Handle for the raw PORT2 device.
 *
 * The handle may be used only if #configBSP430_PERIPH_PORT2
 * is defined to a true value. */
#define BSP430_PERIPH_PORT2 ((xBSP430periphHandle)(_BSP430_PERIPH_PORT2_BASEADDRESS))

/** Pointer to the peripheral register map for PORT2.
 *
 * The pointer may be used only if #configBSP430_PERIPH_PORT2
 * is defined to a true value. */
extern volatile xBSP430periphPORT * const xBSP430periph_PORT2;

/** @def configBSP430_PERIPH_PORT3
 *
 * Define to a true value in @c FreeRTOSConfig.h to enable use of the
 * @c PORT3 peripheral HPL or HAL interface.  Only do this if the MCU
 * supports this device. */
#ifndef configBSP430_PERIPH_PORT3
#define configBSP430_PERIPH_PORT3 0
#endif /* configBSP430_PERIPH_PORT3 */

/** Handle for the raw PORT3 device.
 *
 * The handle may be used only if #configBSP430_PERIPH_PORT3
 * is defined to a true value. */
#define BSP430_PERIPH_PORT3 ((xBSP430periphHandle)(_BSP430_PERIPH_PORT3_BASEADDRESS))

/** Pointer to the peripheral register map for PORT3.
 *
 * The pointer may be used only if #configBSP430_PERIPH_PORT3
 * is defined to a true value. */
extern volatile xBSP430periphPORT * const xBSP430periph_PORT3;

/** @def configBSP430_PERIPH_PORT4
 *
 * Define to a true value in @c FreeRTOSConfig.h to enable use of the
 * @c PORT4 peripheral HPL or HAL interface.  Only do this if the MCU
 * supports this device. */
#ifndef configBSP430_PERIPH_PORT4
#define configBSP430_PERIPH_PORT4 0
#endif /* configBSP430_PERIPH_PORT4 */

/** Handle for the raw PORT4 device.
 *
 * The handle may be used only if #configBSP430_PERIPH_PORT4
 * is defined to a true value. */
#define BSP430_PERIPH_PORT4 ((xBSP430periphHandle)(_BSP430_PERIPH_PORT4_BASEADDRESS))

/** Pointer to the peripheral register map for PORT4.
 *
 * The pointer may be used only if #configBSP430_PERIPH_PORT4
 * is defined to a true value. */
extern volatile xBSP430periphPORT * const xBSP430periph_PORT4;

/** @def configBSP430_PERIPH_PORT5
 *
 * Define to a true value in @c FreeRTOSConfig.h to enable use of the
 * @c PORT5 peripheral HPL or HAL interface.  Only do this if the MCU
 * supports this device. */
#ifndef configBSP430_PERIPH_PORT5
#define configBSP430_PERIPH_PORT5 0
#endif /* configBSP430_PERIPH_PORT5 */

/** Handle for the raw PORT5 device.
 *
 * The handle may be used only if #configBSP430_PERIPH_PORT5
 * is defined to a true value. */
#define BSP430_PERIPH_PORT5 ((xBSP430periphHandle)(_BSP430_PERIPH_PORT5_BASEADDRESS))

/** Pointer to the peripheral register map for PORT5.
 *
 * The pointer may be used only if #configBSP430_PERIPH_PORT5
 * is defined to a true value. */
extern volatile xBSP430periphPORT * const xBSP430periph_PORT5;

/** @def configBSP430_PERIPH_PORT6
 *
 * Define to a true value in @c FreeRTOSConfig.h to enable use of the
 * @c PORT6 peripheral HPL or HAL interface.  Only do this if the MCU
 * supports this device. */
#ifndef configBSP430_PERIPH_PORT6
#define configBSP430_PERIPH_PORT6 0
#endif /* configBSP430_PERIPH_PORT6 */

/** Handle for the raw PORT6 device.
 *
 * The handle may be used only if #configBSP430_PERIPH_PORT6
 * is defined to a true value. */
#define BSP430_PERIPH_PORT6 ((xBSP430periphHandle)(_BSP430_PERIPH_PORT6_BASEADDRESS))

/** Pointer to the peripheral register map for PORT6.
 *
 * The pointer may be used only if #configBSP430_PERIPH_PORT6
 * is defined to a true value. */
extern volatile xBSP430periphPORT * const xBSP430periph_PORT6;

/** @def configBSP430_PERIPH_PORT7
 *
 * Define to a true value in @c FreeRTOSConfig.h to enable use of the
 * @c PORT7 peripheral HPL or HAL interface.  Only do this if the MCU
 * supports this device. */
#ifndef configBSP430_PERIPH_PORT7
#define configBSP430_PERIPH_PORT7 0
#endif /* configBSP430_PERIPH_PORT7 */

/** Handle for the raw PORT7 device.
 *
 * The handle may be used only if #configBSP430_PERIPH_PORT7
 * is defined to a true value. */
#define BSP430_PERIPH_PORT7 ((xBSP430periphHandle)(_BSP430_PERIPH_PORT7_BASEADDRESS))

/** Pointer to the peripheral register map for PORT7.
 *
 * The pointer may be used only if #configBSP430_PERIPH_PORT7
 * is defined to a true value. */
extern volatile xBSP430periphPORT * const xBSP430periph_PORT7;

/** @def configBSP430_PERIPH_PORT8
 *
 * Define to a true value in @c FreeRTOSConfig.h to enable use of the
 * @c PORT8 peripheral HPL or HAL interface.  Only do this if the MCU
 * supports this device. */
#ifndef configBSP430_PERIPH_PORT8
#define configBSP430_PERIPH_PORT8 0
#endif /* configBSP430_PERIPH_PORT8 */

/** Handle for the raw PORT8 device.
 *
 * The handle may be used only if #configBSP430_PERIPH_PORT8
 * is defined to a true value. */
#define BSP430_PERIPH_PORT8 ((xBSP430periphHandle)(_BSP430_PERIPH_PORT8_BASEADDRESS))

/** Pointer to the peripheral register map for PORT8.
 *
 * The pointer may be used only if #configBSP430_PERIPH_PORT8
 * is defined to a true value. */
extern volatile xBSP430periphPORT * const xBSP430periph_PORT8;

/** @def configBSP430_PERIPH_PORT9
 *
 * Define to a true value in @c FreeRTOSConfig.h to enable use of the
 * @c PORT9 peripheral HPL or HAL interface.  Only do this if the MCU
 * supports this device. */
#ifndef configBSP430_PERIPH_PORT9
#define configBSP430_PERIPH_PORT9 0
#endif /* configBSP430_PERIPH_PORT9 */

/** Handle for the raw PORT9 device.
 *
 * The handle may be used only if #configBSP430_PERIPH_PORT9
 * is defined to a true value. */
#define BSP430_PERIPH_PORT9 ((xBSP430periphHandle)(_BSP430_PERIPH_PORT9_BASEADDRESS))

/** Pointer to the peripheral register map for PORT9.
 *
 * The pointer may be used only if #configBSP430_PERIPH_PORT9
 * is defined to a true value. */
extern volatile xBSP430periphPORT * const xBSP430periph_PORT9;

/** @def configBSP430_PERIPH_PORT10
 *
 * Define to a true value in @c FreeRTOSConfig.h to enable use of the
 * @c PORT10 peripheral HPL or HAL interface.  Only do this if the MCU
 * supports this device. */
#ifndef configBSP430_PERIPH_PORT10
#define configBSP430_PERIPH_PORT10 0
#endif /* configBSP430_PERIPH_PORT10 */

/** Handle for the raw PORT10 device.
 *
 * The handle may be used only if #configBSP430_PERIPH_PORT10
 * is defined to a true value. */
#define BSP430_PERIPH_PORT10 ((xBSP430periphHandle)(_BSP430_PERIPH_PORT10_BASEADDRESS))

/** Pointer to the peripheral register map for PORT10.
 *
 * The pointer may be used only if #configBSP430_PERIPH_PORT10
 * is defined to a true value. */
extern volatile xBSP430periphPORT * const xBSP430periph_PORT10;

/** @def configBSP430_PERIPH_PORT11
 *
 * Define to a true value in @c FreeRTOSConfig.h to enable use of the
 * @c PORT11 peripheral HPL or HAL interface.  Only do this if the MCU
 * supports this device. */
#ifndef configBSP430_PERIPH_PORT11
#define configBSP430_PERIPH_PORT11 0
#endif /* configBSP430_PERIPH_PORT11 */

/** Handle for the raw PORT11 device.
 *
 * The handle may be used only if #configBSP430_PERIPH_PORT11
 * is defined to a true value. */
#define BSP430_PERIPH_PORT11 ((xBSP430periphHandle)(_BSP430_PERIPH_PORT11_BASEADDRESS))

/** Pointer to the peripheral register map for PORT11.
 *
 * The pointer may be used only if #configBSP430_PERIPH_PORT11
 * is defined to a true value. */
extern volatile xBSP430periphPORT * const xBSP430periph_PORT11;

/* END AUTOMATICALLY GENERATED CODE [hpl_ba_decl] */
/* !BSP430! end=hpl_ba_decl */

/* !BSP430! insert=hal_isr_decl */
/* BEGIN AUTOMATICALLY GENERATED CODE---DO NOT MODIFY [hal_isr_decl] */
/** @def configBSP430_HAL_PORT1_ISR
 *
 * Define to a true value in @c FreeRTOSConfig.h to use the BSP430 HAL
 * interrupt vector for @c PORT1.  Define to a false value if you
 * need complete control over how interrupts are handled for the device
 * and will be defining the vector yourself.
 *
 * @note #configBSP430_PERIPH_PORT1 must be also be true. */
#ifndef configBSP430_HAL_PORT1_ISR
#define configBSP430_HAL_PORT1_ISR 1
#endif /* configBSP430_HAL_PORT1_ISR */

/** @def configBSP430_HAL_PORT2_ISR
 *
 * Define to a true value in @c FreeRTOSConfig.h to use the BSP430 HAL
 * interrupt vector for @c PORT2.  Define to a false value if you
 * need complete control over how interrupts are handled for the device
 * and will be defining the vector yourself.
 *
 * @note #configBSP430_PERIPH_PORT2 must be also be true. */
#ifndef configBSP430_HAL_PORT2_ISR
#define configBSP430_HAL_PORT2_ISR 1
#endif /* configBSP430_HAL_PORT2_ISR */

/** @def configBSP430_HAL_PORT3_ISR
 *
 * Define to a true value in @c FreeRTOSConfig.h to use the BSP430 HAL
 * interrupt vector for @c PORT3.  Define to a false value if you
 * need complete control over how interrupts are handled for the device
 * and will be defining the vector yourself.
 *
 * @note #configBSP430_PERIPH_PORT3 must be also be true. */
#ifndef configBSP430_HAL_PORT3_ISR
#define configBSP430_HAL_PORT3_ISR 1
#endif /* configBSP430_HAL_PORT3_ISR */

/** @def configBSP430_HAL_PORT4_ISR
 *
 * Define to a true value in @c FreeRTOSConfig.h to use the BSP430 HAL
 * interrupt vector for @c PORT4.  Define to a false value if you
 * need complete control over how interrupts are handled for the device
 * and will be defining the vector yourself.
 *
 * @note #configBSP430_PERIPH_PORT4 must be also be true. */
#ifndef configBSP430_HAL_PORT4_ISR
#define configBSP430_HAL_PORT4_ISR 1
#endif /* configBSP430_HAL_PORT4_ISR */

/** @def configBSP430_HAL_PORT5_ISR
 *
 * Define to a true value in @c FreeRTOSConfig.h to use the BSP430 HAL
 * interrupt vector for @c PORT5.  Define to a false value if you
 * need complete control over how interrupts are handled for the device
 * and will be defining the vector yourself.
 *
 * @note #configBSP430_PERIPH_PORT5 must be also be true. */
#ifndef configBSP430_HAL_PORT5_ISR
#define configBSP430_HAL_PORT5_ISR 1
#endif /* configBSP430_HAL_PORT5_ISR */

/** @def configBSP430_HAL_PORT6_ISR
 *
 * Define to a true value in @c FreeRTOSConfig.h to use the BSP430 HAL
 * interrupt vector for @c PORT6.  Define to a false value if you
 * need complete control over how interrupts are handled for the device
 * and will be defining the vector yourself.
 *
 * @note #configBSP430_PERIPH_PORT6 must be also be true. */
#ifndef configBSP430_HAL_PORT6_ISR
#define configBSP430_HAL_PORT6_ISR 1
#endif /* configBSP430_HAL_PORT6_ISR */

/** @def configBSP430_HAL_PORT7_ISR
 *
 * Define to a true value in @c FreeRTOSConfig.h to use the BSP430 HAL
 * interrupt vector for @c PORT7.  Define to a false value if you
 * need complete control over how interrupts are handled for the device
 * and will be defining the vector yourself.
 *
 * @note #configBSP430_PERIPH_PORT7 must be also be true. */
#ifndef configBSP430_HAL_PORT7_ISR
#define configBSP430_HAL_PORT7_ISR 1
#endif /* configBSP430_HAL_PORT7_ISR */

/** @def configBSP430_HAL_PORT8_ISR
 *
 * Define to a true value in @c FreeRTOSConfig.h to use the BSP430 HAL
 * interrupt vector for @c PORT8.  Define to a false value if you
 * need complete control over how interrupts are handled for the device
 * and will be defining the vector yourself.
 *
 * @note #configBSP430_PERIPH_PORT8 must be also be true. */
#ifndef configBSP430_HAL_PORT8_ISR
#define configBSP430_HAL_PORT8_ISR 1
#endif /* configBSP430_HAL_PORT8_ISR */

/** @def configBSP430_HAL_PORT9_ISR
 *
 * Define to a true value in @c FreeRTOSConfig.h to use the BSP430 HAL
 * interrupt vector for @c PORT9.  Define to a false value if you
 * need complete control over how interrupts are handled for the device
 * and will be defining the vector yourself.
 *
 * @note #configBSP430_PERIPH_PORT9 must be also be true. */
#ifndef configBSP430_HAL_PORT9_ISR
#define configBSP430_HAL_PORT9_ISR 1
#endif /* configBSP430_HAL_PORT9_ISR */

/** @def configBSP430_HAL_PORT10_ISR
 *
 * Define to a true value in @c FreeRTOSConfig.h to use the BSP430 HAL
 * interrupt vector for @c PORT10.  Define to a false value if you
 * need complete control over how interrupts are handled for the device
 * and will be defining the vector yourself.
 *
 * @note #configBSP430_PERIPH_PORT10 must be also be true. */
#ifndef configBSP430_HAL_PORT10_ISR
#define configBSP430_HAL_PORT10_ISR 1
#endif /* configBSP430_HAL_PORT10_ISR */

/** @def configBSP430_HAL_PORT11_ISR
 *
 * Define to a true value in @c FreeRTOSConfig.h to use the BSP430 HAL
 * interrupt vector for @c PORT11.  Define to a false value if you
 * need complete control over how interrupts are handled for the device
 * and will be defining the vector yourself.
 *
 * @note #configBSP430_PERIPH_PORT11 must be also be true. */
#ifndef configBSP430_HAL_PORT11_ISR
#define configBSP430_HAL_PORT11_ISR 1
#endif /* configBSP430_HAL_PORT11_ISR */

/* END AUTOMATICALLY GENERATED CODE [hal_isr_decl] */
/* !BSP430! end=hal_isr_decl */

#else /* MSP430XV2 */
/* 1xx through 4xx port management */
#warning not yet implemented
#endif /* MSP430XV2 */

/* !BSP430! insert=hal_decl */
/* BEGIN AUTOMATICALLY GENERATED CODE---DO NOT MODIFY [hal_decl] */
/** FreeRTOS HAL handle for PORT1.
 *
 * The handle may be used only if #configBSP430_PERIPH_PORT1
 * is defined to a true value. */
extern xBSP430portHandle const xBSP430port_PORT1;

/** FreeRTOS HAL handle for PORT2.
 *
 * The handle may be used only if #configBSP430_PERIPH_PORT2
 * is defined to a true value. */
extern xBSP430portHandle const xBSP430port_PORT2;

/** FreeRTOS HAL handle for PORT3.
 *
 * The handle may be used only if #configBSP430_PERIPH_PORT3
 * is defined to a true value. */
extern xBSP430portHandle const xBSP430port_PORT3;

/** FreeRTOS HAL handle for PORT4.
 *
 * The handle may be used only if #configBSP430_PERIPH_PORT4
 * is defined to a true value. */
extern xBSP430portHandle const xBSP430port_PORT4;

/** FreeRTOS HAL handle for PORT5.
 *
 * The handle may be used only if #configBSP430_PERIPH_PORT5
 * is defined to a true value. */
extern xBSP430portHandle const xBSP430port_PORT5;

/** FreeRTOS HAL handle for PORT6.
 *
 * The handle may be used only if #configBSP430_PERIPH_PORT6
 * is defined to a true value. */
extern xBSP430portHandle const xBSP430port_PORT6;

/** FreeRTOS HAL handle for PORT7.
 *
 * The handle may be used only if #configBSP430_PERIPH_PORT7
 * is defined to a true value. */
extern xBSP430portHandle const xBSP430port_PORT7;

/** FreeRTOS HAL handle for PORT8.
 *
 * The handle may be used only if #configBSP430_PERIPH_PORT8
 * is defined to a true value. */
extern xBSP430portHandle const xBSP430port_PORT8;

/** FreeRTOS HAL handle for PORT9.
 *
 * The handle may be used only if #configBSP430_PERIPH_PORT9
 * is defined to a true value. */
extern xBSP430portHandle const xBSP430port_PORT9;

/** FreeRTOS HAL handle for PORT10.
 *
 * The handle may be used only if #configBSP430_PERIPH_PORT10
 * is defined to a true value. */
extern xBSP430portHandle const xBSP430port_PORT10;

/** FreeRTOS HAL handle for PORT11.
 *
 * The handle may be used only if #configBSP430_PERIPH_PORT11
 * is defined to a true value. */
extern xBSP430portHandle const xBSP430port_PORT11;

/* END AUTOMATICALLY GENERATED CODE [hal_decl] */
/* !BSP430! end=hal_decl */

xBSP430portHandle xBSP430portLookup (xBSP430periphHandle xHandle);

#endif /* BSP430_PERIPH_PORT_H */